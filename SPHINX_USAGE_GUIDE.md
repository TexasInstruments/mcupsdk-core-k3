# Sphinx Documentation System - MCU+ SDK

## Overview

The MCU+ SDK uses **Sphinx** as its primary documentation build system, replacing the previous pure Doxygen HTML pipeline. This is a multi-layered, device-aware documentation system that combines API documentation (from C headers) with user guides and examples.

### Documentation Pipeline

```
┌─────────────────────────────────────────────────────────────┐
│                   SOURCE LAYER                              │
├─────────────────────────────────────────────────────────────┤
│  C API Headers (.h)      │  Markdown Pages  │  Device Config│
│  - Under source/         │  - Under docs/api_guide_sphinx/ │  - includes.cfg
│  - Listed in includes.cfg│  - Pre-converted │  - Doxygen aliases
│                          │    to MyST format│
└──────────┬───────────────┴──────────┬────────┴────────┬──────┘
           │                         │                 │
           ▼                         ▼                 ▼
┌─────────────────────────────────────────────────────────────┐
│                GENERATION LAYER                             │
├─────────────────────────────────────────────────────────────┤
│  Doxygen        │  MyST Parser      │  Sphinx Config        │
│  (XML only)     │  (Markdown)       │  (Per-device setup)   │
│                 │                   │                       │
│  Generates:     │  Parses:          │  Applies:             │
│  - doxygen_xml/ │  - .md files      │  - Device tags        │
│    <device>/xml │  - docs/api_guide_sphinx/        │  - Exclusions         │
└──────────┬──────┴────────┬──────────┴────────┬──────────────┘
           │               │                   │
           └───────────────┼───────────────────┘
                           ▼
┌─────────────────────────────────────────────────────────────┐
│                    SPHINX BUILD                             │
├─────────────────────────────────────────────────────────────┤
│  Breathe: Links Doxygen XML to Sphinx                       │
│  MyST:    Converts Markdown to reStructuredText              │
│  RTD:     Read the Docs theme (HTML output)                 │
│                                                             │
│  Device Selection via DEVICE env var or -t tag             │
└──────────┬──────────────────────────────────────────────────┘
           ▼
┌─────────────────────────────────────────────────────────────┐
│               OUTPUT (HTML)                                 │
├─────────────────────────────────────────────────────────────┤
│  docs/api_guide_am62ax/                                   │
│  docs/api_guide_am62px/                                   │
│  ... (one per supported device)                             │
└─────────────────────────────────────────────────────────────┘
```

---

## Directory Structure

```
docs_src/
├── README.md                       # Build instructions
├── requirements.txt                # Python dependencies
│
├── docs/api_guide_sphinx/          # Sphinx project root (config + MyST source, checked in)
│   ├── Makefile                    # Build targets (sphinx-build commands)
│   ├── conf.py                     # Sphinx config (device-aware)
│   ├── doxygen_am62ax_xml.cfg      # Doxygen config for AM62AX headers
│   ├── doxygen_am62px_xml.cfg      # Doxygen config for AM62PX headers
│   ├── doxygen_am62dx_xml.cfg      # Doxygen config for AM62DX headers
│   ├── doxygen_xml.cfg             # Base Doxygen config (included by device-specific configs)
│   ├── _static/
│   │   └── custom.css              # RTD theme CSS overrides
│   ├── _templates/
│   │
│   ├── getting_started/            # Setup guides
│   ├── developer_guides/           # How-to guides (IPC, bootflow, etc.)
│   ├── components/                 # Component documentation
│   │   ├── drivers/
│   │   ├── board/
│   │   ├── kernel/
│   │   ├── sdl/
│   │   ├── networking/            # AM62PX-only
│   │   └── ...
│   ├── examples/                   # Code examples
│   ├── device/                     # Device-specific main pages
│   │   ├── am62ax/
│   │   ├── am62px/
│   │   └── am62dx/
│   ├── release_notes/              # Per-device release notes
│   ├── sbom/                       # Software bill of materials
│   ├── datasheet/                  # Datasheet references
│   ├── buildsheet/                 # Build configuration docs
│   ├── images/                     # Copied from docs/api_guide/images/ (gitignored)
│   └── doxygen_xml/                # Generated — gitignored
│       ├── am62ax/xml/
│       └── am62px/xml/
│
└── docs/                           # Generated HTML — gitignored
    ├── api_guide_am62ax/
    └── api_guide_am62px/
```

---

## Key Concepts

### 1. Device-Specific Builds

Sphinx builds are controlled by the **`DEVICE`** environment variable and **`-t <tag>`** flag.

**Supported Devices:**
- `am62x`, `am62ax`, `am62px`, `am62dx`, `am62lx`, `am275x`, `am283x`, `j722s`

