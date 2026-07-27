"""
Sphinx configuration for MCU+ SDK documentation.
Per-device build controlled by DEVICE environment variable.

Usage (run from this directory — config dir and source dir are the same now):
    DEVICE=am62ax sphinx-build -t SOC_AM62AX -b html . ../../../docs/api_guide_am62ax
    DEVICE=am62px sphinx-build -t SOC_AM62PX -b html . ../../../docs/api_guide_am62px
"""

import datetime
import os
import re
from pathlib import Path

# ---------------------------------------------------------------------------
# Project metadata
# ---------------------------------------------------------------------------
project = "MCU+ SDK"
author = "Texas Instruments"
release = "12.01.00"
version = release
copyright = f"{datetime.datetime.now().year} Texas Instruments Incorporated"

# ---------------------------------------------------------------------------
# Extensions
# ---------------------------------------------------------------------------
extensions = [
    "myst_parser",
    "breathe",
    "sphinx.ext.autosectionlabel",
]

# ---------------------------------------------------------------------------
# Source
# ---------------------------------------------------------------------------
source_suffix = {".rst": "restructuredtext", ".md": "markdown"}
master_doc = "index"
templates_path = ["_templates"]

# ---------------------------------------------------------------------------
# HTML theme
# ---------------------------------------------------------------------------
html_theme = "sphinx_rtd_theme"
html_static_path = ["_static"]
html_css_files = ["custom.css"]
html_show_sphinx = False        # hide "Built with Sphinx" footer
html_show_sourcelink = False    # hide "View page source" link
html_logo = "_static/ti_logo.png"
html_theme_options = {
    "collapse_navigation": False,
    "sticky_navigation": True,
    "navigation_depth": 5,
    "titles_only": False,
    "logo_only": False,
}

# ---------------------------------------------------------------------------
# MyST
# ---------------------------------------------------------------------------
myst_enable_extensions = [
    "colon_fence",
    "html_image",
    "substitution",
    "linkify",          # auto-link bare https:// URLs
]
autosectionlabel_prefix_document = True
suppress_warnings = [
    "toc.excluded",
    "myst.xref_missing",
    "myst.substitution",
    "myst.header",          # heading level jumps in source files
    "autosectionlabel",
    "toc.not_readable",
    "toc.secnum",
    "toc.not_numbered",     # documents not included in toctree
    "toc.orphan",           # orphaned documents
    "misc.highlighting_failure",  # code block highlighting
    "",                     # untyped warnings (includes "document isn't included in any toctree" in Sphinx 8.x)
    "app.add_config_value",  # Sphinx 8.x compatibility
]

# ---------------------------------------------------------------------------
# Device/SOC setup
# ---------------------------------------------------------------------------
_ALL_DEVICES = ["am62x", "am62ax", "am62px", "am62dx", "am62lx", "am275x", "j722s"]

_DEVICE_SOC_TAG = {
    "am62x":  "SOC_AM62X",
    "am62ax": "SOC_AM62AX",
    "am62px": "SOC_AM62PX",
    "am62dx": "SOC_AM62DX",
    "am62lx": "SOC_AM62LX",
    "am275x": "SOC_AM275X",
    "j722s":  "SOC_J722S",
}


def _soc_display_name(device: str) -> str:
    """e.g. 'am62px' -> 'AM62Px', 'am62dx' -> 'AM62Dx', 'j722s' -> 'J722S'."""
    name = device.upper()
    if name.endswith("X"):
        name = name[:-1] + "x"
    return name


_sdk_path = Path(__file__).resolve().parent.parent.parent.parent


def _auto_exclude_unsupported_examples(source_dir: str, active_tag: str) -> list:
    """
    Scan example source files and exclude any that contain {only} blocks
    but none of those blocks mention the current device's tag.
    Files with no {only} blocks are universal and kept for all devices.
    Only applied to leaf-level example files where {only} blocks indicate
    the entire example is device-specific (not just a section within it).
    """
    only_re = re.compile(r':{3,}\{only\}\s+([^\n]+)')
    excluded = []
    # Directories where {only} indicates the whole file is device-specific
    _device_scoped_dirs = ['examples', 'components/kernel/os']
    source_path = Path(source_dir)
    for scan_dir in _device_scoped_dirs:
        scan_path = source_path / scan_dir
        if not scan_path.exists():
            continue
        for md_file in sorted(scan_path.rglob('*.md')):
            if md_file.name.startswith('examples_') or md_file.name == 'index.md':
                continue  # skip index/container pages — they're structural, not device-specific leaf files
            # Landing/container pages whose {only} blocks only gate a few
            # extra optional links, not the whole page's applicability —
            # excluding by name here (like examples_*/index.md above) since
            # a generic "has its own toctree" check would also wrongly
            # un-exclude genuinely device-exclusive pages (e.g. sigchain_top.md).
            if str(md_file.relative_to(source_path)) == 'examples/networking/enet_cpsw_tsn_gptp.md':
                continue
            try:
                content = md_file.read_text(errors='replace')
            except Exception:
                continue
            conditions = only_re.findall(content)
            if not conditions:
                continue  # no {only} blocks → universal, keep
            if any(active_tag in cond for cond in conditions):
                continue  # device is supported
            excluded.append(str(md_file.relative_to(source_path)))
    return excluded


