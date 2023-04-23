#include <iostream>
#include <string>

#include "lexer.h"


int main() {
    std::string text = "Hello a1 = b3";
    lexer lex("../file.mjs");

    while (not lex.is_empty()){
        auto lexeme = lex.get_lex();
        std::cout << lexeme.get_body() << "\t" << (int)lexeme.get_type() << std::endl;
    }

    return 0;
}
