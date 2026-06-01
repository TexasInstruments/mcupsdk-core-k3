#!/usr/bin/env python3
"""
snagfactory_flash.py — TI SOC flash utility
Wraps snagrecover + snagflash for AM62x family boards.

Usage:
    python3 snagfactory_flash.py --board am62px-sk --target emmc  \
        --cfg-file <path-to>.cfg --gen-cfg 

    python3 snagfactory_flash.py --board am62px-sk --target ospi-nor  \
        --cfg-file <path-to>.cfg --gen-cfg

    python3 snagfactory_flash.py --board am62px-sk --list-targets
"""

import argparse
import logging
import os
import re
import subprocess
import sys
import time
from datetime import datetime
from pathlib import Path

import yaml


SCRIPT_DIR     = Path(__file__).resolve().parent     # .../snagfactory/
TOOLS_BOOT_DIR = SCRIPT_DIR.parent                   # .../tools/boot/
SDK_PATH       = SCRIPT_DIR.parents[2]               # .../mcu_plus_sdk/
LOGS_DIR       = SCRIPT_DIR / "logs"

# ─────────────────────────────────────────────
# Board → params.yaml map
# ─────────────────────────────────────────────
BOARD_YAML_MAP = {
    "am62px-sk":    "am62px-sk/params.yaml",
    "am62ax-sk":    "am62ax-sk/params.yaml",
    "am62x-sip-sk": "am62x-sip-sk/params.yaml",
    "am62x-sk":     "am62x-sk/params.yaml",
    "am62x-sk-lp":  "am62x-sk-lp/params.yaml",
    "am62dx-evm":   "am62dx-evm/params.yaml",
}


# ─────────────────────────────────────────────
# Custom YAML types & representers
# ─────────────────────────────────────────────
class HexInt(int):
    """Integer that serializes as unquoted hex in YAML (e.g. 0x40000)."""
    pass

class QuotedStr(str):
    """String that serializes with double quotes in YAML (e.g. "hwpart 1")."""
    pass

def _hex_representer(dumper, data):
    return dumper.represent_scalar('tag:yaml.org,2002:int', hex(data))

def _quoted_str_representer(dumper, data):
    return dumper.represent_scalar('tag:yaml.org,2002:str', data, style='"')

def _str_representer(dumper, data):
    return dumper.represent_scalar('tag:yaml.org,2002:str', data, style='')

yaml.add_representer(HexInt,    _hex_representer)
yaml.add_representer(QuotedStr, _quoted_str_representer)
yaml.add_representer(str,       _str_representer)


def _hex(value) -> HexInt:
    """Convert a hex string '0x...' or int to HexInt for unquoted YAML output."""
    if isinstance(value, str):
        return HexInt(int(value, 16))
    return HexInt(value)


# ─────────────────────────────────────────────
# Logging
# ─────────────────────────────────────────────
def setup_logger(board: str, target: str) -> logging.Logger:
    LOGS_DIR.mkdir(parents=True, exist_ok=True)
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    log_file  = LOGS_DIR / f"flash_{board}_{target}_{timestamp}.log"

    logger = logging.getLogger("snagfactory")
    logger.setLevel(logging.DEBUG)

    fmt = logging.Formatter("[%(levelname)s] %(message)s")

    ch = logging.StreamHandler()
    ch.setLevel(logging.DEBUG)
    ch.setFormatter(fmt)

    fh = logging.FileHandler(log_file)
    fh.setLevel(logging.DEBUG)
    fh.setFormatter(fmt)

    logger.addHandler(ch)
    logger.addHandler(fh)

    logger.info(f"Log file: {log_file}")
    return logger


# ─────────────────────────────────────────────
# YAML Loading
# ─────────────────────────────────────────────
def load_params(board: str, logger: logging.Logger) -> dict:
    """Load params.yaml for the given board."""
    yaml_rel = BOARD_YAML_MAP.get(board)
    if not yaml_rel:
        logger.error(
            f"Unknown board '{board}'. "
            f"Supported: {list(BOARD_YAML_MAP.keys())}"
        )
        sys.exit(1)

    yaml_path = SCRIPT_DIR / yaml_rel
    if not yaml_path.exists():
        logger.error(f"Params file not found: {yaml_path}")
        sys.exit(1)

    with open(yaml_path) as f:
        params = yaml.safe_load(f)

    params_board = params.get("board_name")
    if params_board and params_board != board:
        logger.warning(
            f"params.yaml board_name '{params_board}' "
            f"does not match CLI --board '{board}'"
        )

    logger.info(f"Loaded params from: {yaml_path}")
    logger.info(f"Board: {params.get('board_name')}  SOC: {params.get('soc_model')}")
    return params