**Device-to-Tag Mapping (in conf.py):**
```python
_DEVICE_SOC_TAG = {
    "am62x":  "SOC_AM62X",
    "am62ax": "SOC_AM62AX",
    "am62px": "SOC_AM62PX",
    # ... etc
}
```

**Build Command Example (run from `docs_src/docs/api_guide_sphinx/`):**
```bash
DEVICE=am62ax sphinx-build -t SOC_AM62AX -b html . ../../../docs/api_guide_am62ax
```

### 2. Per-Device Configuration (conf.py)

When `DEVICE` is set, `conf.py` automatically:

1. **Sets breathe_default_project** → Points at `doxygen_xml/<device>/xml/`
2. **Loads myst_substitutions** → Parses aliases from Doxygen `.cfg` files (e.g., `{{ VAR_SOC_NAME }}`)
3. **Adds exclude_patterns** → Removes pages for other devices and unsupported components
4. **Adds tags** → Sphinx `only` blocks use `SOC_AM62AX`, `SOC_AM62PX`, etc.

### 3. Conditional Content

Use MyST `{only}` blocks for device-specific sections:

```markdown
:::{only} SOC_AM62PX
This section is AM62PX only (e.g., networking).
:::

:::{only} SOC_AM62AX or SOC_AM62PX
This applies to both AM62AX and AM62PX.
:::
```

In `.rst` format:
```rst
.. only:: SOC_AM62PX

   This section is AM62PX only.
```

### 4. Markdown → MyST Conversion

**preprocess.py** converts Doxygen-flavored Markdown to MyST format:

```bash
cd docs_src/
python3 preprocess.py am62ax am62px    # Convert for specific devices
python3 preprocess.py --all-devices    # Convert for all
```

This script:
- Parses `docs/api_guide/device/<dev>/includes.cfg` chains
- Finds all `.md` files listed in Doxygen configs
- Converts Doxygen syntax (like `\ref`) to MyST syntax (like `[link](ref)`)
- Writes output to `docs_src/docs/api_guide_sphinx/`

### 5. Doxygen Integration (Breathe)

**breathe** links Sphinx to Doxygen API documentation via XML.

**Configuration (conf.py):**
```python
breathe_projects = {
    "am62x":  "/path/to/doxygen_xml/am62x/xml",
    "am62ax": "/path/to/doxygen_xml/am62ax/xml",
    # ...
}
breathe_default_project = os.environ.get("DEVICE", "")
```

**Usage in MyST:**
```markdown
```{doxygenfunction} GPIO_pinWrite
```

**Doxygen Output:**
- XML only (no HTML) — stored in `doxygen_xml/<device>/xml/`
- Configured per-device in `doxygen_am62ax_xml.cfg`, `doxygen_am62px_xml.cfg`

### 6. MyST Extensions

Enabled in conf.py:
- **colon_fence** — Triple-colon syntax for code blocks
- **html_image** — HTML image tags in Markdown
- **substitution** — Template variables like `{{ VAR_SOC_NAME }}`
- **linkify** — Auto-link bare URLs

### 7. Theme & Styling

- **Theme:** `sphinx_rtd_theme` (Read the Docs)
- **CSS:** `_static/custom.css` (RTD theme overrides)
- **Navigation:** Collapsible sidebar via `collapse_navigation: True`
- **Branding:** Sphinx footer and source link hidden (see conf.py)

---

## Building Documentation

### Setup (One-time)

```bash
cd docs_src/docs/api_guide_sphinx/
pip install -r ../../../requirements.txt
make copy-images    # Copies docs/api_guide/images/ → images/
```

### Build All Devices

```bash
make html           # Builds AM62AX and AM62PX
```

Output:
- `docs/api_guide_am62ax/index.html`
- `docs/api_guide_am62px/index.html`

### Build Single Device

```bash
make html-am62ax    # AM62AX only
make html-am62px    # AM62PX only
```

### Doxygen Only (XML, no Sphinx)

```bash
make doxygen-am62ax  # Generate XML only
```

Output: `doxygen_xml/am62ax/xml/`

### Clean

```bash
make clean
```

Removes:
- `doxygen_xml/` (all devices)
- `docs/api_guide_am62ax/`, `docs/api_guide_am62px/`

**Note:** `docs/api_guide_sphinx/` source tree is preserved.

---

## CI/CD Pipeline

### Build-Test Workflow (`.github/workflows/build-test.yml`)

Runs on push/PR to `k3_next`, `k3_next_stage`, `k3_main` branches.

**Per-device jobs** (e.g., `build_am62ax`):
1. Checks out PR
2. Runs `.github/workflows/build-test.sh`
3. Executes: `./build-test.sh --device=am62ax`

**build-test.sh steps:**
1. Builds tests
2. **Generates docs:** `make docs DEVICE=am62ax`
   - Calls Sphinx with device tag
   - Outputs to `docs/api_guide_am62ax/`
3. Checks for Doxygen warnings in `docs_src/docs/api_guide/doxy_warnings_am62ax.txt`

---

## Configuration Deep Dive

### conf.py Key Sections

#### 1. Project Metadata
```python
project = "MCU+ SDK"
author = "Texas Instruments"
release = "11.02.00"
```

#### 2. Extensions
```python
extensions = [
    "myst_parser",      # Markdown support
    "breathe",          # Doxygen integration
    "sphinx.ext.autosectionlabel",  # Auto-link headers
]
```

#### 3. Source & Master Doc
```python
source_suffix = {".rst": "restructuredtext", ".md": "markdown"}
master_doc = "index"  # index.rst is the toctree root
```

#### 4. Device-Aware Configuration
```python
_device = os.environ.get("DEVICE", "").strip().lower()

