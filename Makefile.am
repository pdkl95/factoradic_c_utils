ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -Wall -Wextra

LDADD = -lgmp

bin_PROGRAMS = dec2fact fact2dec

COMMON_SRC = \
	src/options.c options.h \
	src/globals.c \
	src/common.h

dec2fact_SOURCES = \
	$(COMMON_SRC) \
	src/dec2fact.c

fact2dec_SOURCES = \
	$(COMMON_SRC) \
	src/fact2dec.c

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/build-aux/tap-driver.sh

TESTS = tests/check_dec2fact \
	tests/check_fact2dec

EXTRA_DIST = \
	$(TESTS) \
	tests/test_helper.sh \
	README.m4
