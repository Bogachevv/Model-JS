#include <iostream>
#include <string>

#include "lexer.h"


int main() {
    std::string text = "a123 = b12 - 1.12* 3.14 + 'Hello world'\nabc";
    lexer lex(text);

    while (not lex.is_empty()){
        std::cout << lex.get_lex() << std::endl;
    }

    return 0;
}
