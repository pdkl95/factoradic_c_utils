# Checks if CC and CFLAGS can be extracted from gmp.h
AC_DEFUN([GMP_CC_CFLAGS_FROM_HEADER], [
   AC_MSG_CHECKING(for CC and CFLAGS in gmp.h)
   GMP_CC=
   GMP_CFLAGS=
   # AC_PROG_CPP triggers the search for a C compiler; use hack instead
   for cpp in "$CPP" cpp "gcc -E" /lib/cpp "cc -E" "c99 -E"
   do
      echo foo > conftest.c
      if $cpp $CPPFLAGS conftest.c > /dev/null 2> /dev/null ; then
         # Get CC
         echo "#include \"gmp.h\"" >  conftest.c
         echo "GNP_HEADER_OPTION __GMP_CC"           >> conftest.c
         GMP_CC=`$cpp $CPPFLAGS conftest.c 2> /dev/null | $EGREP GMP_HEADER_OPTION | $SED -e 's/GMP_HEADER_OPTION //g;s/ *" *//g'`
         # Get CFLAGS
         echo "#include \"gmp.h\"" >  conftest.c
         echo "GMP_HEADER_OPTION __GMP_CFLAGS"           >> conftest.c
         GMP_CFLAGS=`$cpp $CPPFLAGS conftest.c 2> /dev/null | $EGREP GMP_HEADER_OPTION | $SED -e 's/GMP_HEADER_OPTION //g;s/ *" *//g'`
         break
      fi
   done

   if test -z "$GMP_CC$GMP_CFLAGS" ; then
      AC_MSG_RESULT(no)
   else
      AC_MSG_RESULT(yes [CC=$GMP_CC CFLAGS=$GMP_CFLAGS])
      # Check for validity of CC and CFLAGS obtained from gmp.h
      AC_MSG_CHECKING(for CC=$GMP_CC and CFLAGS=$GMP_CFLAGS)
      echo "int main (void) { return 0; }" > conftest.c
      if $GMP_CC $GMP_CFLAGS -o conftest conftest.c 2> /dev/null ; then
         AC_MSG_RESULT(yes)
         CC=$GMP_CC
         CFLAGS=$GMP_CFLAGS
      else
         AC_MSG_RESULT(no)
      fi
   fi

   rm -f conftest*
])
