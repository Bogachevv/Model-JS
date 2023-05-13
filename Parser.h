#pragma once

#include "lexer.h"

#include <unordered_set>

class parser {
    lexer lex;
    lexeme cur;

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
