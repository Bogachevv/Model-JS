#pragma once

#include "mjs_data_containers.h"
#include "unordered_map"

namespace proprietary_functions{
    static std::unordered_map<std::string, int> argc_map = {{"write", 1}, {"writeln", 1}, {"get_env", 1}};

    mjs_data* write(std::vector<mjs_data*>);

    mjs_data* writeln(std::vector<mjs_data*>);

    mjs_data* get_env(std::vector<mjs_data*>);
}