MCU_PLUS_SDK_PATH ?= $(abspath .)
include imports.mak

# Default device
DEVICE?=am62px

# debug, release
PROFILE?=release

# yes = build fftlib/mathlib/vxlib/dsplib/audiolib/tisp and their examples
BUILD_XLIBS ?= no

# GP, HS, HS_FS
ifeq ($(DEVICE),$(filter $(DEVICE), j722s))
DEVICE_TYPE?=HS_FS
else
DEVICE_TYPE?=GP
endif

ifeq ($(DEVICE),$(filter $(DEVICE), am62x))
  SYSCFG_DEVICE = AM62x
  SYSCFG_DEVICE_VARIANT = Default
  SYSCFG_DEVICE_PACKAGE = ALW
  # default syscfg CPU to use,
  # options on am62x are m4fss0-0
  SYSCFG_CPU = m4fss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am62ax))
  SYSCFG_DEVICE = AM62Ax
  SYSCFG_DEVICE_VARIANT = Default
  SYSCFG_DEVICE_PACKAGE = AMB
  # default syscfg CPU to use,
  # options on am62x are m4fss0-0
  SYSCFG_CPU = r5fss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am62px))
  SYSCFG_DEVICE = AM62Px
  SYSCFG_DEVICE_VARIANT = Default
  SYSCFG_DEVICE_PACKAGE = AMH
  # default syscfg CPU to use,
  # options on am62ax are wkup-r5fss0-0, mcu-r5fss0-0
  SYSCFG_CPU = mcu-r5fss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am62dx))
  SYSCFG_DEVICE = AM62Dx
  SYSCFG_DEVICE_VARIANT = AM62D24-G
  SYSCFG_DEVICE_PACKAGE = ANF
  # default syscfg CPU to use,
  # options on am62dx are mcu-r5fss0-0, r5fss0-0, c75ss0-0, a53ss0-0
  SYSCFG_CPU = mcu-r5fss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am275x))
  SYSCFG_DEVICE = AM275x
  SYSCFG_DEVICE_VARIANT = AM2754
  SYSCFG_DEVICE_PACKAGE = ANJ
  # default syscfg CPU to use,
  # options on am275x are wkup-r5fss0-0, r5fss0-1, r5fss1-0, r5fss1-1, c75ss0-0, c75ss1-0
  SYSCFG_CPU = r5fss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am62lx))
  SYSCFG_DEVICE = AM62L
  SYSCFG_DEVICE_VARIANT = AM62L32-G-ANB
  SYSCFG_DEVICE_PACKAGE = ANB
  # default syscfg CPU to use,
  # options on am62lx are a53ss0-0
  SYSCFG_CPU = a53ss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), j722s))
  SYSCFG_DEVICE = AM67
  SYSCFG_DEVICE_VARIANT = Default
  SYSCFG_DEVICE_PACKAGE = AMW
  # Default syscfg CPU to use, out of the following core options on j722s:
  # main-r5fss0-0, mcu-r5fss0-0, wkup-r5fss0-0, c75ss0-0, c75ss1-0,
  # a53ss0-0, a53ss0-1, a53ss1-0, a53ss1-1, hsm0-0
  SYSCFG_CPU = mcu-r5fss0-0
endif

all:
	$(MAKE) -C . -f makefile.$(DEVICE) all PROFILE=$(PROFILE)

clean:
	$(MAKE) -C . -f makefile.$(DEVICE) clean PROFILE=$(PROFILE)

scrub:
	$(MAKE) -C . -f makefile.$(DEVICE) scrub PROFILE=$(PROFILE)

ifeq ($(DEVICE),$(filter $(DEVICE), am62x am62ax am62dx am62px am275x))
hsm:
	$(MAKE) -C . -f makefile.$(DEVICE) hsm PROFILE=$(PROFILE)

hsm-clean:
	$(MAKE) -C . -f makefile.$(DEVICE) hsm-clean PROFILE=$(PROFILE)

hsm-scrub:
	$(MAKE) -C . -f makefile.$(DEVICE) hsm-scrub PROFILE=$(PROFILE)
endif

ifeq ($(DEVICE),$(filter $(DEVICE), am62x am62ax am62px))
linux: 
	$(MAKE) -C . -f makefile.$(DEVICE) linux PROFILE=$(PROFILE)

linux-clean: 
	$(MAKE) -C . -f makefile.$(DEVICE) linux-clean PROFILE=$(PROFILE)

linux-scrub: 
	$(MAKE) -C . -f makefile.$(DEVICE) linux-scrub PROFILE=$(PROFILE)