def _parse_aliases(device: str) -> dict:
    """
    Parse ALIASES from doxygen.cfg and device includes.cfg.
    Returns a dict suitable for myst_substitutions.
    """
    alias_re = re.compile(r'^ALIASES\s*\+=\s*(\w+)\s*=\s*"(.*)"')
    aliases = {}

    def _parse_file(path):
        try:
            for line in Path(path).read_text(errors="replace").splitlines():
                m = alias_re.match(line.strip())
                if m:
                    # Strip inner Doxygen markup so values are plain text
                    key, val = m.group(1), m.group(2)
                    # Remove \htmlonly ... \endhtmlonly, \note, \ref, etc.
                    val = re.sub(r'\\htmlonly.*?\\endhtmlonly', '', val, flags=re.DOTALL)
                    val = re.sub(r'\\[a-z]+\{[^}]*\}', '', val)
                    val = re.sub(r'\\[a-z]+', '', val)
                    # Unwrap htmllink{url,text} → text
                    val = re.sub(r'<a href="[^"]*">([^<]*)</a>', r'\1', val)
                    aliases[key] = val.strip()
        except FileNotFoundError:
            pass

    _parse_file(_sdk_path / "docs_src" / "docs" / "api_guide_sphinx" / "doxygen_xml.cfg")
    _parse_file(_sdk_path / "docs_src" / "docs" / "api_guide" / "doxygen.cfg")
    _parse_file(
        _sdk_path / "docs_src" / "docs" / "api_guide" / "device" / device / "includes.cfg"
    )
    return aliases


# ---------------------------------------------------------------------------
# breathe: one project per device
# ---------------------------------------------------------------------------
breathe_projects = {
    dev: str(_sdk_path / "docs_src" / "docs" / "api_guide_sphinx" / "doxygen_xml" / dev / "xml")
    for dev in _ALL_DEVICES
}
# Breathe configuration (no suppressions - fix doxygen XML generation instead)

# ---------------------------------------------------------------------------
# Per-device configuration (set via DEVICE env var)
# ---------------------------------------------------------------------------
_device = os.environ.get("DEVICE", "").strip().lower()

# Base exclusions — apply to every device (genuinely orphaned files, referenced
# by no toctree anywhere in the tree; not device-specific).
_BASE_EXCLUDE_PATTERNS = [
    # Exclude legacy api_guide structure (not used in Sphinx builds)
    "_build",
    "api_guide/**",
    # Exclude orphaned reference files not included in any toctree
    "getting_started/application_launch.md",
    "examples/drivers/sbl_emmc_linux.md",
    "examples/drivers/sbl_ospi_linux.md",
    "examples/drivers/sbl_ospi_nand_linux.md",
    "examples/drivers/spinlock_demo.md",
]

