#include <iostream>
#include <string>

#include "lexer.h"
#include "parser.h"

int main() {
    std::string path = "../file.mjs";
    lexer lex(path);

    while (not lex.is_empty()){
        auto lexeme = lex.get_lex();
        std::cout << lexeme.get_body() << "\t" << (int)lexeme.get_type() << std::endl;
    }

    std::cout << "Start parsing..." << std::endl;

    parser p(path);
    p.analyze();

    return 0;
}