endif

libs:
	$(MAKE) -C . -f makefile.$(DEVICE) libs PROFILE=$(PROFILE) DEVICE_TYPE=$(DEVICE_TYPE)

libs-clean:
	$(MAKE) -C . -f makefile.$(DEVICE) libs-clean PROFILE=$(PROFILE)

libs-scrub:
	$(MAKE) -C . -f makefile.$(DEVICE) libs-scrub PROFILE=$(PROFILE)

libs-external:
	$(MAKE) -C . -f makefile.$(DEVICE) libs-external PROFILE=$(PROFILE) DEVICE_TYPE=$(DEVICE_TYPE)

libs-external-clean:
	$(MAKE) -C . -f makefile.$(DEVICE) libs-external-clean PROFILE=$(PROFILE)

libs-external-scrub:
	$(MAKE) -C . -f makefile.$(DEVICE) libs-external-scrub PROFILE=$(PROFILE)

examples:
	$(MAKE) -C . -f makefile.$(DEVICE) examples PROFILE=$(PROFILE)

examples-clean:
	$(MAKE) -C . -f makefile.$(DEVICE) examples-clean PROFILE=$(PROFILE)

examples-scrub:
	$(MAKE) -C . -f makefile.$(DEVICE) examples-scrub PROFILE=$(PROFILE)

help:
	$(MAKE) -C . -f makefile.$(DEVICE) -s help PROFILE=$(PROFILE)

sbl:
	$(MAKE) -C . -f makefile.$(DEVICE) sbl PROFILE=$(PROFILE)

sbl-hs:
	$(MAKE) -C . -f makefile.$(DEVICE) sbl-hs PROFILE=$(PROFILE)

sbl-clean:
	$(MAKE) -C . -f makefile.$(DEVICE) sbl-clean PROFILE=$(PROFILE)

sbl-scrub:
	$(MAKE) -C . -f makefile.$(DEVICE) sbl-scrub PROFILE=$(PROFILE)

syscfg-gui:
	$(SYSCFG_GUI_SCRIPT) --product $(SYSCFG_SDKPRODUCT) --device $(SYSCFG_DEVICE) --context $(SYSCFG_CPU)

devconfig:
	$(SYSCFG_GUI_SCRIPT) --product $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.json --device $(SYSCFG_DEVICE) --context $(SYSCFG_CPU) --output devconfig/ $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.syscfg

.PHONY: all clean scrub
.PHONY: libs libs-clean libs-scrub
.PHONY: libs-external libs-external-clean libs-external-scrub
.PHONY: examples examples-clean examples-scrub
.PHONY: help
.PHONY: sbl sbl-clean sbl-scrub
.PHONY: syscfg-gui
.PHONY: devconfig


################ Internal make targets - not to be used by customers ################
NODE=node

GEN_BUILDFILES_TARGET?=development
INSTRUMENTATION_MODE?=disable

DOC_COMBO = r5f.ti-arm-clang
# default combo for doc generation
ifeq ($(DEVICE),$(filter $(DEVICE), am62x))
  DOC_COMBO = m4f.ti-arm-clang
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am62lx))
  DOC_COMBO = a53.gcc-aarch64
endif

projectspec-help:
	$(MAKE) -C . -f makefile_projectspec.$(DEVICE) -s help PROFILE=$(PROFILE)

docs:
	$(MAKE) -C docs_src/docs/api_guide all DEVICE=$(DEVICE) DOC_COMBO=$(DOC_COMBO)
	@echo "<script id=\"searchdata\" type=\"text/xmldata\">" >> ./docs/api_guide_$(DEVICE)/search.html
	$(COPY) docs_src/docs/api_guide/search.js ./docs/api_guide_$(DEVICE)/search/search.js
	$(CAT) ./docs/api_guide_$(DEVICE)/searchdata.xml >> ./docs/api_guide_$(DEVICE)/search.html
	@echo "</script>" >> ./docs/api_guide_$(DEVICE)/search.html

