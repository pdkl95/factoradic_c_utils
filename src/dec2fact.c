#include "common.h"
#include <getopt.h>
#include <libgen.h>

#include <gmp.h>

bool
convert_decimal_string(
    char *str
) {
    return true;
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
