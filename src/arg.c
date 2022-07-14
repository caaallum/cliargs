#include "cliargs/arg.h"
#include <stdlib.h>
#include <string.h>

arg_t *
arg_new(char flag, const char *description, arg_bool has_val, void (*callback)(struct arg_list_t *al, const char *val)) {
    arg_t *arg = (arg_t *)malloc(sizeof(arg_t));

    arg->flag = flag;
    arg->description = (char *)malloc(strlen(description));
    strcpy(arg->description, description);

    arg->has_val = has_val;
    arg->callback = callback;

    return arg;
}

void 
arg_free(arg_t *arg) {
    free(arg->description);

    free(arg);
}