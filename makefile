CFLAGS := -std=gnu11 -mcpu=arm946e-s -marm
CFLAGS += -O2 -Wall -Wextra -Wpedantic
CFLAGS += -Wno-implicit-int
CFLAGS += -Wno-implicit-function-declaration
CFLAGS += -Wno-main
CFLAGS += -Wno-overflow
CFLAGS += -Wno-sign-compare
CFLAGS += -Wno-builtin-declaration-mismatch
CFLAGS += -Wno-unused-variable
CFLAGS += -Wno-unused-but-set-variable
CFLAGS += -DARM9
CFLAGS += -I$(DEVKITPRO)/libnds/include
CFLAGS += -I$(DEVKITPRO)/calico/include

LDFLAGS := -specs=$(DEVKITPRO)/calico/share/ds9.specs

src = $(wildcard src/*.c)
obj = $(src:src/%.c=obj/%.o)
d = $(src:src/%.c=obj/%.d)

elf = life.elf
out = life.nds

LIBS := -lnds9 -lfat -lcalico_ds9
LIBDIRS := $(DEVKITPRO)/libnds $(DEVKITPRO)/calico

include $(DEVKITARM)/ds_rules

.PHONY: all clean run

all: $(out)

$(out): $(elf)
	@echo 'NDS $@'
	@ndstool -c $@ -9 $< $(_ARM7_ELF) >/dev/null

$(elf): $(obj)
	@echo 'LD $^'
	@$(CC) $(LIBDIRS:%= -L%/lib) $(LDFLAGS) $^ $(LIBS) -o $@

obj/%.o: src/%.c | obj
	@echo 'CC $<'
	@$(CC) -MMD -MP -MF $(@:%.o=%.d) $(_EXTRADEFS) $(CFLAGS) -c $< -o $@

obj:
	@mkdir -p $@

-include $(d)

run: $(out)
	./emu -f $< >/dev/null

clean:
	rm -rf obj $(elf) $(out) sd*
