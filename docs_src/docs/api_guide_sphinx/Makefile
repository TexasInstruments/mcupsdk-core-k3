SDK_PATH   = $(abspath ../../..)

# imports.mak defaults DEVICE to am62px (DEVICE ?= am62px) if it isn't already
# defined. Pre-define it as empty (without `override`) so that default doesn't
# silently kick in when DEVICE is omitted on the command line -- a
# command-line DEVICE=<dev> still takes precedence over this, unaffected.
DEVICE :=

# Cross-platform tool macros (MKDIR, RMDIR, RM, COPY, SHELL on Windows, etc.)
# -- same mechanism the legacy doxygen-only makefile (docs_src/docs/api_guide/makefile)
# uses to build on both Windows and Linux.
export MCU_PLUS_SDK_PATH := $(SDK_PATH)
include $(MCU_PLUS_SDK_PATH)/imports.mak

ifeq ($(OS),Windows_NT)
    GREP = $(CYGWIN_PATH)/grep
else
    GREP = grep
endif

PYTHON ?= python3
SPHINX  ?= sphinx-build
DOXYGEN ?= doxygen
OUTDIR     = $(SDK_PATH)/docs
SPHINX_SRC = .

# Ensure DEVICE (when set on the command line) is passed through to
# sub-processes (doxygen, sphinx-build) regardless of host shell.
export DEVICE

# SOC tag map — extend when adding new devices
SOC_TAG_am62ax  = SOC_AM62AX
SOC_TAG_am62px  = SOC_AM62PX
SOC_TAG_am62x   = SOC_AM62X
SOC_TAG_am62dx  = SOC_AM62DX
SOC_TAG_am62lx  = SOC_AM62LX
SOC_TAG_am275x  = SOC_AM275X
SOC_TAG_j722s   = SOC_J722S

# Devices built by the html/all aggregate targets — extend when adding new devices
DEVICES = am62ax am62px am62dx am275x am62x am62lx

.PHONY: docs doxygen-docs copy-images install-requirements copy-legacy-anchors create-index-redirect html all clean help

help:
	@echo "MCU+ SDK documentation targets:"
	@echo ""
	@echo "  docs DEVICE=<dev>          Generate Doxygen XML + Sphinx HTML for <dev>"
	@echo "                              e.g. make docs DEVICE=am62ax"
	@echo ""
	@echo "  html                       Build all Sphinx documentation ($(DEVICES))"
	@echo "  all                        Build all Sphinx documentation"
	@echo ""
	@echo "  doxygen-docs DEVICE=<dev>  Generate Doxygen XML only for <dev>"
	@echo "  copy-images                Copy images from docs/api_guide/images/ to $(SPHINX_SRC)/images/"
	@echo "  install-requirements       Install Python packages needed by Sphinx (requirements.txt)"
	@echo "  copy-legacy-anchors DEVICE=<dev>  Recreate legacy EXAMPLES_*.html anchor filenames"
	@echo "  create-index-redirect DEVICE=<dev>  Recreate legacy index.html entry point"
	@echo "  clean                      Remove doxygen_xml/ and generated HTML"