# Per-device exclusions — on top of _BASE_EXCLUDE_PATTERNS, plus the dynamic
# other-device-dir / unused-component-subdir exclusions computed below.
_EXCLUDE_BY_DEVICE = {
    "am62ax": [
        "components/board/hyperram.md",
        "components/board/ioexp_tca6424.md",
        "components/board/panel.md",
        "components/board/pmic.md",
        "components/drivers/aasrc.md",
        "components/drivers/adc.md",
        "components/drivers/dss.md",
        "components/drivers/fvid2.md",
        "components/drivers/gpmc.md",
        "components/networking/enet_cpsw_tsn_architecture_guide.md",
        "components/networking/enet_cpsw_tsn_developer_guide.md",
        "components/networking/enet_cpsw_tsn_landing_page.md",
        "components/networking/networking_ethfw.md",
        "components/networking/networking_features.md",
        "components/optiflash/optiflash.md",
        "components/signal_processing/calcratio.md",
        "components/signal_processing/signal_processing.rst",
        "developer_guides/add_smart_placement_sections.md",
        "developer_guides/amp_freertos.md",
        "developer_guides/atf_integration.md",
        "developer_guides/boot_benchmark.md",
        "developer_guides/bootflow_xip.md",
        "developer_guides/custom_flash.md",
        "developer_guides/fast_xspi.md",
        "developer_guides/instrumented_application_special_section.md",
        "developer_guides/mcelf_landing_page.md",
        "developer_guides/optiflash_configuration.md",
        "developer_guides/optishare/optishare.md",
        "developer_guides/smp_freertos_guide.md",
        "examples/examples_benchmark.rst",
        "examples/examples_networking_avb.rst",
        "examples/examples_signal_processing.rst",
        "examples/networking/enet_cpsw_tsn_est_example.md",
        "examples/networking/enet_cpsw_tsn_gptp.md",
        "examples/signal_processing/calcratio.md",
        "examples/signal_processing/sigchain_8ch_to_12ch_audio_chain.md",
        "examples/signal_processing/sigchain_biquad_cascade.md",
        "examples/signal_processing/sigchain_biquad_linux_example.md",
        "examples/signal_processing/sigchain_eq_gain_mute.md",
        "examples/signal_processing/sigchain_router_8ch_12ch.md",
        "examples/signal_processing/sigchain_top.md",
        "examples/signal_processing/swasrc_multichannel_playback.md",
        "getting_started/getting_started_smart_placement.md",
    ],
    "am62px": [
        "components/board/hyperram.md",
        "components/board/ioexp_tca6424.md",
        "components/drivers/aasrc.md",
        "components/drivers/adc.md",
        "components/drivers/eqep.md",
        "components/drivers/gpmc.md",
        "components/drivers/gtc.md",
        "components/fs/freertos_fat.md",
        "components/fs/fs.rst",
        "components/kernel/dpl/MmuP_arm_v8.md",
        "components/networking/enet_cpsw_avtp_apiguide.md",
        "components/networking/enet_cpsw_lldp_apiguide.md",
        "components/optiflash/optiflash.md",
        "components/signal_processing/calcratio.md",
        "components/signal_processing/signal_processing.rst",
        "developer_guides/add_smart_placement_sections.md",
        "developer_guides/amp_freertos.md",
        "developer_guides/atf_integration.md",
        "developer_guides/boot_benchmark.md",
        "developer_guides/bootflow_xip.md",
        "developer_guides/fast_xspi.md",
        "developer_guides/instrumented_application_special_section.md",
        "developer_guides/mcelf_landing_page.md",
        "developer_guides/optiflash_configuration.md",
        "developer_guides/optishare/optishare.md",
        "developer_guides/smp_freertos_guide.md",
        "examples/dmautils/dmautils_autoinc_1d2d3d.md",
        "examples/dmautils/dmautils_autoinc_circular.md",
        "examples/dmautils/dmautils_autoinc_compression.md",
        "examples/dmautils/dmautils_autoincrement.md",
        "examples/drivers/mcasp_playback_codec_aic31.md",
        "examples/examples_benchmark.rst",
        "examples/examples_dmautils.rst",
        "examples/examples_networking_avb.rst",
        "examples/examples_signal_processing.rst",
        "examples/signal_processing/calcratio.md",
        "examples/signal_processing/sigchain_8ch_to_12ch_audio_chain.md",
        "examples/signal_processing/sigchain_biquad_cascade.md",
        "examples/signal_processing/sigchain_biquad_linux_example.md",
        "examples/signal_processing/sigchain_eq_gain_mute.md",
        "examples/signal_processing/sigchain_router_8ch_12ch.md",
        "examples/signal_processing/sigchain_top.md",
        "examples/signal_processing/swasrc_multichannel_playback.md",
        "getting_started/getting_started_smart_placement.md",
    ],
    "am62dx": [
        "components/board/hyperram.md",
        "components/board/ioexp_tca6424.md",
        "components/drivers/aasrc.md",
        "components/drivers/adc.md",
        "components/drivers/dss.md",
        "components/drivers/fvid2.md",
        "components/drivers/gpmc.md",
        "components/optiflash/optiflash.md",
        "components/safety_checkers/safety_app.md",
        "components/safety_checkers/safety_checkers.md",
        "components/safety_checkers/safety_checkers.rst",
        "components/safety_checkers/safety_checkers_pm.md",
        "components/safety_checkers/safety_checkers_rm.md",
        "components/safety_checkers/safety_checkers_tifs.md",
        "developer_guides/add_smart_placement_sections.md",
        "developer_guides/amp_freertos.md",
        "developer_guides/atf_integration.md",
        "developer_guides/bootflow_xip.md",
        "developer_guides/fast_xspi.md",
        "developer_guides/graceful_remotecore_shutdown.md",
        "developer_guides/instrumented_application_special_section.md",
        "developer_guides/low_power_mode_aware_remotecore.md",
        "developer_guides/mcelf_landing_page.md",
        "developer_guides/optiflash_configuration.md",
        "developer_guides/optishare/optishare.md",
        "developer_guides/sysfw_pll_update.md",
        "examples/examples_benchmark.rst",
        "examples/examples_otp.rst",
        "examples/examples_safety_checkers.rst",
        "getting_started/getting_started_smart_placement.md",
    ],
    "am62lx": [
        "components/board/eeprom.md",
        "components/board/hyperram.md",
        "components/board/ioexp_tca6424.md",
        "components/board/pmic.md",
        "components/drivers/aasrc.md",
        "components/drivers/ddr.md",
        "components/drivers/gpmc.md",
        "components/drivers/gtc.md",
        "components/networking/networking_ethfw.md",
        "components/optiflash/optiflash.md",
        "components/safety_checkers/safety_app.md",
        "components/safety_checkers/safety_checkers.md",
        "components/safety_checkers/safety_checkers.rst",
        "components/safety_checkers/safety_checkers_pm.md",
        "components/safety_checkers/safety_checkers_rm.md",
        "components/safety_checkers/safety_checkers_tifs.md",
        "components/sdl/dcc.md",
        "components/sdl/ecc.md",
        "components/sdl/esm.md",
        "components/sdl/lbist.md",
        "components/sdl/mcrc.md",
        "components/sdl/mtog.md",
        "components/sdl/pbist.md",
        "components/sdl/pok.md",
        "components/sdl/rom_checksum.md",
        "components/sdl/rti.md",
        "components/sdl/sdl.rst",
        "components/sdl/sdl_dpl.md",
        "components/sdl/stog.md",
        "components/sdl/vtm.md",
        "components/signal_processing/calcratio.md",
        "components/signal_processing/signal_processing.rst",
        "developer_guides/add_smart_placement_sections.md",
        "developer_guides/appimage_sw_version.md",
        "developer_guides/boot_benchmark.md",
        "developer_guides/bootflow_xip.md",
        "developer_guides/ccs_rov.md",
        "developer_guides/custom_flash.md",
        "developer_guides/develop_dmr5_applications.md",
        "developer_guides/fast_xspi.md",
        "developer_guides/graceful_remotecore_shutdown.md",
        "developer_guides/instrumented_application_special_section.md",
        "developer_guides/ipc.md",
        "developer_guides/low_power_mode_aware_remotecore.md",
        "developer_guides/main_domain_peripheral_access.md",
        "developer_guides/mcelf_landing_page.md",
        "developer_guides/mcu_reset_isolation.md",
        "developer_guides/memorymap.md",
        "developer_guides/optiflash_configuration.md",
        "developer_guides/optishare/optishare.md",
        "developer_guides/resource_allocation.md",
        "developer_guides/secure_boot.md",
        "developer_guides/smp_freertos_guide.md",
        "developer_guides/sysfw_pll_update.md",
        "examples/dmautils/dmautils_autoinc_1d2d3d.md",
        "examples/dmautils/dmautils_autoinc_circular.md",
        "examples/dmautils/dmautils_autoinc_compression.md",
        "examples/dmautils/dmautils_autoincrement.md",
        "examples/drivers/fwl_isolation.md",
        "examples/drivers/mcu_bist_result.md",
        "examples/drivers/reset_isolation.md",
        "examples/drivers/sbl_null.md",
        "examples/drivers/sbl_ospi_linux_multistage.md",
        "examples/drivers/sbl_sd.md",
        "examples/drivers/sbl_uart.md",
        "examples/examples_dmautils.rst",
        "examples/examples_drivers_sbl.rst",
        "examples/examples_hello_world_cpp.md",
        "examples/examples_lpm.rst",
        "examples/examples_networking_avb.rst",
        "examples/examples_otp.rst",
        "examples/examples_safety_checkers.rst",
        "examples/examples_sdl.rst",
        "examples/examples_security.rst",
        "examples/examples_signal_processing.rst",
        "examples/sdl/ecc_tcm.md",
        "examples/signal_processing/calcratio.md",
        "examples/signal_processing/sigchain_8ch_to_12ch_audio_chain.md",
        "examples/signal_processing/sigchain_biquad_cascade.md",
        "examples/signal_processing/sigchain_biquad_linux_example.md",
        "examples/signal_processing/sigchain_eq_gain_mute.md",
        "examples/signal_processing/sigchain_router_8ch_12ch.md",
        "examples/signal_processing/sigchain_top.md",
        "examples/signal_processing/swasrc_multichannel_playback.md",
    ],
    "am275x": [
        "components/board/panel.md",
        "components/drivers/ddr.md",
        "components/drivers/dss.md",
        "components/drivers/eqep.md",
        "components/drivers/fvid2.md",
        "components/drivers/gpmc.md",
        "components/networking/networking_ethfw.md",
        "components/safety_checkers/safety_app.md",
        "components/safety_checkers/safety_checkers.md",
        "components/safety_checkers/safety_checkers.rst",
        "components/safety_checkers/safety_checkers_pm.md",
        "components/safety_checkers/safety_checkers_rm.md",
        "components/safety_checkers/safety_checkers_tifs.md",
        "components/sdl/mtog.md",
        "components/sdl/stog.md",
        "developer_guides/amp_freertos.md",
        "developer_guides/atf_integration.md",
        "developer_guides/boot_benchmark.md",
        "developer_guides/ccs_cloud_intro.md",
        "developer_guides/develop_dmr5_applications.md",
        "developer_guides/graceful_remotecore_shutdown.md",
        "developer_guides/low_power_mode_aware_remotecore.md",
        "developer_guides/main_domain_peripheral_access.md",
        "developer_guides/mcu_reset_isolation.md",
        "developer_guides/memorymap.md",
        "developer_guides/secure_boot.md",
        "developer_guides/smp_freertos_guide.md",
        "developer_guides/sysfw_pll_update.md",
        "examples/dmautils/dmautils_autoinc_compression.md",
        "examples/drivers/fwl_isolation.md",
        "examples/drivers/mcu_bist_result.md",
        "examples/drivers/reset_isolation.md",
        "examples/examples_safety_checkers.rst",
        "examples/signal_processing/sigchain_biquad_linux_example.md",
    ],
    "j722s": [
        "examples/dmautils/dmautils_autoinc_1d2d3d.md",
        "examples/dmautils/dmautils_autoinc_circular.md",
        "examples/dmautils/dmautils_autoinc_compression.md",
        "examples/dmautils/dmautils_autoincrement.md",
        "examples/examples_dmautils.rst",
        "examples/examples_signal_processing.rst",
        "examples/signal_processing/calcratio.md",
        "examples/signal_processing/sigchain_8ch_to_12ch_audio_chain.md",
        "examples/signal_processing/sigchain_biquad_cascade.md",
        "examples/signal_processing/sigchain_biquad_linux_example.md",
        "examples/signal_processing/sigchain_eq_gain_mute.md",
        "examples/signal_processing/sigchain_router_8ch_12ch.md",
        "examples/signal_processing/sigchain_top.md",
        "examples/signal_processing/swasrc_multichannel_playback.md",
    ],
    "am62x": [
        "components/board/eeprom.md",
        "components/board/hyperram.md",
        "components/board/ioexp_tca6424.md",
        "components/board/pmic.md",
        "components/drivers/aasrc.md",
        "components/drivers/adc.md",
        "components/drivers/gtc.md",
        "components/networking/enet_cpsw_avtp_apiguide.md",
        "components/networking/enet_cpsw_lldp_apiguide.md",
        "components/networking/networking_ethfw.md",
        "components/optiflash/optiflash.md",
        "components/signal_processing/calcratio.md",
        "components/signal_processing/signal_processing.rst",
        "developer_guides/add_smart_placement_sections.md",
        "developer_guides/boot_benchmark.md",
        "developer_guides/bootflow_xip.md",
        "developer_guides/ccs_rov.md",
        "developer_guides/fast_xspi.md",
        "developer_guides/instrumented_application_special_section.md",
        "developer_guides/mcelf_landing_page.md",
        "developer_guides/optiflash_configuration.md",
        "developer_guides/optishare/optishare.md",
        "examples/dmautils/dmautils_autoinc_1d2d3d.md",
        "examples/dmautils/dmautils_autoinc_circular.md",
        "examples/dmautils/dmautils_autoinc_compression.md",
        "examples/dmautils/dmautils_autoincrement.md",
        "examples/drivers/fwl_isolation.md",
        "examples/examples_dmautils.rst",
        "examples/examples_networking_avb.rst",
        "examples/examples_signal_processing.rst",
        "examples/signal_processing/calcratio.md",
        "examples/signal_processing/sigchain_8ch_to_12ch_audio_chain.md",
        "examples/signal_processing/sigchain_biquad_cascade.md",
        "examples/signal_processing/sigchain_biquad_linux_example.md",
        "examples/signal_processing/sigchain_eq_gain_mute.md",
        "examples/signal_processing/sigchain_router_8ch_12ch.md",
        "examples/signal_processing/sigchain_top.md",
        "examples/signal_processing/swasrc_multichannel_playback.md",
    ],
}


