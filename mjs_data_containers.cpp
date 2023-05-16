#include "mjs_data_containers.h"

#include <utility>

proprietary_function::proprietary_function(std::string identifier, int argc, decltype(body) body) :
    body(std::move(body)), function(std::move(identifier), argc)
{

}

mjs_data* proprietary_function::operator()(std::vector<mjs_data*> actual_params) {
    if (actual_params.size() != argc) throw mjs_runtime_error("Argument count mismatch");

    auto result = body(actual_params);

    return result;
}