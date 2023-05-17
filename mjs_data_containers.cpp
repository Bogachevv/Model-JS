#include "mjs_data_containers.h"
#include "RPN.h"

#include <utility>
#include <algorithm>
#include <unordered_map>


proprietary_function::proprietary_function(std::string identifier, int argc, decltype(body) body) :
    body(std::move(body)), function(std::move(identifier), argc)
{

}

mjs_data* proprietary_function::operator()(std::vector<mjs_data*> actual_params) {
    if (actual_params.size() != argc) throw mjs_runtime_error("Argument count mismatch");

    auto result = body(actual_params);

    return result;
}

mjs_data *custom_function::operator()(std::vector<mjs_data*> actual_params) {
    std::unordered_map<std::string, mjs_data*> args_processor;

    for (auto elm: body->get_elements()){
        if (elm.type != RPN_types::variable_ref) continue;
        auto it = args_processor.find(elm.var_ref->identifier);
        if (args_processor.find(elm.var_ref->identifier) == args_processor.end()) continue;
        elm.var_ref->data = it->second;
    }

    return body->evaluate();
}