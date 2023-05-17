#include "proprietary_functions.h"

#include <iostream>
#include <string>
#include <cstdlib>

using std::cout;
using std::endl;

namespace proprietary_functions{
    mjs_data* write(std::vector<mjs_data*> args){
        cout << args[0]->convert_to_string();

        return new mjs_undefined();
    }

    mjs_data* writeln(std::vector<mjs_data*> args){
        cout << args[0]->convert_to_string() << endl;

        return new mjs_undefined();
    }

    mjs_data* get_env(std::vector<mjs_data*> args){
        std::string key = args[0]->convert_to_string();
        auto env = std::getenv(key.c_str());

        if (env == nullptr){
            return new mjs_string("");
        }else return new mjs_string(env);
    }
}