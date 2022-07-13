#ifndef __PARAMS_H
#define __PARAMS_H

#include <string>
#include <vector>

namespace cli_params {
    struct arg {
        std::vector<std::string> keys;
        std::string description;
        std::string name;
        std::string *val;
        void (*callback)(void *);
    }

    typedef std::vector<arg> args;

    void init(int argc, char **argv, const args &args);
}

#endif//!__PARAMS_H