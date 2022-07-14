#include "cliargs/params.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARG_LIST_INIT_CAPACITY 4

typedef struct arg_list_t {
    arg_t **args;
    int total;
    int capacity;

    char *program_name;
} arg_list_t;

static arg_bool
_arg_list_resize(arg_list_t *al, int capacity) {
    arg_t **args = realloc(al->args, sizeof(arg_t *) * capacity);
    if (!args) {
        return arg_false;
    }

    al->args = args;
    al->capacity = capacity;

    return arg_true;
}

static arg_t *
_arg_list_get(arg_list_t *al, int index) {
    if (!al) {
        return NULL;
    }

    if (index >= 0 && index < al->total) {
        return al->args[index];
    }

    return NULL;
}

static arg_bool
_arg_list_add(arg_list_t *al, arg_t *arg) {
    if (!al) {
        return arg_false;
    }

    if (al->capacity == al->total) {
        arg_bool rc = _arg_list_resize(al, al->capacity * 2);
        if (!rc) {
            return rc;
        }
    }

    al->args[al->total++] = arg;

    return arg_true;
}

static void 
_print_help(arg_list_t *al, const char *val __attribute__((unused))) {
    printf("Usage: %s\n", al->program_name);
    for (int i = 0; i < al->total; i++) {
        arg_t *arg = _arg_list_get(al, i);
        printf("\t-%c: %s\n", arg->flag, arg->description);
    }
    exit(0);
}

arg_list_t *
arg_list_init() {
    arg_list_t *al = (arg_list_t *)malloc(sizeof(arg_list_t));

    al->capacity = ARG_LIST_INIT_CAPACITY;
    al->total = 0;
    al->args = malloc(sizeof(arg_t *) * al->capacity);

    _arg_list_add(al, arg_new('h', "Show this help message", arg_false, _print_help));

    return al;
}

arg_bool
arg_list_add(arg_list_t *al, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        arg_t *a = va_arg(args, arg_t *);
        if (!_arg_list_add(al, a)) {
            return arg_false;
        }
    }
    va_end(args);
    return arg_true;
}

void
args_init(arg_list_t *al, int argc, char **argv) {
    al->program_name = (char *)malloc(strlen(argv[0]));
    strcpy(al->program_name, argv[0]);

    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        if (strlen(arg) < 2) {
            continue;
        }
        for (int j = 0; j < al->total; j++) {
            arg_t *a = _arg_list_get(al, j);
            if (arg[1] == a->flag) {
                a->callback(al, a->has_val ? argv[i + 1] : NULL);
                break;
            }
        }
    }
}

void 
args_cleanup(arg_list_t *al) {
    for (int i = 0; i < al->total; i++) {
        arg_t *arg = _arg_list_get(al, i);
        arg_free(arg);
    }

    free(al->args);
    free(al->program_name);

    free(al);
}