ifneq ($(OS),Windows_NT)
ifeq ($(BUILD_XLIBS),yes)
ifeq ($(filter $(DEVICE),am62dx am275x),$(DEVICE))
	$(MAKE) -C source/fftlib -f makefile.$(DEVICE).c75x.ti-c7000 docs
	mkdir -p docs/api_guide_$(DEVICE)/fftlib_docs
	$(COPY) -r source/fftlib/docs/user_guide/ ./docs/api_guide_$(DEVICE)/fftlib_docs

	$(MAKE) -C source/mathlib -f makefile.$(DEVICE).c75x.ti-c7000 docs
	mkdir -p docs/api_guide_$(DEVICE)/mathlib_docs
	$(COPY) -r source/mathlib/docs/user_guide/ ./docs/api_guide_$(DEVICE)/mathlib_docs

	$(MAKE) -C source/vxlib -f makefile.$(DEVICE).c75x.ti-c7000 docs
	mkdir -p docs/api_guide_$(DEVICE)/vxlib_docs
	$(COPY) -r source/vxlib/docs/user_guide/ ./docs/api_guide_$(DEVICE)/vxlib_docs

	$(MAKE) -C source/dsplib -f makefile.$(DEVICE).c75x.ti-c7000 docs
	mkdir -p docs/api_guide_$(DEVICE)/dsplib_docs
	$(COPY) -r source/dsplib/docs/user_guide/ ./docs/api_guide_$(DEVICE)/dsplib_docs

	$(MAKE) -C source/audiolib -f makefile.$(DEVICE).c75x.ti-c7000 docs
	mkdir -p docs/api_guide_$(DEVICE)/audiolib_docs
	$(COPY) -r source/audiolib/docs/user_guide/ ./docs/api_guide_$(DEVICE)/audiolib_docs

	$(MAKE) -C source/tisp -f makefile.$(DEVICE).c75x.ti-c7000 docs
	mkdir -p docs/api_guide_$(DEVICE)/tisp_docs
	$(COPY) -r source/tisp/docs/user_guide/ ./docs/api_guide_$(DEVICE)/tisp_docs
endif
endif # ifeq ($(BUILD_XLIBS),yes)
endif # ifneq ($(OS),Windows_NT)

docs-clean:
	$(MAKE) -C docs_src/docs/api_guide clean DEVICE=$(DEVICE) DOC_COMBO=$(DOC_COMBO)

gen-buildfiles:
	$(NODE) ./.project/project.js --device $(DEVICE) --target $(GEN_BUILDFILES_TARGET) --instrumentation $(INSTRUMENTATION_MODE)

gen-buildfiles-clean:
	$(NODE) ./.project/project.js --device $(DEVICE) --target clean

tests: libs libs-external
	$(MAKE) -C test -f makefile.$(DEVICE) all PROFILE=$(PROFILE)

tests-clean:
	$(MAKE) -C test -f makefile.$(DEVICE) clean PROFILE=$(PROFILE)

tests-scrub:
	$(MAKE) -C test -f makefile.$(DEVICE) scrub PROFILE=$(PROFILE)

tests-libs: libs libs-external
	$(MAKE) -C test -f makefile.$(DEVICE) libs PROFILE=$(PROFILE)

tests-libs-clean:
	$(MAKE) -C test -f makefile.$(DEVICE) libs-clean PROFILE=$(PROFILE)

tests-libs-scrub:
	$(MAKE) -C test -f makefile.$(DEVICE) libs-scrub PROFILE=$(PROFILE)

ifeq ($(DEVICE),$(filter $(DEVICE), am62x))
syscfg-tests: syscfg-tests-a53ss0-0 syscfg-tests-m4fss0-0 syscfg-tests-r5fss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am62ax am62dx))
syscfg-tests: syscfg-tests-a53ss0-0 syscfg-tests-r5fss0-0 syscfg-tests-mcu-r5fss0-0 syscfg-tests-c75ss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am62px))
syscfg-tests: syscfg-tests-wkup-r5fss0-0 syscfg-tests-mcu-r5fss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am275x))
syscfg-tests: syscfg-tests-r5fss0-0 syscfg-tests-wkup-r5fss0-0 syscfg-tests-c75ss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am62lx))
syscfg-tests: syscfg-tests-a53ss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), j722s))
syscfg-tests: syscfg-tests-a53ss0-0 syscfg-tests-a53ss0-1 syscfg-tests-a53ss1-0 syscfg-tests-a53ss1-1 syscfg-tests-mcu-r5fss0-0 syscfg-tests-wkup-r5fss0-0 syscfg-tests-main-r5fss0-0 syscfg-tests-c75ss0-0 syscfg-tests-c75ss0-1
endif

syscfg-tests-a53ss0-0:
	-$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/tests/sanityTests.js $(SYSCFG_TEST_FLAGS) -s $(SYSCFG_SDKPRODUCT) -d "$(SYSCFG_DEVICE).*_$(SYSCFG_DEVICE_VARIANT)_$(SYSCFG_DEVICE_PACKAGE)" -c a53ss0-0

