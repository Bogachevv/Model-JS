#pragma once

#include <string>
#include <fstream>
#include <stdexcept>

struct StopIteration : std::exception{};

class lexer {
    std::string seq;
    std::string lex;
    std::string::const_iterator it;

public:
    explicit lexer(std::string seq);

    bool is_empty();

    std::string get_lex();

};

//#include <iostream>
//void process(const std::string &seq);