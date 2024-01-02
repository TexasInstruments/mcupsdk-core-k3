MODULE_NAME = dm_stub

SRCDIR = src/rm_pm_hal_src src/rm_pm_hal_src/app/dmstub
INCDIR = src/rm_pm_hal_src src/rm_pm_hal_src/app/dmstub
DM_CFLAGS =  -DBUILD_MCU1_0 -DBUILD_MCU

CFLAGS_LOCAL_COMMON = $(DM_CFLAGS)
CONFIG_LPM_DM_STUB=y
CONFIG_LPM_DM_TRACE=y
CONFIG_LPM_DM_TRACE_BUFFER=y
CONFIG_LPM_DM_TRACE_UART=y
CONFIG_LPM_32_BIT_DDR=y

ifeq ($(CONFIG_LPM_DM_STUB),y)
  CFLAGS_LOCAL_COMMON += -DCONFIG_LPM_DM_STUB
endif
ifeq ($(CONFIG_LPM_DM_TRACE),y)
  CFLAGS_LOCAL_COMMON += -DCONFIG_LPM_DM_TRACE
	ifeq ($(CONFIG_LPM_DM_TRACE_BUFFER),y)
  	CFLAGS_LOCAL_COMMON += -DCONFIG_LPM_DM_TRACE_BUFFER
	endif
	ifeq ($(CONFIG_LPM_DM_TRACE_UART),y)
  	CFLAGS_LOCAL_COMMON += -DCONFIG_LPM_DM_TRACE_UART
	endif
endif
ifeq ($(CONFIG_LPM_32_BIT_DDR),y)
  CFLAGS_LOCAL_COMMON += -DCONFIG_LPM_32_BIT_DDR
endif

CONFIG_SOC_FOLDER_STRING=am62px
SCICLIENT_SOCVER = V7
TARGET_SOC = $(shell echo $(CONFIG_SOC_FOLDER_STRING))

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
_build=$(eval include ../rm_pm_hal/rm_pm_hal_src/$(1)build.mk)
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

PDK_INSTALL_PATH :=
objtree := $(PDK_INSTALL_PATH)
srctree := $(objtree)
srcroot := $(srctree)
DEFINES := $(CFLAGS_LOCAL_COMMON)
CFLAGS_LOCAL_COMMON :=

$(call _recurse_inc,)

CFLAGS_LOCAL_COMMON += $(cppflags-y)
CFLAGS_LOCAL_COMMON += -I$(srctree)/include

# for all obj-y entries .o extensions are changed to .c
SRCS_COMMON = $(foreach f, $(obj-y), $(subst .o,.c,$(f)))
TEM_SRCS_COMMON := $(SRCS_COMMON)

# When obj-y is evaluated entry.o is added to the variable. but entry.o corresponds to entry.S file
# So removing entry.c from SRCS_COMMON and adding entry.S in SRCS_ASM_S
SRCS_COMMON = $(filter-out app/dmstub/entry.c, $(TEM_SRCS_COMMON))
SRCS_ASM_S += entry.S
