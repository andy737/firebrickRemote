ramstage-y += socket_AM2r2.c
subdirs-y += ../model_10xxx
subdirs-y += ../quadcore
subdirs-y += ../mtrr
subdirs-y += ../microcode
subdirs-y += ../../x86/tsc
subdirs-y += ../../x86/lapic
subdirs-y += ../../x86/cache
subdirs-y += ../../x86/pae
subdirs-y += ../../x86/mtrr
subdirs-y += ../../x86/smm
subdirs-y += ../smm

cpu_incs += $(src)/cpu/amd/car/cache_as_ram.inc
