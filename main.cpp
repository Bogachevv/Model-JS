#include <iostream>
#include <string>

#include "lexer.h"


int main() {
    std::string text = "Hello a1 = b3";
    lexer lex("../file.mjs");

    while (not lex.is_empty()){
        std::cout << lex.get_lex() << std::endl;
    }

    return 0;
}
