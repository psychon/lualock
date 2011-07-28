PREFIX     ?= /usr
INSTALLDIR := $(DESTDIR)$(PREFIX)

CC	:= gcc

PKGS := gtk+-3.0 lua5.1 oocairo xscrnsaver
INCS := $(shell PKG_CONFIG_PATH=/home/psychon/projects/lua-oocairo pkg-config --cflags $(PKGS))
LIBS := $(shell PKG_CONFIG_PATH=/home/psychon/projects/lua-oocairo pkg-config --libs $(PKGS)) -lpam

CFLAGS   := -Wall -Wextra -std=gnu99 -I. $(INCS) $(CFLAGS)
CPPFLAGS := -DLUALOCK_INSTALL_DIR=\"$(INSTALLDIR)/share/lualock\"  \
			-DLUALOCK_DATA_DIR=\"./data\" $(CPPFLAGS)
DEBUG    := -g -DDEBUG
LDFLAGS  := $(LIBS) $(LDFLAGS)

SRCS  := $(wildcard *.c clib/*.c)
HEADS := $(wildcard *.h clib/*.h)
OBJS  := $(foreach obj,$(SRCS:.c=.o),$(obj))

default: debug


all: options lualock

debug: CFLAGS += $(DEBUG)
debug: all

options:
	@echo lualock build options:
	@echo "CC               = $(CC)"
	@echo "CFLAGS           = $(CFLAGS)"
	@echo "LDFLAGS          = $(LDFLAGS)"
	@echo "INSTALLDIR       = $(INSTALLDIR)"
	@echo
	@echo "build targets:"
	@echo "SRCS = $(SRCS)"
	@echo

.c.o:
	@echo $(CC) -c $< -o $@
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

lualock: $(OBJS)
	@echo $(CC) -o $@ $(OBJS)
	@$(CC) -o $@ $(OBJS) $(LDFLAGS)

apidoc:
	mkdir -p apidocs
	luadoc --nofiles -d apidocs lib/* luadoc/*

doc: $(HEADS) $(SRCS)
	doxygen -s lualock.doxygen

install:
	install -d $(INSTALLDIR)/share/lualock/
	cp -r data $(INSTALLDIR)/share/lualock/
	chmod 644 $(INSTALLDIR)/share/lualock/data/*
	cp -r lib $(INSTALLDIR)/share/lualock/
	chmod 755 $(INSTALLDIR)/share/lualock/lib/
	chmod 755 $(INSTALLDIR)/share/lualock/lib/odious/
	chmod 644 $(INSTALLDIR)/share/lualock/lib/odious/*.lua
	install -d $(INSTALLDIR)/bin/
	install lualock $(INSTALLDIR)/bin/lualock
	install -d $(DESTDIR)/etc/xdg/lualock/
	install -m644 config/rc.lua $(DESTDIR)/etc/xdg/lualock/
	install -D -m 644 lualock.pam $(DESTDIR)/etc/pam.d/lualock

clean:
	rm -rf lualock $(OBJS)
	rm -rf apidocs
