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
    if (not p.analyze()) exit(1);

    auto rpn = p.get_rpn();
    auto elms = rpn->get_elements();
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

    cout << endl << "Running program..." << endl;
    rpn->evaluate();

    cout << endl << "Variables: " << endl;
    for (const auto & it : p.get_variables()){
        cout << it.first << ": " << it.second.data->convert_to_string() << endl;
    }

    cout << endl << "Success" << endl;

    return 0;
}
