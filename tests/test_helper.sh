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

bail_out()
{
    echo "Bail out! $*"
    exit 1
}

TEST_PROG=''
TEST_COUNT=0
TEST_RV=0

set_test_program()
{
    TEST_PROG="${builddir}/$1"

    if ! test -e "${TEST_PROG}" ; then
        bail_out "Test program \"${TEST_PROGRAM}\" does not exist!"
    fi

    if ! test -f "${TEST_PROG}" ; then
        bail_out "Test program \"${TEST_PROGRAM}\" exists, but it isn't a regular file!"
    fi

    if ! test -x "${TEST_PROG}" ; then
        bail_out "Test program \"${TEST_PROGRAM}\" exists, but does not have execute permission!"
    fi   
}

end_of_tests()
{
    echo "1..${TEST_COUNT}"

    exit ${TEST_RV}
}

increment_test_count()
{
    TEST_COUNT=$(expr ${TEST_COUNT} + 1)
}

pass_test()
{
    increment_test_count
    echo "ok ${TEST_COUNT}"
}

fail_test()
{
    increment_test_count
    TEST_RV=1
    echo "not ok ${TEST_COUNT} # $*"
}

assert_output()
{
    expected_output="$1"
    shift

    # run the test program and capture its outut
    output="$("${TEST_PROG}" "$@")"
    rv=$?

    if ! test ${rv} -eq 0 ; then
        fail_test "test program ${TEST_PROG} exited with error code ${rv}"
        return
    fi

    if test "${output}" = "${expected_output}" ; then
        pass_test
    else
        fail_test "expected ${TEST_PROG} to output \"${expected_output}\" but it printed \"${output}\""
    fi
}
