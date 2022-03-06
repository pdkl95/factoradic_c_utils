#ifndef OPTIONS_H
#define OPTIONS_H

#include "common.h"

void show_usage(char *usage_args);
void show_help(char *help_text, char *usage_args);
void show_version(void);

void options_set_str(char **opt, const char *src);

#endif /*OPTIONS_H*/