if _device in _DEVICE_SOC_TAG:
    breathe_default_project = _device
    myst_substitutions = _parse_aliases(_device)  # Parse Doxygen aliases
    tags.add(_DEVICE_SOC_TAG[_device])  # Enable device tag for {only} blocks
```

#### 5. Alias Parsing from Doxygen Config
```python
def _parse_aliases(device: str) -> dict:
    """Parse ALIASES from doxygen.cfg and device includes.cfg"""
    # Returns dict like: {"VAR_SOC_NAME": "AM62AX", ...}
    # Used for {{ VAR_SOC_NAME }} substitutions in Markdown
```

#### 6. Per-Device Exclusions
```python
# Exclude other devices' pages
for _other in [d for d in _ALL_DEVICES if d != _device]:
    exclude_patterns += [f"device/{_other}/**", ...]

# Exclude components not used by this device (e.g., networking is AM62PX-only)
_device_comp_subdirs = _get_device_component_subdirs(_device)
if "networking" not in _device_comp_subdirs:
    exclude_patterns += ["components/networking/**"]
```

#### 7. Toctree Filtering
```python
def _filter_toctree_for_device(app, doctree):
    """Remove {only} blocks that don't match the device tag"""
    # Ensures device-specific toctrees don't create duplicate nav
    # Runs at doctree-read event (after parsing, before build)
```

---

## Common Workflows

### Add a New Page

1. **Create Markdown file** in `docs/api_guide_sphinx/<section>/`
   ```bash
   touch docs_src/docs/api_guide_sphinx/developer_guides/new_guide.md
   ```

2. **Add to toctree** in parent `index.md` or section index
   ```markdown
   ```{toctree}
   :maxdepth: 2
   
   existing_page
   new_guide
   ```
   ```

3. **Build to test**
   ```bash
   make html-am62ax
   open docs/api_guide_am62ax/index.html
   ```

### Add Device-Specific Content

Use MyST `{only}` blocks:

```markdown
# My Feature

General info here.

:::{only} SOC_AM62PX
AM62PX-specific implementation details.
:::

:::{only} SOC_AM62AX
AM62AX-specific implementation details.
:::
```

### Reference Doxygen API

Use breathe directives:

```markdown
```{doxygenfunction} GPIO_pinWrite
:project: am62ax
```

```{doxygentype} GPIO_Config
```

