#ifndef __ARG_H
#define __ARG_H

typedef unsigned char arg_bool;
#define arg_true (1)
#define arg_false (2)

struct arg_list_t;

typedef struct {
    char flag;                              /* eg. e */
    char *description;                      /* Description of what the flag does */
    arg_bool has_val;                       /* Boolean to set if the flag is a value */
    void (*callback)(struct arg_list_t *al, const char *val);      /* Function callback for when flag is set.  */
} arg_t;

arg_t *arg_new(char flag, const char *description, arg_bool has_val, void (*callback)(struct arg_list_t *al, const char *val));

void arg_free(arg_t *arg);

#endif/* !__ARG_H */
