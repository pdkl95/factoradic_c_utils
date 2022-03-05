#include "common.h"
#include <getopt.h>
#include <libgen.h>

#include <gmp.h>

char *delim = ":";

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
            fprintf(stdout, "%s", delim);
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

    bool run_ok = true;

    // do stuff
    for (int i=1; i<argc; i++) {
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
