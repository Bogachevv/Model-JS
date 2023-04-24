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
    void Expr();
    void Const();
    void Arifm();
    void A1();
    void A2();
    void A3();

    bool next(bool silent = false);

    void error();

    static void error(const std::string& msg);

public:
    explicit parser(const std::string& path);

    bool analyze();
};