# Copy images from the source tree into $(SPHINX_SRC)/images/ so Sphinx figure/image
# directives (which resolve relative to $(SPHINX_SRC)/) can find them.
# The legacy Doxygen build additionally searched the enet-lld submodule's own
# internal docs images (via an extra IMAGE_PATH entry) -- Sphinx/MyST has no
# such search mechanism, so copy the whole enet-lld internal images directory
# into images/networking/ alongside the rest, instead of listing individual
# files one by one (new images added to that submodule folder are then picked
# up automatically without a Makefile edit).
# optishare.md's images likewise lived alongside the legacy doc source
# (developer_guides/optishare/*.png) rather than under api_guide/images/, so
# copy them in explicitly too.
copy-images:
	$(RMDIR) $(SPHINX_SRC)/images
	$(COPY) -r $(SDK_PATH)/docs_src/docs/api_guide/images $(SPHINX_SRC)/images
	$(COPY) -r $(SDK_PATH)/source/networking/enet/core/docs/internal/images/. $(SPHINX_SRC)/images/networking/
	$(COPY) $(SDK_PATH)/docs_src/docs/api_guide/developer_guides/optishare/*.png $(SPHINX_SRC)/images/

# Install the Python packages Sphinx needs (sphinx, myst-parser, breathe, etc.)
# Required on CI agents (e.g. Jenkins) that don't already have them; a no-op
# on a machine that's already up to date.
install-requirements:
	$(PYTHON) -m pip install -q -r $(SPHINX_SRC)/requirements.txt

# Generic device target — primary target for building Sphinx documentation
#   make -C docs_src/docs/api_guide_sphinx docs DEVICE=am62ax
# examples_sdl.rst lists SDL MTOG/STOG examples unconditionally, but those
# features have no AM275X/AM62LX/J722S support at all (confirmed against the
# legacy doc source -- no historical mention of those SoCs). Sphinx resolves
# :doc:/:ref: roles (ReferencesResolver, priority 10) before it prunes
# non-matching `.. only::`/`{only}` blocks (OnlyNodeTransform, priority 50),
# so wrapping the reference in `only::` cannot suppress the resulting
# "unknown document" warning -- it is structurally unavoidable without either
# dropping the entries for every device or fabricating fake support content.
# Filtered the same narrow way as doxygen-docs' legacy _PAGE anchors below.
docs: install-requirements copy-images doxygen-docs
	$(if $(DEVICE),,$(error DEVICE is not set. Usage: make docs DEVICE=<device>))
	$(if $(SOC_TAG_$(DEVICE)),,$(error No SOC tag defined for DEVICE=$(DEVICE)))
	$(SPHINX) -j auto -c . -t $(SOC_TAG_$(DEVICE)) -b html $(SPHINX_SRC) $(OUTDIR)/api_guide_$(DEVICE) 2> $(SPHINX_SRC)/.sphinx_raw_$(DEVICE).tmp
	-$(GREP) -Ev "unknown document: 'sdl/(mtog|stog)' \[ref\.doc\]" $(SPHINX_SRC)/.sphinx_raw_$(DEVICE).tmp >> $(SPHINX_SRC)/sphinx_warnings_$(DEVICE).txt
	$(RM) $(SPHINX_SRC)/.sphinx_raw_$(DEVICE).tmp
	$(MAKE) copy-legacy-anchors DEVICE=$(DEVICE)
	$(MAKE) create-index-redirect DEVICE=$(DEVICE)

# Example .projectspec files link their CCS "README.html" to legacy Doxygen
# anchor-style filenames (e.g. EXAMPLES_COREMARK_PRO.html), one per example
# page, generated from that page's old {#ANCHOR} label. Sphinx builds pages
# under their docname path instead (e.g. examples/benchmarks/coremark_pro_benchmark.html),
# so scan the legacy docs tree for {#ANCHOR} labels and recreate each one as a
# flat copy of the real built page. Pages this device doesn't build
# (excluded/unsupported) are skipped silently — that mirrors what the
# .projectspec would see anyway.
copy-legacy-anchors:
	$(if $(DEVICE),,$(error DEVICE is not set. Usage: make copy-legacy-anchors DEVICE=<device>))
	$(PYTHON) $(SPHINX_SRC)/copy_legacy_anchors.py $(SDK_PATH) $(DEVICE) $(OUTDIR)

# TIREX packaging (make_package.sh's url-validation step) and the per-device
# webgen.mak/*.json asset metadata hard-code
# "exports/docs/api_guide_<device>/index.html" as the doc entry point.
# Devices whose master_doc is "index_<device>" (see conf.py) build
# "index_<device>.html" as their root page instead, so recreate index.html
# as a redirect to it.
create-index-redirect:
	$(if $(DEVICE),,$(error DEVICE is not set. Usage: make create-index-redirect DEVICE=<device>))
	$(PYTHON) $(SPHINX_SRC)/create_index_redirect.py $(DEVICE) $(OUTDIR)

# Doxygen-only target (generates XML for API docs)
# Warnings are filtered to drop only \ref failures against legacy \page anchors
# (e.g. DRIVERS_DDR_PAGE) that were intentionally removed during the Sphinx
# migration — all other doc-error warnings (missing/mismatched \param, broken
# \link to real symbols, etc.) are kept so real regressions stay visible.
doxygen-docs: clean
	$(if $(DEVICE),,$(error DEVICE is not set. Usage: make doxygen-docs DEVICE=<device>))
	$(MKDIR) $(SDK_PATH)/docs_src/docs/api_guide_sphinx/doxygen_xml/$(DEVICE)
	$(DOXYGEN) doxygen_$(DEVICE)_xml.cfg 2> $(SPHINX_SRC)/.doxygen_raw_$(DEVICE).tmp
	-$(GREP) -Ev "unable to resolve reference to .*_PAGE. for .ref command" $(SPHINX_SRC)/.doxygen_raw_$(DEVICE).tmp > $(SPHINX_SRC)/sphinx_warnings_$(DEVICE).txt
	$(RM) $(SPHINX_SRC)/.doxygen_raw_$(DEVICE).tmp

# Per-device sub-target (invoked via html's prerequisite list below) instead of
# a shell "for" loop, so this works under cmd.exe on Windows as well as sh/bash.
html: $(addprefix html-,$(DEVICES))

html-%:
	$(MAKE) docs DEVICE=$*

all: html

clean:
	$(if $(DEVICE),,$(error DEVICE is not set. Usage: make clean DEVICE=<device>))
	$(RMDIR) doxygen_xml/$(DEVICE)
	$(RMDIR) $(OUTDIR)/api_guide_$(DEVICE)
