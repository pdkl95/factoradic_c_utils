ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -Wall -Wextra

EXTRA_DIST = \
	README.m4

LDADD = -lgmp

bin_PROGRAMS = dec2fact fact2dec

COMMON_SRC = \
	src/globals.c \
	src/common.h

dec2fact_SOURCES = \
	$(COMMON_SRC) \
	src/dec2fact.c

fact2dec_SOURCES = \
	$(COMMON_SRC) \
	src/fact2dec.c

