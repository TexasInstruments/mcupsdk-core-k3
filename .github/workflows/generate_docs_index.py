#
#  Copyright (C) 2026 Texas Instruments Incorporated.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#    Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
#    Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the
#    distribution.
#
#    Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

"""Generate a landing index.html for the GitHub Pages docs site.

Scans the given output directory for per-device subdirectories (each
already containing its own Sphinx-built index.html, courtesy of
docs_src/docs/api_guide_sphinx/create_index_redirect.py) and writes a
top-level index.html linking to each one. Only devices that actually
built (their build job may have failed and been skipped -- see
docs-pages.yml's deploy job) show up; there's no placeholder for a
missing one.

Styled to match the sidebar colors already applied to the per-device
Sphinx docs themselves (TI red header, #404040 body text on white) --
see docs_src/docs/api_guide_sphinx/_static/custom.css.
"""

import base64
import sys
from pathlib import Path

# name -> (display name, chip family) -- chip family text is purely
# cosmetic context for the card, sourced from CLAUDE.md's device table.
DEVICE_INFO = {
    "am62ax": ("AM62Ax", "AM62A3 / AM62A7"),
    "am62px": ("AM62Px", "AM62P"),
    "am62dx": ("AM62Dx", "AM62D-Q1"),
    "am275x": ("AM275x", "AM2754-Q1"),
    "am62x": ("AM62x", "AM623 / AM625"),
    "am62lx": ("AM62Lx", "AM62L"),
}


def main():
    site_dir = Path(sys.argv[1])
    logo_path = Path(sys.argv[2])

    devices = sorted(
        d.name for d in site_dir.iterdir() if d.is_dir() and d.name in DEVICE_INFO
    )
    logo_b64 = base64.b64encode(logo_path.read_bytes()).decode()

    cards = "\n".join(
        f"""      <a class="card" href="{d}/index.html">
        <h2>{DEVICE_INFO[d][0]}</h2>
        <p>{DEVICE_INFO[d][1]}</p>
        <span class="card-link">View documentation &rarr;</span>
      </a>"""
        for d in devices
    )

    (site_dir / "index.html").write_text(f"""<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>MCU+ SDK/ FreeRTOS SDK Documentation</title>
<style>
  body {{
    margin: 0;
    font-family: Lato, "Helvetica Neue", Arial, sans-serif;
    color: #404040;
    background-color: #FCFCFC;
  }}
  .topbar {{
    background-color: #ffffff;
    padding: 20px 40px;
  }}
  .topbar img {{
    height: 32px;
  }}
  .navbar {{
    background-color: #CC0000;
    padding: 16px 40px;
  }}
  .navbar span {{
    color: #ffffff;
    font-size: 15px;
    font-weight: bold;
    letter-spacing: 0.02em;
  }}
  main {{
    max-width: 960px;
    margin: 0 auto;
    padding: 40px 24px;
  }}
  main h1 {{
    font-size: 34px;
    font-weight: bold;
    color: #1a1a1a;
    margin: 0 0 8px 0;
  }}
  main > p {{
    font-size: 17px;
    color: #757575;
    margin-top: 0;
    margin-bottom: 32px;
  }}
  .grid {{
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(220px, 1fr));
    gap: 20px;
    margin-top: 24px;
  }}
  .card {{
    display: block;
    border: 1px solid #e0e0e0;
    border-radius: 6px;
    padding: 20px;
    text-decoration: none;
    color: #404040;
    background-color: #ffffff;
    transition: border-color 0.15s ease, box-shadow 0.15s ease;
  }}
  .card:hover {{
    border-color: #CC0000;
    box-shadow: 0 2px 8px rgba(0, 0, 0, 0.08);
  }}
  .card h2 {{
    margin: 0 0 4px 0;
    font-size: 18px;
    color: #1a1a1a;
  }}
  .card p {{
    margin: 0;
    font-size: 13px;
    color: #757575;
  }}
  .card-link {{
    display: inline-block;
    margin-top: 12px;
    font-size: 13px;
    font-weight: bold;
    color: #CC0000;
  }}
  footer {{
    text-align: center;
    padding: 24px;
    font-size: 12px;
    color: #9a9a9a;
  }}
</style>
</head>
<body>
  <div class="topbar">
    <img src="data:image/png;base64,{logo_b64}" alt="Texas Instruments">
  </div>
  <div class="navbar">
    <span>MCU+ SDK/ FreeRTOS SDK Documentation</span>
  </div>
  <main>
    <h1>MCU+ SDK/ FreeRTOS SDK Documentation</h1>
    <p>FreeRTOS-based software development kit &mdash; select a device below to view its documentation.</p>
    <div class="grid">
{cards}
    </div>
  </main>
  <footer>&copy; 2026 Texas Instruments Incorporated</footer>
</body>
</html>
""")


if __name__ == "__main__":
    main()