def _get_device_component_subdirs(device: str) -> tuple:
    """
    Scan the device's includes.cfg chain and return the sets of
    components/<subdir> and examples/<subdir> paths actually referenced.
    Returns (components_subdirs, examples_subdirs), e.g.
    ({"networking", "security", "sdl", ...}, {"networking", "drivers", ...}).
    """
    api_guide = _sdk_path / "docs_src" / "docs" / "api_guide"
    cfg = api_guide / "device" / device / "includes.cfg"
    subdirs: set = set()
    examples_subdirs: set = set()
    visited: set = set()

    def _scan(p: Path):
        if not p.exists() or str(p) in visited:
            return
        visited.add(str(p))
        try:
            for line in p.read_text(errors="replace").splitlines():
                line = line.strip()
                if m := re.match(r'(?:INPUT\s*\+?=|@INCLUDE\s*=)\s*(.+)', line):
                    val = (m.group(1).strip()
                           .replace("$(MCU_PLUS_SDK_PATH)", str(_sdk_path))
                           .replace("$(DEVICE)", device))
                    fp = Path(val)
                    try:
                        rel = fp.resolve().relative_to(api_guide.resolve())
                        parts = rel.parts
                        # Collect components/<subdir> and examples/<subdir>
                        if len(parts) >= 2 and parts[0] == "components":
                            subdirs.add(parts[1])
                        elif len(parts) >= 2 and parts[0] == "examples":
                            examples_subdirs.add(parts[1])
                    except ValueError:
                        pass
                    if val.endswith(".cfg") and Path(val).exists():
                        _scan(Path(val))
        except Exception:
            pass

    _scan(cfg)
    return subdirs, examples_subdirs


