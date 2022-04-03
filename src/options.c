/******************************************************************************
 *                                                                            *
 *  This file is part of factoradic_c_utils.                                  *
 *                                                                            *
 *  factoradic_c_utils is free software: you can redistribute it and/or       *
 *  modify it under the terms of the GNU General Public License as published  *
 *  by the Free Software Foundation, either version 3 of the License,         *
 *  or (at your option) any later version.                                    *
 *                                                                            *
 *  factoradic_c_utils is distributed in the hope that it will be useful,     *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General  *
 *  Public License for more details.                                          *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License along   *
 *  with factoradic_c_utils. If not, see <https://www.gnu.org/licenses/>.     *
 *                                                                            *
 ******************************************************************************/

#include "common.h"

#ifdef HAVE_GETOPT_H
# include <getopt.h>
#else
# warning "Missing <getopt.h> - trying to compile with our \"gnugetopt.h\""
# warning "This fallback is untested, and may not work!"
# include "gnugetopt.h"
#endif

#include "options.h"


void
show_usage(
    char *usage_args
) {
    printf("Usage: %s [OPTIONS] %s\n",
           progname, usage_args);
}

void
show_help(
    char *help_text,
    char *usage_args
) {
    show_usage(usage_args);
    printf("%s", help_text);
}

void
show_version(
    void
) {
    printf("%s %s\n", PACKAGE_NAME, PACKAGE_VERSION);
    printf("%s\n", PACKAGE_COPYRIGHT_STRING);
    printf("License %s: %s\n", PACKAGE_LICENCE, PACKAGE_LICENCE_DESC);
    printf("This is free software: you are free to change and redistribute it.\n");
    printf("There is NO WARRANTY, to the extent permitted by law.\n");
    printf("\n");
    printf("Written by %s.\n", PACKAGE_AUTHOR);
    printf("%s\n", PACKAGE_URL);
}

void
options_set_str(
    char **opt,
    const char *src
) {
    assert_not_null(opt);
    assert_not_null(src);

    if (NULL != *opt) {
        free(*opt);
    }

    *opt = strdup(src);
}