syscfg-tests-a53ss0-1:
	-$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/tests/sanityTests.js $(SYSCFG_TEST_FLAGS) -s $(SYSCFG_SDKPRODUCT) -d "$(SYSCFG_DEVICE).*_$(SYSCFG_DEVICE_VARIANT)_$(SYSCFG_DEVICE_PACKAGE)" -c a53ss0-1

syscfg-tests-a53ss1-0:
	-$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/tests/sanityTests.js $(SYSCFG_TEST_FLAGS) -s $(SYSCFG_SDKPRODUCT) -d "$(SYSCFG_DEVICE).*_$(SYSCFG_DEVICE_VARIANT)_$(SYSCFG_DEVICE_PACKAGE)" -c a53ss1-0

syscfg-tests-a53ss1-1:
	-$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/tests/sanityTests.js $(SYSCFG_TEST_FLAGS) -s $(SYSCFG_SDKPRODUCT) -d "$(SYSCFG_DEVICE).*_$(SYSCFG_DEVICE_VARIANT)_$(SYSCFG_DEVICE_PACKAGE)" -c a53ss1-1

syscfg-tests-m4fss0-0:
	-$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/tests/sanityTests.js $(SYSCFG_TEST_FLAGS) -s $(SYSCFG_SDKPRODUCT) -d "$(SYSCFG_DEVICE).*_$(SYSCFG_DEVICE_VARIANT)_$(SYSCFG_DEVICE_PACKAGE)" -c m4fss0-0

syscfg-tests-r5fss0-0:
	-$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/tests/sanityTests.js $(SYSCFG_TEST_FLAGS) -s $(SYSCFG_SDKPRODUCT) -d "$(SYSCFG_DEVICE).*_$(SYSCFG_DEVICE_VARIANT)_$(SYSCFG_DEVICE_PACKAGE)" -c "^r5fss0-0"

syscfg-tests-mcu-r5fss0-0:
	-$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/tests/sanityTests.js $(SYSCFG_TEST_FLAGS) -s $(SYSCFG_SDKPRODUCT) -d "$(SYSCFG_DEVICE).*_$(SYSCFG_DEVICE_VARIANT)_$(SYSCFG_DEVICE_PACKAGE)" -c mcu-r5fss0-0

syscfg-tests-wkup-r5fss0-0:
	-$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/tests/sanityTests.js $(SYSCFG_TEST_FLAGS) -s $(SYSCFG_SDKPRODUCT) -d "$(SYSCFG_DEVICE).*_$(SYSCFG_DEVICE_VARIANT)_$(SYSCFG_DEVICE_PACKAGE)" -c wkup-r5fss0-0

syscfg-tests-main-r5fss0-0:
	-$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/tests/sanityTests.js $(SYSCFG_TEST_FLAGS) -s $(SYSCFG_SDKPRODUCT) -d "$(SYSCFG_DEVICE).*_$(SYSCFG_DEVICE_VARIANT)_$(SYSCFG_DEVICE_PACKAGE)" -c main-r5fss0-0

syscfg-tests-c75ss0-0:
	-$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/tests/sanityTests.js $(SYSCFG_TEST_FLAGS) -s $(SYSCFG_SDKPRODUCT) -d "$(SYSCFG_DEVICE).*_$(SYSCFG_DEVICE_VARIANT)_$(SYSCFG_DEVICE_PACKAGE)" -c c75ss0-0

syscfg-tests-c75ss1-0:
	-$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/tests/sanityTests.js $(SYSCFG_TEST_FLAGS) -s $(SYSCFG_SDKPRODUCT) -d "$(SYSCFG_DEVICE).*_$(SYSCFG_DEVICE_VARIANT)_$(SYSCFG_DEVICE_PACKAGE)" -c c75ss1-0


.PHONY: syscfg-tests-a53ss0-0 syscfg-tests-a53ss0-1 syscfg-tests-a53ss1-0 syscfg-tests-a53ss1-1
.PHONY: syscfg-tests-r5fss0-0 syscfg-tests-mcu-r5fss0-0 syscfg-tests-wkup-r5fss0-0 syscfg-tests-main-r5fss0-0
.PHONY: syscfg-tests-m4fss0-0 syscfg-tests-c75ss0-0 syscfg-tests-c75ss0-1
.PHONY: projectspec-help docs docs-clean
.PHONY: gen-buildfiles gen-buildfiles-clean
.PHONY: tests tests-clean tests-scrub tests-libs tests-libs-clean tests-libs-scrub
.PHONY: syscfg-tests
