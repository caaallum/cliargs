#ifndef __PARAMS_H
#define __PARAMS_H

#include "arg.h"

struct arg_list_t;

struct arg_list_t *arg_list_init();

arg_bool arg_list_add(struct arg_list_t *al, int count, ...);

void args_init(struct arg_list_t *al, int argc, char **argv);

void args_cleanup(struct arg_list_t *al);

#endif/* !__PARAMS_H */
