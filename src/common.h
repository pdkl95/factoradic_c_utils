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

#ifndef COMMON_H
#define COMMON_H

#include "config.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define QUOTE(x) #x
#define STR(macro) QUOTE(macro)


extern const char *progname;
extern const char *progversion;

/***********************************************/
/***       error reporting & asserts         ***/

#define assert_null(x)     assert((x) == NULL)
#define assert_not_null(x) assert((x) != NULL)

#endif /*COMMON_H*/
