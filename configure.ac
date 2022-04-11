dnl -*- Autoconf -*-

dnl  This file is part of factoradic_c_utils.
dnl
dnl  factoradic_c_utils is free software: you can redistribute it and/or
dnl  modify it under the terms of the GNU General Public License as published
dnl  by the Free Software Foundation, either version 3 of the License,
dnl  or (at your option) any later version.
dnl
dnl  factoradic_c_utils is distributed in the hope that it will be useful,
dnl  but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
dnl  Public License for more details.
dnl
dnl  You should have received a copy of the GNU General Public License along
dnl  with factoradic_c_utils. If not, see <https://www.gnu.org/licenses/>.


m4_define([project_name], [factoradic_c_utils])
m4_define([project_url], [https://github.com/pdkl95/]project_name)
m4_define([project_email], [pdkl95@gmail.com])
m4_define([project_author], [Brent Sanders])
m4_define([project_copyright_year], [2022])
m4_define([project_licence], [GPLv3+])
m4_define([project_licence_desc], [GNU GPL version 3 or later <http://gnu.org/licences/gpl.html>])


dnl Release Version
m4_define([project_major_version], [0])
m4_define([project_minor_version], [1])
m4_define([project_micro_version], [0])
m4_define([project_version], project_major_version.project_minor_version.project_micro_version)

AC_PREREQ([2.64])

AC_INIT(project_name,project_version,project_email,project_name,project_url)

dnl http://xkcd.com/371/
m4_append([AM_SANITY_CHECK],[
AS_ECHO(["Build environment is grinning and holding a spatula. Guess not."])
])


dnl =================================
dnl ===  general Autotools Setup  ===
dnl =================================

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS([config.h])

AC_REQUIRE_AUX_FILE([tap-driver.sh])

AM_INIT_AUTOMAKE([1.13 foreign color-tests dist-xz subdir-objects -Wall -Werror])
AM_MAINTAINER_MODE([enable])


dnl =======================
dnl ===  early options  ===
dnl =======================

USER_CC=$CC
USER_CFLAGS=$CFLAGS

dnl >>> Build in debug mode

AC_ARG_ENABLE([debug],
    AS_HELP_STRING([--enable-debug], [Enable normal debug features (-g, -O0)]))

AS_IF([test "x$enable_debug" = "xyes"], [
     CFLAGS="$CFLAGS -ggdb3 -O0"
     LDFLAGS="$LDFLAGS -ggdb3"
])

AH_TEMPLATE([DEBUG_BUILD], [Defined to 1 when --enable-debug is active])
AS_IF([test "x$enable_debug" = "xyes"],[AC_DEFINE([DEBUG_BUILD],[1])])


dnl ==============
dnl ===  Deps  ===
dnl ==============

AC_ARG_WITH([gmp_include],
            [AC_HELP_STRING([--with-gmp-include=DIR],
                            [GMP include directory])],
            [CPPFLAGS="-I$withval $CPPFLAGS"])
AC_ARG_WITH([gmp_lib],
            [AC_HELP_STRING([--with-gmp-lib=DIR],
                            [GMP lib directory])],
            [LDFLAGS="-L$withval $LDFLAGS"])
AC_ARG_WITH([gmp],
            [AC_HELP_STRING([--with-gmp=DIR],
                           [GMP install directory])],
            [
            if test -z "$with_gmp_lib" -a -z "$with_gmp_include" ; then
               CPPFLAGS="-I$withval/include $CPPFLAGS"
               LDFLAGS="-L$withval/lib $LDFLAGS"
            else
               AC_MSG_FAILURE([Do not use --with-gmp and --with-gmp-include/--with-gmp-lib options simultaneously.])
            fi
            ])


dnl ===============================================
dnl ===  Check for CC and CFLAGS in gmp.h       ===
dnl ===  unless the user specified one of them  ===
dnl ===============================================

AC_PROG_EGREP
AC_PROG_SED
if test -z "$" && test -z "$USER_CFLAGS"; then
   GMP_CC_CFLAGS_FROM_HEADER
fi


dnl ========================================
dnl ===  Compiler/Language Dependencies  ===
dnl ========================================

AC_PROG_CC
AC_PROG_CC_C99
AM_PROG_CC_C_O
AC_LANG(C)

AC_USE_SYSTEM_EXTENSIONS

AC_PROG_RANLIB
AM_PROG_AR


dnl ===============================================================
dnl ===  Export the project configuration into config.h macros  ===
dnl ==============================================================-

dnl push this all into the headers
AH_TEMPLATE([PACKAGE_AUTHOR],
        [Author(s) of the project, and holder of the copyright])
AH_TEMPLATE([PACKAGE_COPYRIGHT_YEAR],
        [The year(s) that the project's copyright was established])
AH_TEMPLATE([PACKAGE_COPYRIGHT_STRING],
        [Official string to use when printing the project's copyright])
AH_TEMPLATE([PACKAGE_LICENCE],
        [Short name or abbreviation for the project's licencse])
AH_TEMPLATE([PACKAGE_LICENCE_DESC],
        [Full, descriptive name of the project's licencse])
AC_DEFINE([PACKAGE_AUTHOR],           "project_author")
AC_DEFINE([PACKAGE_COPYRIGHT_YEAR],   "project_copyright_year")
AC_DEFINE([PACKAGE_COPYRIGHT_STRING], "Copyright (c) project_copyright_year project_author")
AC_DEFINE([PACKAGE_LICENCE],          "project_licence")
AC_DEFINE([PACKAGE_LICENCE_DESC],     "project_licence_desc")


dnl ====================================
dnl ===  General Requirement Checks  ===
dnl ====================================

dnl Checks for compiler features
AX_C___ATTRIBUTE__
AC_C_CONST

dnl Checks for header files.
AC_CHECK_HEADERS([libgen.h stdlib.h string,h])
AC_CHECK_HEADER(gmp.h, ,
  [AC_MSG_ERROR([GNU MP not found, see https://gmplib.org/])])

AC_HEADER_ASSERT

dnl Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

dnl Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([basename memset perror strcspn strdup strtok])
AX_FUNC_GETOPT_LONG
AC_CHECK_FUNCS([getline], ,
  [AC_MSG_ERROR([Cannot find the function getline()])])
AC_CHECK_LIB(gmp, __gmpz_init, ,
  [AC_MSG_ERROR([GNU MP not found, see https://gmplib.org/])])

dnl Export any extra build options
APP_CFLAGS=""
APP_LIBS=""
AC_SUBST(APP_CFLAGS)
AC_SUBST(APP_LIBS)


dnl ================
dnl ===  Output  ===
dnl ================

AC_SUBST(ALL_PKG_CFLAGS)
AC_SUBST(ALL_PKG_LIBS)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