# ─────────────────────────────────────────────
# CFG File Parsing
# ─────────────────────────────────────────────
def parse_cfg_file(cfg_file: Path, logger: logging.Logger, sec: str = "hs_fs") -> list:
    """
    ...same docstring...
    Filters flash entries by security variant based on filename suffix (hs_fs / hs_se).
    """
    entries  = []
    current  = {}

    def _should_skip_by_sec(file_val: str) -> bool:
        """Skip entry if it belongs to the OTHER security variant."""
        other = "hs_se" if sec == "hs_fs" else "hs_fs"
        return other in file_val and sec not in file_val

    with open(cfg_file) as f:
        for i, raw_line in enumerate(f, 1):
            line = raw_line.strip()

            if not line or line.startswith("#"):
                continue

            is_single_line = (
                re.search(r"--file=\S+", line) and
                re.search(r"--operation=\S+", line) and
                re.search(r"--flash-offset=\S+", line)
            )

            if is_single_line:
                file_m   = re.search(r"--file=(\S+)", line)
                op_m     = re.search(r"--operation=(\S+)", line)
                offset_m = re.search(r"--flash-offset=(\S+)", line)
                writer_m = re.search(r"--flash-writer=", line)

                if writer_m:
                    logger.debug(f"Line {i}: skipping flash-writer entry")
                    continue

                if not (file_m and op_m and offset_m):
                    logger.warning(f"Line {i}: incomplete entry, skipping: {line}")
                    continue

                file_val = file_m.group(1)
                op_val   = op_m.group(1)
                offset   = offset_m.group(1)

                if "sbl_uart_uniflash_stage2" in file_val:
                    logger.debug(f"Line {i}: skipping uniflash stage2 RAM helper")
                    continue
                if op_val in ("flashverify", "flash-phy-tuning-data", "erase"):
                    logger.debug(f"Line {i}: skipping operation '{op_val}'")
                    continue
                if _should_skip_by_sec(file_val):
                    logger.debug(f"Line {i}: skipping mismatched sec variant: {file_val}")
                    continue

                abs_path = (TOOLS_BOOT_DIR / file_val).resolve()
                entries.append({"file": abs_path, "offset": offset})
                logger.debug(f"Line {i}: entry → {abs_path.name} @ {offset}")

            else:
                m = re.match(r"-{1,2}([\w-]+?)=(.+)", line)
                if not m:
                    continue

                key, val = m.group(1), m.group(2).strip()

                if key == "flash-writer":
                    logger.debug(f"Line {i}: skipping flash-writer entry")
                    current = {}
                    continue

                if key == "file":
                    if current:
                        logger.debug(f"Line {i}: incomplete entry discarded: {current}")
                        current = {}
                    current["file"] = val

                elif key == "operation":
                    current["operation"] = val

                elif key == "flash-offset":
                    current["offset"] = val

                if {"file", "operation", "offset"} <= current.keys():
                    op       = current["operation"]
                    file_val = current["file"]

                    if op in ("flashverify", "flash-phy-tuning-data", "erase"):
                        logger.debug(f"Line {i}: skipping operation '{op}'")
                        current = {}
                        continue

                    if "sbl_uart_uniflash_stage2" in file_val:
                        logger.debug(f"Line {i}: skipping uniflash stage2 RAM helper")
                        current = {}
                        continue

                    if _should_skip_by_sec(file_val):                        # ← NEW
                        logger.debug(f"Line {i}: skipping mismatched sec variant: {file_val}")
                        current = {}
                        continue

                    abs_path = (TOOLS_BOOT_DIR / file_val).resolve()
                    entries.append({"file": abs_path, "offset": current["offset"]})
                    logger.debug(f"Line {i}: entry → {abs_path.name} @ {current['offset']}")
                    current = {}

    logger.info(f"Parsed {len(entries)} flash entries from: {cfg_file.name} (sec={sec})")
    return entries


