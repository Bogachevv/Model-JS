#include "Parser.h"
#include "Parser_utils.h"
#include "Parser_first_functions.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>


struct parse_error : std::runtime_error{
    explicit parse_error(const std::string& msg) : std::runtime_error(msg) {}
};

parser::parser(const std::string& path) : lex(path), cur("") {
    cur = lex.get_lex();
    function_args_processing = false;
    arg_counter = 0;
}

void parser::error() {
    error("Unexpected lexeme" + cur.get_body());
}

void parser::error(const std::string &msg) {
    throw parse_error(msg);
}

bool parser::next(bool silent) {
//    if (lex.is_empty()) {
//        if (silent) return false;
//        throw parse_error("Unexpected end of file");
//    }
    cur = lex.get_lex();
    return cur.get_type() == lexeme_type::eof;
}

bool parser::analyze() {
    try{
        while (cur.get_type() != lexeme_type::eof) S();
    }
    catch (parse_error& err) {
        std::cout << err.what() << std::endl;
        return false;
    }

    return true;
}

void parser::S() {
    if (in_set(Func_first(), cur.get_type())) Func();
    else if (in_set(Oper_first(), cur.get_type())) Oper();
    else error();
}

void parser::Func() {
    if (cur.get_type() != lexeme_type::function) error();
    next();
    if (cur.get_type() != lexeme_type::identifier) error();
    function new_func(cur.get_body(), 0);
    if (functions.find(cur.get_body()) != functions.end()) error("redefining a function");
    std::cout << "Declaring function " << cur.get_body() << " with args: ";
    next();
    if (cur.get_type() != lexeme_type::left_parenthesis) error();
    next();

    if (cur.get_type() == lexeme_type::identifier){
        std::cout << cur.get_body();
        new_func.argc += 1;
        next();

        while (cur.get_type() == lexeme_type::comma){
            next();
            if (cur.get_type() != lexeme_type::identifier) error();
            new_func.argc += 1;
            std::cout << ", " << cur.get_body();
            next();
        }
    }

    if (cur.get_type() != lexeme_type::right_parenthesis) error();
    next();

    functions.emplace(new_func.identifier, new_func);

    std::cout << std::endl;

    if (in_set(Scope_first(), cur.get_type())) Scope();
    else error();
}

void parser::Oper() {
    if (in_set(Var_first(), cur.get_type())) return Var();
    if (in_set(Empty_first(), cur.get_type())) return Empty();
    if (in_set(Scope_first(), cur.get_type())) return Scope();
    if (in_set(If_first(), cur.get_type())) return If();
    if (in_set(Loop_first(), cur.get_type())) return Loop();
    if (in_set(Jump_first(), cur.get_type())) return Jump();
    if (in_set(OpExpr_first(), cur.get_type())) return OpExpr();
    error();
}

void parser::Var() {
    if (cur.get_type() != lexeme_type::var) error();
    next();

    if (cur.get_type() != lexeme_type::identifier) error();
    if (variables.find(cur.get_body()) == variables.end()){ //create new variable
        variables.emplace(cur.get_body(), variable(cur.get_body(), ""));
    } else error("redefining a variable" + cur.get_body());
    next();


    if (cur.get_type() == lexeme_type::assign){ // <Name> = <Expr>
        next();
        if (in_set(Expr_first(), cur.get_type())) Expr();
        else error();
    }

    while (cur.get_type() == lexeme_type::comma){
        next();

        if (cur.get_type() != lexeme_type::identifier) error();
        if (variables.find(cur.get_body()) == variables.end()){ //create new variable
            variables.emplace(cur.get_body(), variable(cur.get_body(), ""));
        } else error("redefining a variable" + cur.get_body());
        next();

        if (cur.get_type() == lexeme_type::assign){ // <Name> = <Expr>
            next();
            if (in_set(Expr_first(), cur.get_type())) Expr();
            else error();
        }
    }

    if (cur.get_type() != lexeme_type::semicolon) error();
    next();
}

void parser::Empty() {
    if (cur.get_type() != lexeme_type::semicolon) error();
    next();
}

void parser::Scope() {
    if (cur.get_type() != lexeme_type::left_brace) error();
    next();

    if (in_set(Oper_first(), cur.get_type())) Oper();
    else error();

    while (in_set(Oper_first(), cur.get_type())){
        Oper();
    }

    if (cur.get_type() != lexeme_type::right_brace) error();
    next();
}

