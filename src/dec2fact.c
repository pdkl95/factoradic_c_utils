#include "common.h"
#include <getopt.h>
#include <libgen.h>

int
main(
    int   argc,
    char *argv[]
) {
    app_t *app;

    progname = basename(argv[0]);


    bool run_ok = true;

    // do stuff

    if (run_ok) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
