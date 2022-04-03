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
#include "options.h"

#include <stdio.h>
#include <getopt.h>
#include <libgen.h>

#include <gmp.h>



#define DEFAULT_DELIMETER ":"

char *delimiter = NULL;

static char short_options[] = "d:Vh";

static struct option long_options[] = {
    { "delimiter", required_argument, 0, 'A' },
    {   "version",       no_argument, 0, '.' },
    {      "help",       no_argument, 0, 'h' },
    {           0,                 0, 0,  0  }
};

static char usage_args[] = ">decimal_integer> [...]";

static char help_text[] =
    "\n"
    "A utility that converts integers written in\n"
    "decimal (base 10) into factorial base.\n"
    "\n"
    "OPTIONS\n"
    "  -d, --delimiter             Set the character that separates\n"
    "                                the places in factorial bass numbers.\n"
    "                                (default: \":\")\n"
    "\n"
    "      --version               Show version information and exit\n"
    "  -h, --help                  Show this help and exit\n"
    ;


static bool
parse_args(
    int argc,
    char *argv[]
) {
    int c;

    for (;;) {
        int option_index = 0;

        c = getopt_long(argc, argv, short_options, long_options, &option_index);

        if (-1 == c) {
            break;
        }

        switch (c) {
        case 'd':
            options_set_str(&delimiter, optarg);
            break;

        case 'V':
            show_version();
            exit(0);
            break;

        case 'h':
            show_help(help_text, usage_args);
            exit(0);
            break;

        default:
            fprintf(stderr, "ERROR: getopt returned character code 0%o", c);
            return false;
        }
    }

    return true;
}

struct stack_node {
    unsigned long int data;
    struct stack_node *next;
};

struct stack_node *
new_stack_node(
    unsigned long int data
) {
    struct stack_node *node = malloc(sizeof(struct stack_node));
    node->data = data;
    node->next = NULL;
    return node;
}

void
stack_push(
    struct stack_node **root,
    unsigned long int data
) {
    struct stack_node *node = new_stack_node(data);\
    node->next = *root;
    *root = node;
}

bool
convert_decimal_string(
    char *str
) {
    bool rv = true;
    bool first = true;

    struct stack_node *stack_root = NULL;

    mpz_t value, divisor, zero, q, r;
    mpz_init(value);
    mpz_init(divisor);
    mpz_init(zero);
    mpz_init(q);
    mpz_init(r);

    if (-1 == mpz_set_str(value, str, 10)) {
        fprintf(stderr, "ERROR: input string is not a base 10 integer: \"%s\"\n", str);
        rv = false;
        goto cleanup;
    }

    mpz_set(q, value);
    mpz_set_ui(divisor, (unsigned long int)2);

    stack_push(&stack_root, (unsigned long int)0);

    while (mpz_cmp(q, zero) > 0) {
        mpz_fdiv_qr(q, r, q, divisor);

        stack_push(&stack_root, mpz_get_ui(r));

        mpz_add_ui(divisor, divisor, (unsigned long int)1);
    }

    while (stack_root != NULL) {
        struct stack_node *tmp = stack_root;
        stack_root = stack_root->next;

        if (first) {
            first = false;
        } else {
            fprintf(stdout, "%s", delimiter);
        }

        fprintf(stdout, "%ld", tmp->data);

        free(tmp);
    }

    fprintf(stdout, "\n");

  cleanup:
    mpz_clear(r);
    mpz_clear(q);
    mpz_clear(zero);
    mpz_clear(divisor);
    mpz_clear(value);

    return rv;
}

int
main(
    int   argc,
    char *argv[]
) {
    progname = basename(argv[0]);

    delimiter = strdup(DEFAULT_DELIMETER);

    /* configure options */
    if (!parse_args(argc, argv)) {
        fprintf(stderr, "ERROR: bad args");
        return EXIT_FAILURE;
    }

    bool run_ok = true;

    /* convert numbers */
    for (int i=optind; i<argc; i++) {
        if (!convert_decimal_string(argv[i])) {
            fprintf(stderr, "ERROR: could not convert \"%s\".\n", argv[i]);
            run_ok = false;
            break;
        }
    }

    if (run_ok) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
