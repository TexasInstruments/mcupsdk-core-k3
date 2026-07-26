#!/usr/bin/env python3
"""
Recreate legacy Doxygen anchor-style HTML filenames (EXAMPLES_*.html /
EXAMPLE_*.html) inside a built api_guide_<device> tree.

Example .projectspec files link their CCS "README.html" to these flat,
anchor-named files (e.g. EXAMPLES_COREMARK_PRO.html), one per example page,
named after that page's old Doxygen {#ANCHOR} label. Sphinx builds pages
under their docname path instead (e.g. examples/benchmarks/coremark_pro_benchmark.html),
so this script finds each {#ANCHOR} label in the legacy docs tree and, if the
corresponding Sphinx page was built for this device, writes a tiny
meta-refresh redirect from the flat legacy anchor filename to the real
built page (rather than duplicating its content). Pages a device doesn't
build (excluded/unsupported) are skipped silently -- that mirrors what the
.projectspec would see anyway.

Usage: copy_legacy_anchors.py <mcu_plus_sdk_path> <device> <outdir>
"""
import os
import re
import sys

ANCHOR_RE = re.compile(r"^#{1,3}\s+.*\{#((?:EXAMPLES?)_[A-Z0-9_]+)\}\s*$")

REDIRECT_TEMPLATE = """<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta http-equiv="refresh" content="0; url={target}">
<title>{title}</title>
</head>
<body>
<p>Redirecting to <a href="{target}">{target}</a>...</p>
</body>
</html>
"""


def main():
    if len(sys.argv) != 4:
        print(__doc__)
        sys.exit(1)
    sdk_path, device, outdir = sys.argv[1:4]

    legacy_root = os.path.join(sdk_path, "docs_src", "docs", "api_guide")
    build_dir = os.path.join(outdir, f"api_guide_{device}")
    if not os.path.isdir(build_dir):
        return

    created = 0
    for root, _dirs, files in os.walk(legacy_root):
        for fn in files:
            if not fn.endswith(".md"):
                continue
            path = os.path.join(root, fn)
            with open(path, errors="replace") as f:
                for line in f:
                    m = ANCHOR_RE.match(line.strip())
                    if not m:
                        continue
                    anchor = m.group(1)
                    relpath = os.path.relpath(path, legacy_root)[:-3]
                    target = relpath.replace(os.sep, "/") + ".html"
                    if os.path.isfile(os.path.join(build_dir, target)):
                        dst = os.path.join(build_dir, anchor + ".html")
                        with open(dst, "w") as out:
                            out.write(REDIRECT_TEMPLATE.format(target=target, title=anchor))
                        created += 1
                    break  # only the first anchor per file (the page's own)

    print(f"copy_legacy_anchors: {created} anchor redirect(s) recreated for {device}")


if __name__ == "__main__":
    main()
