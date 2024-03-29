#!/bin/bash

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


cat <<EOF
###############################################
###                                         ###
###  /-----------------------------------\  ###
###  | Not intended as a real benchmark! |  ###
###  \-----------------------------------/  ###
###                                         ###
###     (I just wanted a rough speesd       ###
###      comparison between Ruby and C)     ###
###                                         ###
###############################################

EOF

LC_ALL=C
export LC_ALL
LANGUAGE=C
export LANGUAGE

if type getopt 2>&1 >/dev/null ; then
    # have GNU getopt (allows nicer options)
    SOPT="h"
    LOPT="help"
    OPTIONS=$(getopt -o "$SOPT" --long "$LOPT" -n "$SELFNAME" -- "$@") || exit 1
    eval set -- "$OPTIONS"
fi

while true ; do
    case "$1" in
        -h | --help)    show_usage   ;  exit 0 ;;
        --) shift ; break ;;
        -*) echo "bad opt: $1" ; exit 1 ;;
        *)  break ;;
    esac
done

for arg in "$@" ; do
    case "${arg}" in
        *=?*) optarg=`expr "X${arg}" : '[^=]*=\(.*\)'` ;;
        *=)   optarg= ;;
        *)    optarg=yes ;;
    esac

    case "${arg}" in
        *=*)
            envvar=`expr "x${arg}" : 'x\([^=]*\)='`
            if [[ "${envvar}" =~ ^[A-Z]+$ ]] ; then
               eval $envvar=\$optarg
            fi
            ;;

        *)
            echo "bad arg: ${arg}"
            exit 1
            ;;
    esac
done

: ${SKIP:=}
: ${N:=2000}
: ${FACTORADIC:=factoradic}
: ${GCC:=gcc}
: ${CLANG:=clang}

echo "# <config>"
declare -p SKIP N FACTORADIC GCC CLANG

FACTVALUE="256,181,382,250,417,105,148,94,220,219,290,193,126,393,317,38,359,351,21,230,317,226,298,315,206,364,34,285,21,327,187,336,266,0,334,231,82,309,248,305,300,102,201,321,315,105,36,155,146,81,120,158,24,227,156,284,364,219,157,319,202,309,355,198,126,78,353,247,220,9,152,81,237,122,91,5,345,206,181,93,257,280,231,57,288,314,316,93,193,360,239,196,341,333,56,91,325,3,204,289,320,280,80,173,314,211,322,53,39,105,151,227,237,107,42,95,300,161,263,60,294,39,108,32,132,181,290,43,315,211,8,30,155,224,30,252,73,110,65,157,63,177,236,32,173,201,94,166,108,215,249,125,101,77,10,153,155,222,110,9,154,66,209,27,184,102,43,206,13,178,120,185,162,112,214,37,50,32,188,255,151,107,156,184,180,51,215,8,10,54,248,173,170,233,46,228,187,35,238,212,101,221,73,115,188,111,99,32,241,40,211,121,223,21,131,96,121,123,180,32,222,142,174,140,193,182,145,167,115,59,205,107,188,178,195,52,48,67,191,172,204,122,206,199,1,34,167,44,156,180,83,149,156,53,116,157,130,52,43,91,172,22,70,87,149,104,34,178,115,86,71,86,112,136,94,171,137,74,159,129,118,57,18,145,112,51,4,78,116,57,108,7,41,14,84,148,90,8,143,110,66,89,140,83,88,4,105,12,82,73,89,63,6,94,12,61,14,92,88,95,86,54,120,61,6,3,9,122,39,45,86,2,56,49,68,31,85,9,64,50,32,58,32,48,64,62,72,68,77,36,15,73,77,49,20,19,11,84,81,74,54,54,33,25,18,35,56,57,62,19,22,47,23,13,53,36,28,60,49,11,24,28,9,66,35,43,9,60,6,29,40,13,9,36,8,48,36,44,38,25,29,19,42,26,41,7,26,10,25,4,17,0,20,3,9,5,30,20,4,8,11,8,19,4,20,8,7,10,16,18,13,16,9,2,0,9,12,3,3,4,7,0,7,4,0,3,3,0,0,0"

DECVALUE="9876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210"

echo
echo "# <DATA>"
declare -p DECVALUE FACTVALUE
echo
echo -n -e "length of DECVALUE:\t"
echo -n "$DECVALUE" | wc -c
echo -n -e "length of FACTVALUE:\t"
echo -n "$FACTVALUE" | tr -c -d ',' | wc -c
echo

####################
###  Benchmarks  ###
####################

# A simple comparison of converting a 1000-digit decimal number into
# factorial base 1000 times.

bench() {
    local name="$1"
    shift
    local cmd="$1"

    if skip "${name}" ; then
        echo "# skipping test (SKIP=${name})"
        return 0
    fi

    echo "# running test \"${name}\""
    echo time bash -c "'${cmd}'"
    time bash -c "${cmd}"
}

nbench() {
    local name="$1"
    shift

    bench "${name}" "for i in \$(seq ${N}) ; do $* >/dev/null ; done"
}

skip() {
    local query="$1" IFS LIST

    while IFS="," read -ra LIST ; do
        for i in "${LIST[@]}" ; do
            if [[ "${i}" = "${query}" ]] ; then
                return 0
            fi
        done
    done <<< "${SKIP}"

    return 1
}

### Ruby factoradic gem ###

bench_ruby() {
    nbench dec2fact "factoradic --d2f \"${DECVALUE}\""
    nbench fact2dec "factoradic --f2d -s ',' \"${FACTVALUE}\""
}

echo
echo "### benchmark <ruby>"
if skip ruby ; then
    echo '# skipping tests (SKIP=ruby)'
else
    if command -v factoradic >/dev/null ; then
        bench_ruby
    else
        echo '# ERROR: the "factoradic" program is not in the $PATH'
        echo '#        Is the ruby gem installed?'
        echo '#        (maybe try "gem install factoradic"?)'
    fi
fi

### Compiled C using libgmp ###

run_cmd() {
    local cmd="$1" ; shift
    echo "${cmd} $@"
    "${cmd}" "$@" >/dev/null
}

prepare_bench_c() {
    local mode="$1" ccpath="$2"

    if [[ -f Makefile ]] ; then
        echo "# cleaning existing configuration..."
        run_cmd make distclean
    fi

    echo "# configuring build to use \"${mode}\" as the compiler..."
    run_cmd ./configure --disable-debug --disable-assert CC="${ccpath}"
    echo "# building"
    if ! run_cmd make ; then
        echo "# ERROR: build failed"
        return 1
    fi
}

run_bench_c() {
    nbench dec2fact "./dec2fact \"${DECVALUE}\""
    nbench fact2dec "./fact2dec \"${FACTVALUE}\""
}

bench_c() {
    local mode="$1" ccpath="$2"

    echo
    echo "### benchmark <C: ${mode}> CC='${ccpath}'"
    if skip "${mode}" ; then
        echo "# not running (SKIP=${mode})"
    else
        if skip binrebuild ; then
            echo "# WARNING: skipping rebuilding the C binaries (SKIP=binrebuild)"
        else
            prepare_bench_c "${mode}" "${ccpath}"
        fi
        run_bench_c
    fi
}

echo
echo "### benchmark <C> variations"
if skip c ; then
    echo '# not running (SKIP=c)'
else
    bench_c gcc   "${GCC}"
    bench_c clang "${CLANG}"
fi

echo
echo "### end of benchmarks"
