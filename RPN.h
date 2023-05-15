#pragma once

//#include "Parser.h"
#include "mjs_datatypes.h"

#include <vector>

enum class RPN_types : int{
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
    nop,
};

struct RPN_element{
    RPN_types type;
    variable* var_ref;
    function* func_ref;
    constant* const_ref;
    std::vector<RPN_element>::iterator label;
};

class RPN { //reverse polish notation
    std::vector<RPN_element> elements;

public:
    using rpn_edge = typename decltype(elements)::iterator;

    RPN(){
        RPN_element elm = {RPN_types::nop};
        elements.emplace_back(elm);
    }

    rpn_edge push_elm(RPN_element elm) {
        elements.emplace_back(elm);
        return elements.end() - 1;
    }

    rpn_edge get_last_elm() { return elements.end() - 1; }

    bool evaluate();

    std::vector<RPN_element>& get_elements() { return elements; }
};