```{doxygenfile} gpio.h
```
```

### Use Template Variables

From Doxygen aliases:

```markdown
This SDK is for {{ VAR_SOC_NAME }}.
Download SysConfig from {{ VAR_SYSCFG_WINDOWS_URL }}.
```

### Add a New Device

1. **Create Doxygen config**
   ```bash
   cp doxygen_am62ax_xml.cfg doxygen_newdev_xml.cfg
   # Edit to list newdev header files
   ```

2. **Update conf.py**
   ```python
   _ALL_DEVICES.append("newdev")
   _DEVICE_SOC_TAG["newdev"] = "SOC_NEWDEV"
   ```

3. **Update Makefile**
   ```makefile
   html-newdev: doxygen-newdev
       DEVICE=newdev $(SPHINX) -t SOC_NEWDEV -b html docs/api_guide_sphinx ...
   ```

4. **Create device pages**
   ```bash
   mkdir -p docs/api_guide_sphinx/device/newdev docs/api_guide_sphinx/release_notes/newdev
   touch docs/api_guide_sphinx/device/newdev/main_page.md
   ```

5. **Build**
   ```bash
   make html-newdev
   ```

---

## Troubleshooting

### Issue: Sphinx can't find Doxygen XML

**Problem:** `breathe: doxygen xml output not found`

**Solution:**
1. Ensure `DEVICE` is set: `export DEVICE=am62ax`
2. Regenerate Doxygen XML: `make doxygen-am62ax`
3. Check path exists: `ls doxygen_xml/am62ax/xml/`

### Issue: Pages not appearing in toctree

**Problem:** Page exists but doesn't show in navigation

**Solution:**
1. Verify it's listed in the toctree (`.rst` or `.md`)
2. Check device exclusions: `grep -r "common_page" docs/api_guide_sphinx/index.rst`
3. If device-specific, ensure `{only}` tag matches your device

### Issue: Doxygen warnings during build

**Problem:** Build succeeds but warnings appear in `doxy_warnings_<device>.txt`

**Solution:**
1. Check file: `cat docs_src/docs/api_guide/doxy_warnings_am62ax.txt`
2. Common issues: missing `\param`, malformed `\ref`, etc.
3. Fix in source header files (under `source/`)
4. Regenerate: `make doxygen-am62ax`

### Issue: Template variables not substituting

**Problem:** Markdown shows `{{ VAR_SOC_NAME }}` literally

**Solution:**
1. Ensure alias is parsed: `python3 preprocess.py am62ax` (regenerates `.md`)
2. Check `.cfg` file has the alias: `grep "VAR_SOC_NAME" docs/api_guide/device/am62ax/includes.cfg`
3. Rebuild Sphinx: `make clean && make html-am62ax`

### Issue: Image not displaying

**Problem:** Image references broken in HTML

**Solution:**
1. Verify image copied: `ls docs/api_guide_sphinx/images/myimage.png`
2. Check Markdown syntax: `![alt](images/myimage.png)` (relative path)
3. Run post-build script: `python3 fix_images.py`

---

## File Relationships

```
Source Code Changes
        ↓
docs/api_guide/*.md (Doxygen-flavored)
        ↓
preprocess.py
        ↓
docs/api_guide_sphinx/*.md (MyST format)
        ↓
Sphinx Build (DEVICE env var)
        ├─→ Doxygen → doxygen_xml/<device>/xml/
        ├─→ MyST Parser → docs/api_guide_sphinx/
        └─→ Breathe → Links them
        ↓
docs/api_guide_<device>/
```

---

## Key Sphinx/MyST Syntax

### reStructuredText (`.rst`)

```rst
Section Title
=============

Subsection
----------

.. toctree::
   :maxdepth: 2

   page1
   page2

.. only:: SOC_AM62AX

   Device-specific content

.. code-block:: c

   int x = 42;

`Link text <https://example.com>`_

:ref:`ref_label`
```

### MyST Markdown

```markdown
# Section Title

## Subsection

```{toctree}
:maxdepth: 2

page1
page2
```

::::{only} SOC_AM62AX

Device-specific content

::::

```c
int x = 42;
```

[Link text](https://example.com)

[](ref_label)
```

---

## Dependencies

### Python Packages (requirements.txt)

| Package | Version | Purpose |
|---------|---------|---------|
| sphinx | ≥7.0 | Core build system |
| myst-parser | ≥2.0 | Markdown support |
| sphinx-rtd-theme | ≥2.0 | Read the Docs theme |
| breathe | ≥4.35 | Doxygen integration |
| linkify-it-py | ≥2.0 | URL auto-linking |

### System Tools

- `sphinx-build` (from sphinx package)
- `doxygen` (C/C++ header documentation)
- `python3` (≥3.9)

---

## Performance Notes

- **Incremental builds:** Sphinx caches unchanged files; only modified pages rebuild.
- **Full clean rebuild:** `make clean && make html-am62ax` (~30-60s for typical devices)
- **Doxygen XML:** Regenerates only if `.h` files change; respects `SOURCE_DATE_EPOCH` for reproducibility.
- **Parallel builds:** Not yet used; sequential per-device is stable.

---

## Future Enhancements

Potential improvements to consider:

1. **Multi-device HTML navigation** — Single build with all devices, client-side device selector
2. **Search indexing** — Enable Sphinx `searchindex.js` generation
3. **Automated versioning** — Per-release subdirectories (e.g., `docs/11.0/`, `docs/11.1/`)
4. **CI/CD output upload** — Publish built HTML to a docs hosting service
5. **Parallel device builds** — Use `make -j` to build multiple devices concurrently

---

## Related Documentation

- **Sphinx Documentation:** https://www.sphinx-doc.org/
- **MyST Parser:** https://myst-parser.readthedocs.io/
- **Breathe:** https://breathe.readthedocs.io/
- **Read the Docs Theme:** https://sphinx-rtd-theme.readthedocs.io/
- **Doxygen Manual:** https://www.doxygen.nl/manual/

---

## Questions or Issues?

Refer to:
- `docs_src/README.md` — Quick build reference
- `docs_src/docs/api_guide_sphinx/conf.py` — Sphinx configuration
- `.github/workflows/build-test.sh` — CI build process
