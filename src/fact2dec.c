#include "common.h"

#include <stdio.h>
#include <limits.h>

#include <getopt.h>
#include <libgen.h>

#include <gmp.h>

char *delim = ",";

bool
convert_factoradic_string(
    char *factoradic_string
) {
    bool rv = true;
    char *tmpstr = NULL;
    char *token = NULL;
    char *endptr = NULL;
    size_t num_places = 0;
    long *place_values = NULL;
    long *p = NULL;

    /* first count the number of split place values */
    tmpstr = strdup(factoradic_string);
    token = strtok(tmpstr, delim);
    while (token != NULL) {
        num_places++;
        token = strtok(NULL, delim);
    }
    free(tmpstr);

    place_values = calloc(num_places, sizeof(long));

    /* ...then convert the split values into ints */
    tmpstr = strdup(factoradic_string);
    token = strtok(tmpstr, delim);
    p = place_values;
    while (token != NULL) {
        long value = strtol(token, &endptr, 10);

        if ((errno == ERANGE && (value == LONG_MAX || value == LONG_MIN))
            || (errno != 0 && value == 0)) {
            perror("strtol");
            rv = false;
            goto cleanup;
        }

        if (endptr == token) {
            fprintf(stderr, "No digits were found\n");
            rv = false;
            goto cleanup;
        }

        *p = value;

        p++;
        token = strtok(NULL, delim);
    }

  cleanup:
    free(place_values);
    free(tmpstr);

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
        if (!convert_factoradic_string(argv[i])) {
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
