#ifndef COMMON_H
#define COMMON_H

#include "config.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define QUOTE(x) #x
#define STR(macro) QUOTE(macro)


extern const char *progname;
extern const char *progversion;

/***********************************************/
/***       error reporting & asserts         ***/

#define assert_null(x)     assert((x) == NULL)
#define assert_not_null(x) assert((x) != NULL)

#endif /*COMMON_H*/
