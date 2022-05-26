
export MCU_PLUS_SDK_PATH=$(abspath ../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak

DOXYGEN ?= doxygen
export DEVICE ?= am243x
export DATASHEET_OUT_DIR=$(MCU_PLUS_SDK_PATH)/docs/datasheet_$(DEVICE)

all:
	$(MKDIR) $(DATASHEET_OUT_DIR)
	$(DOXYGEN) doxygen.cfg 2> doxy_warnings_$(DEVICE).txt
	cd theme && $(COPY) *.png $(DATASHEET_OUT_DIR)


clean:
	$(RMDIR) $(DATASHEET_OUT_DIR)

help:
	@echo "# Supported build targets:"
	@echo "# ========================"
	@echo "# $(MAKE) -s all"
	@echo "# $(MAKE) -s clean"
	@echo "# $(MAKE) -s help"
	@echo "#"

.PHONY: all clean help
