export RM_PM_HAL_BUILD_PATH

TARGET_SOC = $(shell echo $(CONFIG_SOC_FOLDER_STRING))

ifeq ($(CONFIG_GET_FW_CAPS),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_GET_FW_CAPS
endif
ifeq ($(CONFIG_PM),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_PM
endif
ifeq ($(CONFIG_PSC),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_PSC
endif
ifeq ($(CONFIG_CLOCK),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_CLOCK
endif
ifeq ($(CONFIG_CLK_RPLL028),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_CLK_RPLL028
endif
ifeq ($(CONFIG_CLK_ADPLLM),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_CLK_ADPLLM
endif
ifeq ($(CONFIG_CLK_PLL_16FFT),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_CLK_PLL_16FFT
endif
ifeq ($(CONFIG_LPM_CLK),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_LPM_CLK
endif
ifeq ($(CONFIG_LPM_LIMIT_IR_TRACKING),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_LPM_LIMIT_IR_TRACKING
endif
ifeq ($(CONFIG_CLK_PLL_DESKEW),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_CLK_PLL_DESKEW
endif
ifeq ($(CONFIG_CLK_PLL_16FFT_FRACF_CALIBRATION),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_CLK_PLL_16FFT_FRACF_CALIBRATION
endif
ifeq ($(CONFIG_PSC_PD_MAX_COUNT_64),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_PSC_PD_MAX_COUNT_64
endif
ifeq ($(CONFIG_DM_BUILD),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_DM_BUILD
endif
ifeq ($(CONFIG_RM),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_RM
endif
ifeq ($(CONFIG_RM_LOCAL_SUBSYSTEM_REQUESTS),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_RM_LOCAL_SUBSYSTEM_REQUESTS
endif
ifeq ($(CONFIG_RM_IRQ),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_RM_IRQ
endif
ifeq ($(CONFIG_INTERRUPT_AGGREGATOR_UNMAPPED_EVENTS),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_INTERRUPT_AGGREGATOR_UNMAPPED_EVENTS
endif
ifeq ($(CONFIG_RM_RA),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_RM_RA
endif
ifeq ($(CONFIG_RM_RA_DMSS_RING),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_RM_RA_DMSS_RING
endif
ifeq ($(CONFIG_INTERRUPT_AGGREGATOR_UNMAPPED_EVENTS),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_INTERRUPT_AGGREGATOR_UNMAPPED_EVENTS
endif
ifeq ($(CONFIG_RM_RA_NAV_RING),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_RM_RA_NAV_RING
endif
ifeq ($(CONFIG_RM_UDMAP),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_RM_UDMAP
endif
ifeq ($(CONFIG_UDMAP_CHANNEL_BURST_SIZE),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_UDMAP_CHANNEL_BURST_SIZE
endif
ifeq ($(CONFIG_UDMAP_TX_CHANNEL_TEARDOWN_TYPE),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_UDMAP_TX_CHANNEL_TEARDOWN_TYPE
endif
ifeq ($(CONFIG_UDMAP_UDMA),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_UDMAP_UDMA
endif
ifeq ($(CONFIG_UDMAP_BCDMA),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_UDMAP_BCDMA
endif
ifeq ($(CONFIG_UDMAP_PKTDMA),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_UDMAP_PKTDMA
endif
ifeq ($(CONFIG_RM_PROXY),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_RM_PROXY
endif
ifeq ($(CONFIG_LPM_DM),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_LPM_DM
endif
ifeq ($(CONFIG_TRACE),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_TRACE
endif
ifeq ($(CONFIG_TRACE_BUFFER),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_TRACE_BUFFER
endif
ifeq ($(CONFIG_TRACE_UART),y)
CFLAGS_LOCAL_COMMON += -DCONFIG_TRACE_UART
endif
CFLAGS_LOCAL_COMMON += -DCONFIG_DEVICE_TYPE_GP
# include build.inc #tdt
yn-files := obj extra prepare_headers target
yn-paths := subdirs
yn-vars := $(yn-files) $(yn-paths)

build_files := $(foreach v,$(yn-files),$v-y $v-n)
build_paths := obj src

objtree ?= .
srctree ?= .

objroot ?= $(objtree)/..
srcroot ?= $(srctree)/..

obj := $(objtree)
src := $(srctree)

var_subst=$(subst /,_,$(subst :,_,$1))
_push=$(eval $2$1 := $($1))
_push_v := $(build_files) $(build_paths) _curr
_push_vars=$(foreach v,$(_push_v),$(call _push,$(v),$(call var_subst,$(_MODULE))))
_push_all=$(if $(_MODULE),$(call _push_vars)$(eval _curr := $(_MODULE)))
_clear=$(eval $1 :=)
_reset_v := $(foreach v,$(yn-files),$v- $v-y $v-n)
_reset_vars=$(foreach v,$(_reset_v),$(call _clear,$v))
_next_path=$(if $(1:.=),$1/$(notdir $(_MODULE:%/=%)),$(notdir $(_MODULE:%/=%)))
_set_src=$(if $(_MODULE),$(eval src := $(call _next_path,$(src))))
_set_obj=$(if $(_MODULE),$(eval obj := $(call _next_path,$(obj))))
obj-n := $(obj-n) $(obj-)
_set_var_n=$(eval $(1)-n := $($(1)-n) $($(1)-))
_set_vars_n=$(foreach v,$(yn-vars),$(call _set_var_n,$v))
_null_if_unset=$(if $($1),$1)
_get_mod_cflags=$(subst CFLAGS_,CFLAGS_$(_MODULE),$1)
_prepend_cflags=$(eval $(call _get_mod_cflags,$1):=$($1))
_all_cflag_vars=$(addprefix CFLAGS_,$1)
_valid_cflag_vars=$(strip $(foreach v,$(call _all_cflag_vars,$1),$(call _null_if_unset,$v)))
_prepend_cflags_obj_y=$(foreach v,$(call _valid_cflag_vars,$(obj-y)),$(call _prepend_cflags,$v))
_clear_cflags_obj_y=$(foreach v,$(call _all_cflag_vars,$(obj-y)),$(call _clear,$v))
_top_actions=\
	$(call _push_all) \
	$(call _reset_vars) \
	$(call _set_obj) \
	$(call _set_src)
_path=$(eval $1 := \
	$(patsubst %,$(src)/%,$(filter-out %:/% ./% /%,$(filter %/,$($1)))) \
	$(patsubst %,$(obj)/%,$(filter-out %:/% ./% /%,$(filter-out %/,$($1)))) \
	$(filter %:/% ./% /%,$($1)))
_prepend_paths=$(foreach f,$(build_files),$(call _path,$f))
_set_path=$(eval $(1)-$(2) := $(filter %/,$(foreach f,$(yn-files:%=%-$2),$($f))))
_set_paths=$(foreach d,$(yn-paths),$(call _set_path,$d,y)$(call _set_path,$d,n))
_rm_path=$(eval $1 := $(filter-out %/,$($1)))
_rm_paths=$(foreach f,$(yn-files),$(call _rm_path,$(f)-y)$(call _rm_path,$(f)-n))
_build=$(eval include $(RM_PM_HAL_BUILD_PATH)/$(1)build.mk)
_recurse_inc=$(call _top_actions)$(call _build,$1)$(call _bottom_actions)
_recurse_vars=$(foreach d,$1,$(eval _MODULE:=$d)$(call _recurse_inc,$d))
_recurse=$(foreach d,$(yn-paths:%=%-y),$(call _recurse_vars,$($d)))
_pop_file=$(eval $1 := $($2$1) $($1))$(eval $2$1 :=)
_pop_path=$(eval $1 := $($2$1))$(eval $2$1 :=)
_pop_files=$(foreach v,$(build_files),$(call _pop_file,$(v),$(call var_subst,$(_curr))))
_pop_paths=$(foreach v,$(build_paths) _curr,$(call _pop_path,$(v),$(call var_subst,$(_curr))))
_pop_all=$(if $(_curr),$(call _pop_files)$(call _pop_paths))
_bottom_actions= \
	$(call _prepend_cflags_obj_y) \
	$(call _clear_cflags_obj_y) \
	$(call _set_vars_n) \
	$(call _prepend_paths) \
	$(call _set_paths) \
	$(call _rm_paths) \
	$(call _recurse) \
	$(call _pop_all) \
	$(eval _MODULE :=)

PDK_INSTALL_PATH =
objtree := $(PDK_INSTALL_PATH)
srctree := $(objtree)
srcroot := $(srctree)
DEFINES := $(CFLAGS_LOCAL_COMMON)
CFLAGS_LOCAL_COMMON :=
$(call _recurse_inc,)

CFLAGS_LOCAL_COMMON += $(cppflags-y)
CFLAGS_LOCAL_COMMON += -Irm_pm_hal_src/pm/soc/$(TARGET_SOC)/include
CFLAGS_LOCAL_COMMON += -Irm_pm_hal_src/include
# CFLAGS_LOCAL_COMMON += -I$(PDK_INSTALL_PATH)/ti/drv/sciclient/soc/$(SCICLIENT_SOCVER)
# CFLAGS_LOCAL_COMMON += -I$(PDK_INSTALL_PATH)/ti/drv/sciclient/src/priv
# CFLAGS_LOCAL_COMMON += -I$(PDK_INSTALL_PATH)/ti/osal

SRCS_COMMON = $(foreach f, $(obj-y), $(subst .o,.c,$(f)))

SRCDIR += src/priv/osal
SRCS_COMMON +=  osal_glue.c

ifeq ($(CONFIG_TRACE),y)

SRCDIR += src/priv/trace
INCDIR += src/priv/trace
ifeq ($(CONFIG_TRACE_BUFFER),y)
SRCS_COMMON +=  trace-buffer.c
endif
ifeq ($(CONFIG_TRACE_UART),y)
SRCS_COMMON +=  trace-uart.c
endif
SRCS_COMMON +=  trace.c

endif

ifeq ($(CONFIG_LPM_DM),y)
SRCDIR += src/priv/osal
SRCS_COMMON +=  osal_dm.c
endif
