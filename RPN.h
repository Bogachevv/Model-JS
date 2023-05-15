#pragma once

#include "Parser.h"

#include <vector>

enum class RPN_types{
    jump_false, jump_true, jump, label,
    variable_ref, function_ref, constant,
    assign, logical_or, logical_and,
    eq, neq, identity, not_identity,
    ls, le, gr, ge,
    bin_plus, bin_minus,
    mul, div, mod,
    logical_not, un_plus, un_minus, prefix_pp, prefix_mm, rpn_typeof,
    postfix_pp, postfix_mm,
    field_access, field_expr_access,
};

struct RPN_element{
    RPN_types type;
    variable* var_ref;
    function* func_ref;
    constant* const_ref;
};

class RPN { //reverse polish notation
    std::vector<RPN_element> elements;

public:
    RPN() = default;

    void push_elm(RPN_element elm) {elements.emplace_back(elm);}

    bool evaluate();
};