# Pages that exist only for AM275X (converted from AM275X's Doxygen chain).
# They are referenced from shared container pages via {only} SOC_AM275X blocks,
# but colon-fence {only} does not reliably drop nested toctrees for other
# devices, so exclude these explicitly for every non-AM275X device.
_AM275X_ONLY_PAGES = [
    "components/drivers/hyperbus.md",
    "components/drivers/spinlock.md",
    "components/optiflash/optiflash.md",
    "components/networking/enet_lld/enet_cpsw_performance_am275x.md",
    "components/networking/enet_lld/eavb_performance.md",
    "components/tools/smart_placement.md",
    "components/tools/manual_smart_placement.md",
    "components/tools/sw_instrument_smart_placement.md",
    "developer_guides/bootflow_xip.md",
    "developer_guides/fast_xspi.md",
    "developer_guides/mcelf_landing_page.md",
    "developer_guides/add_smart_placement_sections.md",
    "developer_guides/instrumented_application_special_section.md",
    "developer_guides/optishare/optishare.md",
    "examples/example_basic_smart_placement.md",
    "examples/benchmarks/memory_latency_benchmark.md",
    "examples/benchmarks/xip_benchmark.md",
    "examples/benchmarks/benchmark_smart_placement.md",
    "examples/kernel/test_data_abort.md",
    "examples/kernel/test_prefetch_abort.md",
    "examples/kernel/test_undefined_abort.md",
    "examples/lpm/lpm_io_retention_mcan_wakeup.md",
    "examples/drivers/hyper_ram_ecc_test.md",
    "examples/drivers/hyper_ram_ecc_esm_test.md",
    "examples/drivers/hyper_ram_read_write.md",
    "examples/drivers/ipc_notify_echo_optishare.md",
    "examples/drivers/sbl_jtag_uniflash.md",
    "examples/drivers/sbl_eth_uniflash.md",
    "examples/drivers/sbl_uart_uniflash.md",
    "examples/networking/enet_cpsw_avb_audio_etherring_demo.md",
    "examples/networking/enet_cpsw_avb_audio_playback.md",
    "examples/networking/enet_cpsw_tsn_media_clock_recovery.md",
]

