
# vpath %.asm arch/i386/
# vpath %.c kernel/
# vpath %.c arch/i386/
# vpath %.ld arch/i386/

MKDIR=mkdir -p
cp=cp

DEFAULT_HOST:=i686-elf
HOST?=$(DEFAULT_HOST)
ARCH!=../scripts/target-triplet-to-arch $(HOST)

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS) -std=c17 -Wall -Wextra -Wpedantic -ffreestanding
CPPFLAGS:=$(CPPFLAGS) -D__iskernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

ARCHDIR=arch/$(ARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel/kernel.o \

OBJS=\
$(KERNEL_OBJS) \

LINK_LIST=\
$(LDFLAGS) \
$(KERNEL_OBJS) \
$(LIBS) \

TARGET=fdos

all: $(TARGET)

$(TARGET): $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot $(TARGET)

.c.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

install: install-headers install-kernel

install-headers:
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/

install-kernel: $(TARGET)
	$(MKDIR) $(DESTDIR)$(BOOTDIR)
	cp $(TARGET) $(DESTDIR)$(BOOTDIR)

.PHONY: clean
clean:
	$(RM) $(TARGET)
	$(RM) $(OBJS) *.o */*.o */*/*.o