void parser::If() {
    if (cur.get_type() != lexeme_type::mjs_if) error();
    next();
    if (cur.get_type() != lexeme_type::left_parenthesis) error();
    next();
    if (in_set(Expr_first(), cur.get_type())) Expr();
    else error();
    if (cur.get_type() != lexeme_type::right_parenthesis) error();
    next();
    if (in_set(Oper_first(), cur.get_type())) Oper();
    else error();

    if (cur.get_type() == lexeme_type::mjs_else){
        next();
        if (in_set(Oper_first(), cur.get_type())) Oper();
        else error();
    }
}

void parser::Loop() {
    if (cur.get_type() == lexeme_type::mjs_while){
        next();
        if (cur.get_type() != lexeme_type::left_parenthesis) error();
        next();
        if (in_set(Expr_first(), cur.get_type())) Expr();
        else error();
        if (cur.get_type() != lexeme_type::right_parenthesis) error();
        next();
        if (in_set(Oper_first(), cur.get_type())) Oper();
        else error();
    }
    else if (cur.get_type() == lexeme_type::mjs_for){
        next();
        if (cur.get_type() != lexeme_type::left_parenthesis) error();
        next();

        if (cur.get_type() != lexeme_type::semicolon){ //Expr1
            if (in_set(Expr_first(), cur.get_type())) Expr();
            else error();
            if (cur.get_type() != lexeme_type::semicolon) error();
            next();
        } else next();

        if (cur.get_type() != lexeme_type::semicolon){ //Expr2
            if (in_set(Expr_first(), cur.get_type())) Expr();
            else error();
            if (cur.get_type() != lexeme_type::semicolon) error();
            next();
        } else next();

        if (cur.get_type() != lexeme_type::right_parenthesis){ //Expr3
            if (in_set(Expr_first(), cur.get_type())) Expr();
            else error();
            if (cur.get_type() != lexeme_type::right_parenthesis) error();
            next();
        } else next();

        if (in_set(Oper_first(), cur.get_type())) Oper();
        else error();
    }
    else if (cur.get_type() == lexeme_type::mjs_do){
        next();
        if (in_set(Oper_first(), cur.get_type())) Oper();
        else error();

        if (cur.get_type() != lexeme_type::mjs_while) error();
        next();
        if (cur.get_type() != lexeme_type::left_parenthesis) error();
        next();
        if (in_set(Expr_first(), cur.get_type())) Expr();
        else error();
        if (cur.get_type() != lexeme_type::right_parenthesis) error();
        next();

        if (cur.get_type() != lexeme_type::semicolon) error();
        next();
    }
    else error();
}

void parser::Jump() {
    switch (cur.get_type()) {
        case lexeme_type::mjs_break:
        case lexeme_type::comma:
            next();
            break;
        case lexeme_type::mjs_return:
            next();
            if (in_set(Expr_first(), cur.get_type())) Expr();
            break;
        default:
            error();
    }
    if (cur.get_type() != lexeme_type::semicolon) error();
    next();
}

void parser::OpExpr() {
    if (in_set(Expr_first(), cur.get_type())) Expr();
    else error();
}

void parser::Const() {
    switch (cur.get_type()) {
        case lexeme_type::string:
        case lexeme_type::number:
        case lexeme_type::mjs_false:
        case lexeme_type::mjs_true:
            next();
            break;
        default:
            error();
    }
}

void parser::Expr() {
    if (in_set(E1_first(), cur.get_type())) E1();
    else error();
    if (function_args_processing) ++arg_counter;

    while (cur.get_type() == lexeme_type::comma){
        next();
        if (in_set(E1_first(), cur.get_type())) E1();
        else error();
        if (function_args_processing) ++arg_counter;
    }
}

void parser::E1() {
    if (in_set(E2_first(), cur.get_type())) E2();
    else error();

    while (cur.get_type() == lexeme_type::assign){
        next();
        if (in_set(E2_first(), cur.get_type())) E2();
        else error();
    }
}

void parser::E2() {
    if (in_set(E3_first(), cur.get_type())) E3();
    else error();

    while (cur.get_type() == lexeme_type::mjs_or){
        next();
        if (in_set(E3_first(), cur.get_type())) E3();
        else error();
    }
}

