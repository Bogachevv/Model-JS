#pragma once

#include <string>
#include <fstream>
#include <stdexcept>
#include <iterator>

struct StopIteration : std::exception{};

class lexer {
//    std::string seq;
    std::string lex;
    std::istreambuf_iterator<char> it, seq_end;
    std::ifstream file;

public:
    explicit lexer(const std::string& path);

    inline bool is_empty() { return it == seq_end; }

    std::string get_lex();

    ~lexer();
};