# ─────────────────────────────────────────────
# Validation
# ─────────────────────────────────────────────
def validate_firmware(params: dict, flash_entries: list, logger: logging.Logger):
    """Validate all firmware and flash entry files exist before flashing."""
    errors = []

    for fw_name, fw_info in params.get("recovery_firmware", {}).items():
        p = (SCRIPT_DIR / fw_info["path"]).resolve()
        if not p.exists():
            errors.append(f"Recovery firmware missing: {p}")
        else:
            logger.debug(f"OK: {fw_name} → {p}")

    for entry in flash_entries:
        p = entry["file"]
        if not p.exists():
            errors.append(f"Flash entry missing: {p}")
        else:
            logger.debug(f"OK: flash entry → {p.name} @ {entry['offset']}")

    if errors:
        logger.error("Pre-flight validation failed:")
        for e in errors:
            logger.error(f"  {e}")
        sys.exit(1)

    logger.info("Pre-flight validation passed.")


# ─────────────────────────────────────────────
# CMD File Generation
# ─────────────────────────────────────────────
def generate_cmd(
    params: dict,
    board: str,
    target: str,
    sec: str,
    flash_entries: list,
    logger: logging.Logger,
) -> Path:
    board_dir = SCRIPT_DIR / board
    board_dir.mkdir(parents=True, exist_ok=True)

    cmd_path      = board_dir / f"{board}_{target}_{sec}.cmd"
    target_cfg    = params["targets"][target]
    target_device = target_cfg["target_device"]
    hwpart        = target_cfg.get("hwpart")
    eraseblk_size = target_cfg.get("eraseblk_size")
    fb_addr       = params["fb_buffer_addr"]
    fb_size       = params["fb_buffer_size"]

    lines = []

    # ── Header ────────────────────────────────────────────────────────────
    lines.append(f"set target {target_device}")
    lines.append(f"set fb-addr {fb_addr}")
    lines.append(f"set fb-size {fb_size}")

    if eraseblk_size:
        lines.append(f"set eraseblk-size {eraseblk_size}")

    lines.append("")

    # ── Flash entries ─────────────────────────────────────────────────────
    for entry in flash_entries:
        filepath = str(entry["file"])
        offset   = entry["offset"]

        if hwpart is not None:
            lines.append(f'flash "{filepath}" {offset} hwpart {hwpart}')
        else:
            lines.append(f'flash "{filepath}" {offset}')

        lines.append("")

    lines.append("exit")

    with open(cmd_path, "w") as f:
        f.write("\n".join(lines) + "\n")

    logger.info(f"Generated CMD file: {cmd_path}")
    return cmd_path


# ─────────────────────────────────────────────
# snagrecover YAML Generation
# ─────────────────────────────────────────────
def generate_snagrecover_yaml(
    params: dict,
    board: str,
    target: str,
    sec: str,
    flash_entries: list,
    logger: logging.Logger,
) -> Path:
    board_dir = SCRIPT_DIR / board
    board_dir.mkdir(parents=True, exist_ok=True)

    yaml_path  = board_dir / f"{board}_{target}_{sec}.yaml"
    target_cfg = params["targets"][target]
    soc_model  = params["soc_model"]
    vid        = params["usb_ids"]["vid"]
    pid        = params["usb_ids"]["pid"]
    fw         = params["recovery_firmware"]

    fw_key    = f"{soc_model}-firmware"
    tasks_key = f"{soc_model}-tasks"
    usb_key   = f"{vid}:{pid}"

    # ── 1. boards ─────────────────────────────────────────────────────────
    boards = {QuotedStr(usb_key): QuotedStr(soc_model)}

    # ── 2. Firmware block ─────────────────────────────────────────────────
    firmware_block = {
        "tiboot3": {"path": fw["tiboot3"]["path"]},
        "tispl":   {"path": fw["tispl"]["path"]},
        "u-boot":  {"path": fw["u-boot"]["path"]},
    }

    # ── 3. Tasks list ─────────────────────────────────────────────────────
    tasks = []

    device_block = {
        "target-device":  target_cfg["target_device"],
        "fb-buffer-addr": _hex(params["fb_buffer_addr"]),
        "fb-buffer-size": _hex(params["fb_buffer_size"]),
    }
    if target_cfg.get("eraseblk_size"):
        device_block["eraseblk-size"] = _hex(target_cfg["eraseblk_size"])

    tasks.append(device_block)

    if target == "emmc":
        tasks.append({"task": "reset"})

    hwpart     = target_cfg.get("hwpart")
    flash_args = []

    for entry in flash_entries:
        arg = {
            "image":        str(entry["file"]),
            "image-offset": _hex(entry["offset"]),
        }
        if hwpart is not None:
            arg["part"] = QuotedStr(f"hwpart {hwpart}")
        flash_args.append(arg)

    tasks.append({"task": "flash", "args": flash_args})

    # ── 4. Assemble document ──────────────────────────────────────────────
    doc = {
        "boards": boards,
        "soc-models": {
            fw_key:    firmware_block,
            tasks_key: tasks,
        },
    }

    # ── 5. Write YAML ─────────────────────────────────────────────────────
    with open(yaml_path, "w") as f:
        yaml.dump(
            doc,
            f,
            default_flow_style=False,
            sort_keys=False,
            allow_unicode=True,
        )

    logger.info(f"Generated YAML file: {yaml_path}")
    return yaml_path
