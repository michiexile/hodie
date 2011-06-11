# Change these to customize for your setup
CC=gcc
CFLAGS=-g -Wall

# Install paths and command on recommendation from Peter Pentchev
INSTALL=/usr/bin/install -c

# Some prefer /usr/local over /usr as installation root
#INSTALL_PATH=/usr/local
INSTALL_PATH=/usr

BINDIR=$(INSTALL_PATH)/bin
MAN1DIR=$(INSTALL_PATH)/man/man1

# BSD might prefer this
# DOCPATH=$(INSTALL_PATH)/share/doc/hodie

# Linux might prefer this:
DOCDIR=$(INSTALL_PATH)/doc/packages/hodie

#############################
# End of user configuration #
#############################

EXEC=hodie
OBJECTS=hodie.o version.o help.o isleap.o to_roman.o to_roman_numerals.o\
	 parse_date.o date_to_roman.o
HEADERS=hodie.h includes.h version.h to_roman.h
DOCS=README LICENSE BUGS CREDITS CHANGELOG TODO DISTRIBUTORS

all: $(EXEC)

.PHONY: clean install uninstall all

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJECTS)

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJECTS): $(HEADERS)

install: $(EXEC)
	$(INSTALL) -s -m 755 $(EXEC) $(BINDIR)
	install -m 644 hodie.1 $(MAN1DIR)
	install -d $(DOCDIR)
	install -m 644 $(DOCS) $(DOCDIR)

uninstall:
	-rm -f $(BINDIR)/$(EXEC)
	-rm -f $(MAN1DIR)/hodie.1
	cd $(DOCDIR) && rm -f $(DOCS)
	-rm -r $(DOCDIR)

clean:
	-rm $(EXEC) *.o
