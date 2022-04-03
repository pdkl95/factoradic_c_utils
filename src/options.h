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

#ifndef OPTIONS_H
#define OPTIONS_H

#include "common.h"

void show_usage(char *usage_args);
void show_help(char *help_text, char *usage_args);
void show_version(void);

void options_set_str(char **opt, const char *src);

#endif /*OPTIONS_H*/