# ─────────────────────────────────────────────
# snagrecover
# ─────────────────────────────────────────────
def run_snagrecover(params: dict, logger: logging.Logger):
    """
    Run snagrecover using:
        snagrecover -s <soc_model> \
            -F "{'tiboot3': {'path': '...'}}" \
            -F "{'tispl':   {'path': '...'}}" \
            -F "{'u-boot':  {'path': '...'}}"
    """
    soc_model = params["soc_model"]
    firmware  = params.get("recovery_firmware", {})

    cmd = ["snagrecover", "-s", soc_model]

    usb_path = params.get("usb_path")
    if usb_path:
        cmd += ["--usb-path", str(usb_path)]

    for fw_name, fw_info in firmware.items():
        resolved_path = str((SCRIPT_DIR / fw_info["path"]).resolve())
        fw_dict = {fw_name: {"path": resolved_path}}
        cmd += ["-F", str(fw_dict)]

    logger.info(f"Running snagrecover: {' '.join(cmd)}")

    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.stdout:
        logger.info(result.stdout.strip())
    if result.stderr:
        logger.debug(result.stderr.strip())
    if result.returncode != 0:
        logger.error(f"snagrecover failed (exit {result.returncode})")
        sys.exit(1)

    logger.info("snagrecover completed successfully.")


# ─────────────────────────────────────────────
# Wait for Fastboot
# ─────────────────────────────────────────────
def wait_for_fastboot(vid: str, pid: str, logger: logging.Logger, timeout: int = 60):
    """Poll until fastboot device is available."""
    logger.info(f"Waiting for fastboot device {vid}:{pid} ...")
    deadline = time.time() + timeout

    while time.time() < deadline:
        result = subprocess.run(
            ["fastboot", "devices"],
            capture_output=True,
            text=True,
        )
        if "fastboot" in result.stdout:
            logger.info("Fastboot device detected.")
            return
        time.sleep(2)

    logger.error(f"Timed out waiting for fastboot device after {timeout}s")
    sys.exit(1)


# ─────────────────────────────────────────────
# snagflash
# ─────────────────────────────────────────────
def run_snagflash(params: dict, cmd_path: Path, logger: logging.Logger):
    """Run snagflash with the generated .cmd file."""
    vid = params["usb_ids"]["vid"]
    pid = params["usb_ids"]["pid"]

    cmd = [
        "snagflash",
        "-P", "fastboot-uboot",
        "-p", f"{vid}:{pid}",
        "-I", str(cmd_path),
    ]

    logger.info(f"Running snagflash: {' '.join(cmd)}")

    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.stdout:
        logger.info(result.stdout.strip())
    if result.stderr:
        logger.debug(result.stderr.strip())
    if result.returncode != 0:
        logger.error(f"snagflash failed (exit {result.returncode})")
        sys.exit(1)

    logger.info("snagflash completed successfully.")


