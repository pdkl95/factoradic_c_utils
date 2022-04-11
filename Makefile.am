##############################################################################
#                                                                            #
#  This file is part of factoradic_c_utils.                                  #
#                                                                            #
#  factoradic_c_utils is free software: you can redistribute it and/or       #
#  modify it under the terms of the GNU General Public License as published  #
#  by the Free Software Foundation, either version 3 of the License,         #
#  or (at your option) any later version.                                    #
#                                                                            #
#  factoradic_c_utils is distributed in the hope that it will be useful,     #
#  but WITHOUT ANY WARRANTY; without even the implied warranty of            #
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General  #
#  Public License for more details.                                          #
#                                                                            #
#  You should have received a copy of the GNU General Public License along   #
#  with factoradic_c_utils. If not, see <https://www.gnu.org/licenses/>.     #
#                                                                            #
##############################################################################


ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -Wall -Wextra

LDADD = -lgmp

bin_PROGRAMS = dec2fact fact2dec

COMMON_SRC = \
	src/options.c src/options.h \
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

TESTS_ENVIRONMENT = builddir=$(builddir)

TESTS = tests/check_dec2fact \
	tests/check_fact2dec

EXTRA_DIST = \
	$(TESTS) \
	tests/test_helper.sh \
	README.md

benchmark:
	./benchmark.sh 2>&1 | tee benchmark.txt 
