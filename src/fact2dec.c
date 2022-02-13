#include "common.h"
#include <getopt.h>
#include <libgen.h>

#include <gmp.h>

int
main(
    int   argc,
    char *argv[]
) {
    progname = basename(argv[0]);

    bool run_ok = true;

    // do stuff

    if (run_ok) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
