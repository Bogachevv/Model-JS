#include <iostream>
#include <string>

#include "lexer.h"
#include "parser.h"

using std::cout;
using std::endl;

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

    RPN rpn = p.get_rpn();
    auto elms = rpn.get_elements();
    size_t counter = 0;
    for (auto & elm : elms){
        if ((elm.type == RPN_types::jump) or (elm.type == RPN_types::jump_true) or (elm.type == RPN_types::jump_false)){
            cout << counter << ": " << (int)(elm.type) << " jump to " << elm.label << endl;
        }
        else{
            cout << counter << ": " << (int)(elm.type) << endl;
        }
        ++counter;
    }

    cout << endl << "Success" << endl;

    return 0;
}
