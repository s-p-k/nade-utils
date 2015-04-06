# nade-utils version
VERSION = 0.1

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

BIN = \
	cpucnt \
	cput   \
	iden

OBJ = ${BIN:=.o}
SRC = ${BIN:=.c}
all: ${BIN}

CC = gcc
CFLAGS += -Wall -Wextra

{$BIN}: ${CC}

.o:
	@echo $<
	${CC} ${CFLAGS} -o $@ $<

.c:.o
	${CC} ${CFLAGS} -o $@ -c $<

clean:
	@echo cleaning
	@rm -f $(BIN) $(OBJ) $(LIB) nade-utils nade-utils-$(VERSION).tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p nade-utils-${VERSION}
	@cp -R LICENSE Makefile README.md ${SRC} iden.1 nade-utils-${VERSION}
	@tar -cf nade-utils-${VERSION}.tar nade-utils-${VERSION}
	@gzip nade-utils-${VERSION}.tar
	@rm -rf nade-utils-${VERSION}

install: all
	@echo installing executable files to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f ${BIN} ${DESTDIR}${PREFIX}/bin
	@cd ${DESTDIR}$(PREFIX)/bin && chmod 755 ${BIN}
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < iden.1 > ${DESTDIR}${MANPREFIX}/man1/iden.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/iden.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@cd ${DESTDIR}${PREFIX}/bin/ && rm -rf ${BIN}
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/iden.1

.PHONY: all options clean dist install uninstall