_AM62X_ONLY_PAGES = [
    "developer_guides/sbl_booting_linux_gpmc.md",
    "examples/drivers/ddr_ecc_test_mcu_esm.md",
    "components/networking/enet_lld/enet_cpsw_performance_am62x.md",
]

_AM62DX_ONLY_PAGES = [
    "components/networking/enet_lld/enet_cpsw_performance_am62dx.md",
]

_AM62LX_ONLY_PAGES = [
    "components/networking/enet_lld/enet_cpsw_performance_am62lx.md",
]

_AM62PX_ONLY_PAGES = [
    "components/networking/enet_lld/enet_cpsw_performance_am62px.md",
]

exclude_patterns = list(_BASE_EXCLUDE_PATTERNS)
if _device != "am275x":
    exclude_patterns += _AM275X_ONLY_PAGES
if _device != "am62x":
    exclude_patterns += _AM62X_ONLY_PAGES
if _device != "am62dx":
    exclude_patterns += _AM62DX_ONLY_PAGES
if _device != "am62lx":
    exclude_patterns += _AM62LX_ONLY_PAGES
if _device != "am62px":
    exclude_patterns += _AM62PX_ONLY_PAGES

if _device in _DEVICE_SOC_TAG:
    breathe_default_project = _device
    myst_substitutions = _parse_aliases(_device)
    tags.add(_DEVICE_SOC_TAG[_device])  # noqa: F821 (injected by Sphinx)
    project = f"{myst_substitutions.get('VAR_SDK_NAME', 'FreeRTOS SDK')} for {_soc_display_name(_device)}"

    # Computed URL substitutions (used where {{ VAR }} can't appear inside href)
    _syscfg_ver = myst_substitutions.get("VAR_SYSCFG_VERSION_FULL", "")
    _c7k_ver    = myst_substitutions.get("VAR_TI_C7000_CGT_VERSION", "")
    _clang_ver  = myst_substitutions.get("VAR_TI_ARM_CLANG_VERSION", "")
    myst_substitutions["VAR_SYSCFG_WINDOWS_URL"] = (
        f"https://software-dl.ti.com/ccs/esd/sysconfig/sysconfig-{_syscfg_ver}-setup.exe"
    )
    myst_substitutions["VAR_SYSCFG_LINUX_URL"] = (
        f"https://software-dl.ti.com/ccs/esd/sysconfig/sysconfig-{_syscfg_ver}-setup.run"
    )
    myst_substitutions["VAR_C7000_CGT_URL"] = (
        f"https://www.ti.com/tool/download/C7000-CGT/{_c7k_ver}"
    )
    myst_substitutions["VAR_TI_ARM_CLANG_URL"] = (
        "https://www.ti.com/tool/download/ARM-CGT-CLANG/"
    )

    # RST files go through docutils' own parser and never see MyST's
    # {{ VAR }} substitution syntax — bridge the same values via docutils'
    # native |VAR| substitution mechanism for plain .rst source files.
    rst_prolog = "\n".join(
        f".. |{_k}| replace:: {_v}" for _k, _v in myst_substitutions.items()
        if str(_v).strip() and "\n" not in str(_v)
    )

    # Per-device static exclusions
    exclude_patterns += _EXCLUDE_BY_DEVICE.get(_device, [])

    # Exclude per-device subdirs that belong to other devices
    for _other in [d for d in _ALL_DEVICES if d != _device]:
        exclude_patterns += [
            f"device/{_other}/**",
            f"release_notes/{_other}/**",
            f"sbom/sbom_{_other}.md",
            f"sbom/sbom_{_other}.md",
            f"buildsheet/buildsheet_{_other}.md",
            f"datasheet/datasheet_{_other}_evm.md",
        ]

    # index.md's per-device toctrees are split into index_<device>.md so that
    # a device's toctree entries (which reference device/<device>/main_page,
    # release_notes/<device>/index, etc.) are never parsed for other devices —
    # avoids "toctree contains reference to excluded document" [toc.excluded]
    # warnings, since {only} blocks don't stop a nested toctree directive from
    # being parsed/validated at read time.
    _INDEX_SPLIT_DEVICES = ["am62ax", "am62px", "am62dx", "am275x", "am62x", "am62lx"]
    if _device in _INDEX_SPLIT_DEVICES:
        master_doc = f"index_{_device}"
        exclude_patterns += ["index.rst"]
        for _other in [d for d in _INDEX_SPLIT_DEVICES if d != _device]:
            exclude_patterns += [
                f"index_{_other}.md",
                f"getting_started/getting_started_{_other}.md",
                f"getting_started/{_other}_evm_setup.md",
            ]
    else:
        exclude_patterns += [f"index_{d}.md" for d in _INDEX_SPLIT_DEVICES]

    # Exclude component dirs not used by this device
    # (e.g. networking components are not used by every device)
    _device_comp_subdirs, _device_examples_subdirs = _get_device_component_subdirs(_device)
    _POSSIBLE_COMPONENT_SUBDIRS = [
        "networking",
    ]
    for _compdir in _POSSIBLE_COMPONENT_SUBDIRS:
        if _compdir not in _device_comp_subdirs:
            exclude_patterns += [f"components/{_compdir}/**"]
            # Only blanket-exclude the examples/<subdir> tree too if this
            # device's own examples.cfg chain doesn't reference it either
            # (e.g. am62ax has no components/networking/* API docs, but
            # still has examples/networking/ethfw_server_and_client.md).
            if _compdir not in _device_examples_subdirs:
                exclude_patterns += [f"examples/{_compdir}/**"]

    # Generically exclude example pages that have no content for this device.
    # Scans {only} conditions in each file — no device names hardcoded here.
    exclude_patterns += _auto_exclude_unsupported_examples(
        str(Path(__file__).parent), _DEVICE_SOC_TAG[_device]
    )

