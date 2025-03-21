#
# This file is in the Public Domain.
#

PROJ=		rhashmap

SYSNAME:=	$(shell uname -s)
SYSARCH:=	$(shell uname -m)

CFLAGS+=	-std=c11 -O2 -g -Wall -Wextra -Werror
CFLAGS+=	-D_POSIX_C_SOURCE=200809L
CFLAGS+=	-D_GNU_SOURCE -D_DEFAULT_SOURCE

#
# Extended warning flags.
#
CFLAGS+=	-Wno-unknown-warning-option # gcc vs clang

CFLAGS+=	-Wstrict-prototypes -Wmissing-prototypes -Wpointer-arith
CFLAGS+=	-Wmissing-declarations -Wredundant-decls -Wnested-externs
CFLAGS+=	-Wshadow -Wcast-qual -Wcast-align -Wwrite-strings
CFLAGS+=	-Wold-style-definition
CFLAGS+=	-Wsuggest-attribute=noreturn -Wjump-misses-init
CFLAGS+=	-Wduplicated-cond -Wmisleading-indentation -Wnull-dereference
CFLAGS+=	-Wduplicated-branches -Wrestrict

ifeq ($(MAKECMDGOALS),tests)
DEBUG=		1
endif

ifeq ($(DEBUG),1)
CFLAGS+=	-Og -DDEBUG -fno-omit-frame-pointer
ifeq ($(SYSARCH),x86_64)
CFLAGS+=	-fsanitize=address -fsanitize=undefined
LDFLAGS+=	-fsanitize=address -fsanitize=undefined
endif
else
CFLAGS+=	-DNDEBUG
endif

LIB=		lib$(PROJ)
INCS=		rhashmap.h

OBJS=		rhashmap.o
OBJS+=		murmurhash.o
OBJS+=		siphash.o

$(LIB).a:	LDFLAGS+=
install/%.a:	ILIBDIR=	$(DESTDIR)/$(LIBDIR)
install:	IINCDIR=	$(DESTDIR)/$(INCDIR)/
#install:	IMANDIR=	$(DESTDIR)/$(MANDIR)/man3/

obj: $(OBJS)

lib: $(LIB).a

%.o: %.c
	gcc -c -fPIC -O3 $(CFLAGS) $<

$(LIB).a: $(OBJS)
	gcc -shared -o $@ $(LDFLAGS) $(notdir $^)

install/%.a: %.a
	mkdir -p $(ILIBDIR)
	cp $(notdir $@) $(ILIBDIR)/$(notdir $@)

install: $(addprefix install/,$(LIB).a)
	mkdir -p $(IINCDIR) && install -c $(INCS) $(IINCDIR)

tests: $(OBJS) t_$(PROJ).o
	$(CC) $(CFLAGS) $^ -o t_$(PROJ)
	MALLOC_CHECK_=3 ./t_$(PROJ)

clean:
	rm -rf .libs *.o *.lo *.la *.a t_$(PROJ)

.PHONY: all obj lib install tests clean
