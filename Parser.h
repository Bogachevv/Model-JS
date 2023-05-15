#pragma once

#include "lexer.h"
#include "mjs_datatypes.h"
#include "RPN.h"

#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>
#include <stack>

class parser {
    lexer lex;
    lexeme cur;

    std::unordered_map<std::string, variable> variables;
    std::unordered_map<std::string, function> functions;

    size_t arg_counter;
    std::stack<size_t> arg_counter_stack;
    bool function_args_processing;

    RPN rpn;

    void S();
    void Func();
    void Oper();
    void Var();
    void Empty();
    void Scope();
    void If();
    void Loop();
    void Jump();
    void OpExpr();
    void Const();
    void Expr();
    void E1();
    void E2();
    void E3();
    void E4();
    void E5();
    void E6();
    void E7();
    void E8();
    void E9();
    void E10();
    void E11();


    bool next(bool silent = false);

    void error();

    static void error(const std::string& msg);

public:
    explicit parser(const std::string& path);

    bool analyze();
};