# ─────────────────────────────────────────────
# CLI
# ─────────────────────────────────────────────
def parse_args():
    parser = argparse.ArgumentParser(
        description="TI SOC flash utility — wraps snagrecover + snagflash",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Flash eMMC on am62px-sk
  python3 snagfactory_flash.py --board am62px-sk --target emmc  --cfg-file emmc.cfg

  # Flash ospi-nor on am62px-sk
  python3 snagfactory_flash.py --board am62px-sk --target ospi-nor --cfg-file ospi_nor.cfg

  # GUI mode — generate CMD + YAML only, no flashing
  python3 snagfactory_flash.py --board am62ax-sk --target ospi-nand --cfg-file <path>.cfg --gen-cfg

  # List available targets for a board
  python3 snagfactory_flash.py --board am62px-sk --list-targets
        """,
    )
    parser.add_argument(
        "--board",
        required=True,
        choices=list(BOARD_YAML_MAP.keys()),
        help="Board to flash. Supported: " + ", ".join(BOARD_YAML_MAP.keys()),
    )
    parser.add_argument(
        "--target",
        help="Flash target: emmc | ospi-nor | ospi-nand",
    )
    parser.add_argument(
        "--sec",
        default="hs_fs",
        choices=["hs_fs", "hs_se"],          
        help="Security variant (default: hs_fs)",
    )
    parser.add_argument(
        "--cfg-file",
        type=Path,
        help="Path to .cfg file for flash layout",
    )
    parser.add_argument(
        "--list-targets",
        action="store_true",
        help="List available targets for the given board and exit",
    )
    parser.add_argument(
        "--gen-cfg",
        action="store_true",
        help="Generate .cmd + YAML only; do not flash",
    )
    parser.add_argument(
        "--background",
        action="store_true",
        help="Fork to background and log to file",
    )
    return parser.parse_args()


# ─────────────────────────────────────────────
# Main
# ─────────────────────────────────────────────
def main():
    args = parse_args()

    logger = setup_logger(args.board, args.target or "unknown")
    params = load_params(args.board, logger)

    # ── --list-targets ────────────────────────────────────────────────────
    if args.list_targets:
        print(f"\nAvailable targets for board '{args.board}':")
        for t in params["targets"]:
            print(f"  {t}")
        sys.exit(0)

    # ── Require --target ──────────────────────────────────────────────────
    if not args.target:
        logger.error("--target is required (use --list-targets to see options)")
        sys.exit(1)

    if args.target not in params["targets"]:
        logger.error(
            f"Target '{args.target}' not found. "
            f"Available: {list(params['targets'].keys())}"
        )
        sys.exit(1)

    # ── Require --cfg-file ────────────────────────────────────────────────
    if not args.cfg_file:
        logger.error("--cfg-file is required")
        sys.exit(1)

    if not args.cfg_file.exists():
        logger.error(f"CFG file not found: {args.cfg_file}")
        sys.exit(1)

    # ── Background mode ───────────────────────────────────────────────────
    if args.background:
        pid = os.fork()
        if pid > 0:
            print(f"[INFO] Forked to background. PID: {pid}")
            sys.exit(0)

    logger.info(f"Board={args.board}  Target={args.target}  Sec={args.sec}")

    
    # ── Parse CFG file ────────────────────────────────────────────────────
    flash_entries = parse_cfg_file(args.cfg_file, logger, sec=args.sec)
    if not flash_entries:
        logger.error("No flash entries parsed from CFG file — check file format")
        sys.exit(1)

    # ── Generate files ────────────────────────────────────────────────────
    cmd_path  = generate_cmd(
        params, args.board, args.target, args.sec, flash_entries, logger
    )
    yaml_path = generate_snagrecover_yaml(
        params, args.board, args.target, args.sec, flash_entries, logger
    )

    # ── Gen-cfg mode — generate files only, no flashing ──────────────────
    if args.gen_cfg:
        logger.info("Gen-cfg mode: files generated. No flashing performed.")
        logger.info(f"CMD  file : {cmd_path}")
        logger.info(f"YAML file : {yaml_path}")
        sys.exit(0)

    # ── Pre-flight validation ─────────────────────────────────────────────
    validate_firmware(params, flash_entries, logger)

    # ── snagrecover ───────────────────────────────────────────────────────
    run_snagrecover(params, logger)

    # ── Wait for fastboot ─────────────────────────────────────────────────
    vid = params["usb_ids"]["vid"]
    pid = params["usb_ids"]["pid"]
    wait_for_fastboot(vid, pid, logger)

    # ── snagflash ─────────────────────────────────────────────────────────
    run_snagflash(params, cmd_path, logger)

    logger.info("Flash complete!")


if __name__ == "__main__":
    main()