else:
    breathe_default_project = ""
    myst_substitutions = {}


# ---------------------------------------------------------------------------
# Event handlers for filtering toctrees based on device tags
# ---------------------------------------------------------------------------
def _filter_toctree_for_device(app, doctree):
    """
    Remove 'only' directive nodes that don't match the current device tag.
    This ensures that device-specific toctrees don't create duplicate navigation.
    doctree-read event receives (app, doctree), not (app, doctree, docname)
    """
    from sphinx.addnodes import only

    device = os.environ.get("DEVICE", "").strip().lower()
    if device not in _DEVICE_SOC_TAG:
        return

    # Find all 'only' nodes in the doctree (before they're processed)
    only_nodes = list(doctree.traverse(only))

    for node in only_nodes:
        expr = node['expr']
        # Evaluate the {only} expression the same way Sphinx's own only-node
        # resolution does (supports and/or/not). A naive substring check on
        # the active tag mishandles "not SOC_XXX" conditions, e.g. for device
        # tag SOC_AM62X, "not SOC_AM62DX" does not contain "SOC_AM62X" as a
        # substring even though the condition is true and should be kept.
        try:
            keep = app.tags.eval_condition(expr)
        except Exception:
            continue
        if not keep:
            node.parent.remove(node)


def setup(app):
    """Register event handlers."""
    # Use doctree-read which fires after parsing but before toctree collection
    app.connect('doctree-read', _filter_toctree_for_device)
    app.connect('html-page-context', _remove_secondary_toc_for_dpl_pages)


