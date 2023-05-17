#pragma once

#include "lexer.h"
#include "mjs_data_containers.h"
#include "proprietary_functions.h"
#include "RPN.h"

#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>
#include <stack>
#include <memory>

class parser {
    lexer lex;
    lexeme cur;

    std::unordered_map<std::string, variable> variables;
    std::unordered_map<std::string, function*> functions;

    size_t arg_counter;
    std::stack<size_t> arg_counter_stack;
    bool function_args_processing;

    std::shared_ptr<RPN> rpn;
    std::stack<std::shared_ptr<RPN>> functions_rpn_stack;
    std::stack<std::unordered_map<std::string, variable>> functions_variables_stack;

    std::stack<size_t> continue_iterators;
    std::stack<size_t> break_iterators;

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

    void process_for();
    void process_while();
    void process_do();

    bool next(bool silent = false);

    void error();

    static void error(const std::string& msg);

public:
    explicit parser(const std::string& path);

    bool analyze();

    std::shared_ptr<RPN> get_rpn() { return rpn; }

    const std::unordered_map<std::string, variable>& get_variables() const { return variables; }
};
