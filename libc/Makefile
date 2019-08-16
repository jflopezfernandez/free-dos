
MKDIR=mkdir -p
RM=rm -f

DEFAULT_HOST!=../scripts/default-host
HOST?=DEFAULT_HOST
HOSTARCH!=../scripts/target-triplet-to-arch $(HOST)

CFLAGS?=-02 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
INCLUDEDIR?=$(PREFIX)/include
LIBDIR?=$(EXEC_PREFIX)/lib

CFLAGS:=$(CFLAGS) -std=c17 -Wall -Wextra -Wpedantic -ffreestanding
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS:=$(CFLAGS)
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_libk

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS:=$(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPPFLAGS:=$(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREEOBJS=\
$(ARCH_FREEOBJS) \
string/memset.o \
string/strlen.o \

HOSTEDOBJS=\
$(ARCH_HOSTEDOBJS) \

OBJS=\
$(FREEOBJS) \
$(HOSTEDOBJS) \

LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

#BINARIES=libc.a libk.a # Not ready for libc yet.
BINARIES=libk.a

all: $(BINARIES)

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

.c.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.c.S:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

%.libk.o: %.c
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

.S.libk.o:
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

install: install-headers install-libs

install-headers:
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

.PHONY: clean
clean:
	$(RM) $(BINARIES) *.a
	$(RM) $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
