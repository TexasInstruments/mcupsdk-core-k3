#!/usr/bin/env python3
"""
Recreate the legacy Doxygen-build entry point "index.html" inside a built
api_guide_<device> tree.

TIREX packaging (mcupsdk_internal/jenkins/make_package.sh's url-validation
step) and the per-device webgen.mak/*.json asset metadata all hard-code
"exports/docs/api_guide_<device>/index.html" as the documentation entry
point. Sphinx no longer builds anything at that exact path, so generate a
tiny meta-refresh redirect from index.html to device/<device>/main_page.html,
the page users actually land on.

Usage: create_index_redirect.py <device> <outdir>
"""
import os
import sys

REDIRECT_TEMPLATE = """<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta http-equiv="refresh" content="0; url={target}">
<title>MCU+ SDK Documentation</title>
</head>
<body>
<p>Redirecting to <a href="{target}">{target}</a>...</p>
</body>
</html>
"""


def main():
    if len(sys.argv) != 3:
        print(__doc__)
        sys.exit(1)
    device, outdir = sys.argv[1:3]

    build_dir = os.path.join(outdir, f"api_guide_{device}")
    if not os.path.isdir(build_dir):
        return

    if os.path.isfile(os.path.join(build_dir, "index.html")):
        return  # Sphinx already built index.html as the root page

    target = f"device/{device}/main_page.html"
    if not os.path.isfile(os.path.join(build_dir, target)):
        print(f"create_index_redirect: no main_page.html found for {device}, skipping")
        return

    with open(os.path.join(build_dir, "index.html"), "w") as f:
        f.write(REDIRECT_TEMPLATE.format(target=target))
    print(f"create_index_redirect: index.html -> {target} for {device}")


if __name__ == "__main__":
    main()