void parser::E3() {
    if (in_set(E4_first(), cur.get_type())) E4();
    else error();

    while (cur.get_type() == lexeme_type::mjs_and){
        next();
        if (in_set(E4_first(), cur.get_type())) E4();
        else error();
    }
}

void parser::E4() {
    if (in_set(E5_first(), cur.get_type())) E5();
    else error();

    switch (cur.get_type()) {
        case lexeme_type::eq:
        case lexeme_type::neq:
            next();
            if (in_set(E5_first(), cur.get_type())) E5();
            else error();
            break;

        default:
            break;
    }

    //TODO:
    //  add ===, !==

}

void parser::E5() {
    if (in_set(E6_first(), cur.get_type())) E6();
    else error();

    switch (cur.get_type()) {
        case lexeme_type::ls:
        case lexeme_type::le:
        case lexeme_type::gr:
        case lexeme_type::ge:
            next();
            if (in_set(E6_first(), cur.get_type())) E6();
            else error();
            break;

        default:
            break;
    }
}

void parser::E6() {
    if (in_set(E7_first(), cur.get_type())) E7();
    else error();

    switch (cur.get_type()) {
        case lexeme_type::plus:
        case lexeme_type::minus:
            next();
            if (in_set(E7_first(), cur.get_type())) E7();
            else error();
            break;

        default:
            break;
    }
}

void parser::E7() {
    if (in_set(E8_first(), cur.get_type())) E8();
    else error();

    switch (cur.get_type()) {
        case lexeme_type::mul:
        case lexeme_type::div:
        case lexeme_type::mod:
            next();
            if (in_set(E8_first(), cur.get_type())) E8();
            else error();
            break;

        default:
            break;
    }
}

void parser::E8() {
    bool loop_cond = true;
    while (loop_cond){
        switch (cur.get_type()) {
            case lexeme_type::mjs_not:
            case lexeme_type::plus:
            case lexeme_type::minus:
            case lexeme_type::plus_plus:
            case lexeme_type::minus_minus:
                next();
                break;
            default:
                loop_cond=false;
                break;
        }
    }

    if (in_set(E9_first(), cur.get_type())) E9();
    else error();
}

void parser::E9() {
    if (in_set(E10_first(), cur.get_type())) E10();
    else error();

    switch (cur.get_type()) {
        case lexeme_type::plus_plus:
        case lexeme_type::minus_minus:
            next();
            break;
        default:
            break;
    }
}

void parser::E10() {
    if (cur.get_type() == lexeme_type::identifier){
        std::string name = cur.get_body();
        next();
        switch (cur.get_type()) {
            case lexeme_type::left_parenthesis:
                next();
                //function call
                if (functions.find(name) == functions.end()) error("Call undeclared function " + name);
                else std::cout << "Call function " << name << std::endl;
                if (arg_counter != 0) {
                    arg_counter_stack.push(arg_counter);
                    arg_counter = 0;
                } else arg_counter_stack.push(0);
                function_args_processing = true;
                if (in_set(Expr_first(), cur.get_type())) Expr();
                else error();
                if (cur.get_type() != lexeme_type::right_parenthesis) error();
                next();
                if (arg_counter == functions.find(name)->second.argc){
                    //function call
                }
                else error("Arguments count mismatch: expected " +
                            std::to_string(functions.find(name)->second.argc) +
                            ", got " + std::to_string(arg_counter));
                arg_counter = arg_counter_stack.top();
                arg_counter_stack.pop();
                if (arg_counter == 0) function_args_processing = false;
                break;
            case lexeme_type::left_square_b:
                next();
                if (in_set(Expr_first(), cur.get_type())) Expr();
                else error();
                if (cur.get_type() != lexeme_type::right_square_b) error();
                next();
                break;
            default:
                if (variables.find(name) == variables.end()) error("Using undeclared variable " + name);
                else std::cout << "Operation with variable " << name << std::endl;
                break;
        }
    }
    else if (in_set(E11_first(), cur.get_type())) E11();
    else error();
}

void parser::E11() {
    if (cur.get_type() == lexeme_type::left_parenthesis){
        next();
        if (in_set(Expr_first(), cur.get_type())) Expr();
        if (cur.get_type() != lexeme_type::right_parenthesis) error();
        next();
    }
    else if (in_set(Const_first(), cur.get_type())) Const();
    else error();
}