def _remove_secondary_toc_for_dpl_pages(app, pagename, templatename, context, doctree):
    """
    Remove secondary TOC for DPL module pages and networking pages to hide
    internal heading hierarchy from the sidebar.
    """
    no_local_toc = {
        'components/kernel/dpl/HwiP',
        'components/kernel/dpl/SemaphoreP',
        'components/kernel/dpl/TaskP',
        'components/kernel/dpl/ClockP',
        'components/kernel/dpl/CycleCountP',
        'components/kernel/dpl/QueueP',
        'components/kernel/dpl/HeapP',
        'components/kernel/dpl/DebugP',
        'components/kernel/dpl/EventP',
        'components/kernel/dpl/TimerP',
        'components/kernel/dpl/CacheP',
        'components/kernel/dpl/CpuIdP',
        'components/kernel/dpl/MpuP_arm_v7',
        'components/kernel/dpl/MmuP_arm_v8',
        'components/kernel/dpl/AddrTranslateP',
        # Networking pages — prevent in-page section headings from appearing
        # as sidebar sub-items when these pages are active
        'components/networking/networking',
        'components/networking/networking_lwip',
        'components/networking/enet_cpsw_tsn_gptp_apiguide',
        'components/networking/enet_lld/enet_lld_top',
        'examples/networking/enet_cpsw_tsn_gptp',
    }
    if pagename in no_local_toc:
        context['display_toc'] = False
