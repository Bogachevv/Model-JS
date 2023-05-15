#include "Parser_first_functions.h"
#include "Parser_utils.h"

const std::unordered_set<lexeme_type>& S_first(){
    static std::unordered_set<lexeme_type> S_first_set;
    if (S_first_set.empty()){
        S_first_set = merge_sets({Func_first(), Oper_first()});
    }

    return S_first_set;
}

const std::unordered_set<lexeme_type>& Func_first(){
    static const std::unordered_set<lexeme_type> Func_first_set = {lexeme_type::function};

    return Func_first_set;
}

const std::unordered_set<lexeme_type>& Oper_first(){
    static std::unordered_set<lexeme_type> Oper_first_set;
    if (Oper_first_set.empty()){
        Oper_first_set = merge_sets({Var_first(), Empty_first(), Scope_first(), If_first(),
                                     Loop_first(), Jump_first(), OpExpr_first()});
    }

    return Oper_first_set;
}

const std::unordered_set<lexeme_type>& Var_first(){
    static const std::unordered_set<lexeme_type> Var_first_set = {lexeme_type::var};

    return Var_first_set;
}

const std::unordered_set<lexeme_type>& Empty_first(){
    static const std::unordered_set<lexeme_type> Empty_first_set = {lexeme_type::semicolon};

    return Empty_first_set;
}

const std::unordered_set<lexeme_type>& Scope_first(){
    static const std::unordered_set<lexeme_type> Scope_first_set = {lexeme_type::left_brace};

    return Scope_first_set;
}

const std::unordered_set<lexeme_type>& If_first(){
    static const std::unordered_set<lexeme_type> Scope_first_set = {lexeme_type::left_brace};

    return Scope_first_set;
}

const std::unordered_set<lexeme_type>& Loop_first(){
    static const std::unordered_set<lexeme_type> Loop_first_set =
            {lexeme_type::mjs_while, lexeme_type::mjs_for, lexeme_type::mjs_do};

    return Loop_first_set;
}

const std::unordered_set<lexeme_type>& Jump_first(){
    static const std::unordered_set<lexeme_type> Jump_first_set =
            {lexeme_type::mjs_break, lexeme_type::mjs_continue, lexeme_type::mjs_return};

    return Jump_first_set;
}

const std::unordered_set<lexeme_type>& OpExpr_first(){
    return Expr_first();
}

const std::unordered_set<lexeme_type>& Const_first(){
    static const std::unordered_set<lexeme_type> Const_first_set =
            {lexeme_type::number, lexeme_type::string,
             lexeme_type::mjs_true, lexeme_type::mjs_false};

    return Const_first_set;
}

const std::unordered_set<lexeme_type>& Expr_first(){
    return E1_first();
}

const std::unordered_set<lexeme_type>& E1_first(){
    return E2_first();
}

const std::unordered_set<lexeme_type>& E2_first(){
    return E3_first();
}

const std::unordered_set<lexeme_type>& E3_first(){
    return E4_first();
}

const std::unordered_set<lexeme_type>& E4_first(){
    return E5_first();
}

const std::unordered_set<lexeme_type>& E5_first(){
    return E6_first();
}

const std::unordered_set<lexeme_type>& E6_first(){
    return E7_first();
}

const std::unordered_set<lexeme_type>& E7_first(){
    return E8_first();
}

const std::unordered_set<lexeme_type>& E8_first(){
    static std::unordered_set<lexeme_type> E8_first_set;
    if (E8_first_set.empty()){
        E8_first_set = {lexeme_type::mjs_not, lexeme_type::plus, lexeme_type::minus,
                        lexeme_type::plus_plus, lexeme_type::minus_minus};
        E8_first_set = merge_sets({E8_first_set, E9_first()});
    }

    //TODO:
    // add typeof

    return E8_first_set;
}

const std::unordered_set<lexeme_type>& E9_first(){
    return E10_first();
}

const std::unordered_set<lexeme_type>& E10_first(){
    static std::unordered_set<lexeme_type> E10_first_set;
    if (E10_first_set.empty()){
        E10_first_set = {lexeme_type::identifier};
        E10_first_set = merge_sets({E10_first_set, E11_first()});
    }

    return E10_first_set;
}

const std::unordered_set<lexeme_type>& E11_first(){
    static std::unordered_set<lexeme_type> E11_first_set;
    if (E11_first_set.empty()){
        E11_first_set = {lexeme_type::left_parenthesis};
        E11_first_set = merge_sets({E11_first_set, Const_first()});
    }

    return E11_first_set;
}