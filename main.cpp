#include <iostream>
#include <string>

#include "lexer.h"


int main() {
    std::string text = "a123 = b12 - 1.12* 3.14 + 'Hello world'";
    process(text);

    return 0;
}
