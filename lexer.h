#pragma once

#include <unordered_set>
#include <unordered_map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iterator>

struct StopIteration : std::exception{};

class lexeme;

class lexer {
//    std::string seq;
    std::string lex;
    std::istreambuf_iterator<char> it, seq_end;
    std::ifstream file;

public:
    explicit lexer(const std::string& path);

    inline bool is_empty() { return it == seq_end; }

    lexeme get_lex();

    ~lexer();
};

enum class lexeme_type{
    identifier, empty,
    // <--- separators --->
        semicolon, comma,
        left_brace, right_brace, // {}
        left_parenthesis, right_parenthesis, // ()
        left_square_b, right_square_b, // []
        plus, minus, mul, div, mod,
        plus_plus, minus_minus,
        mjs_and, mjs_or, mjs_not,
        eq, neq, gr, ls, ge, le,
        assign,
    // <!-- separators --!>

    // <--- service --->
        var, function,
        mjs_for, mjs_while, mjs_do, mjs_in,
        mjs_if, mjs_else,
        mjs_break, mjs_continue, mjs_return,
    // <!-- service --!>

    // <--- constant --->
        mjs_true, mjs_false,
        number, string
    // <!-- constant --!>
};

class lexeme{
    lexeme_type type;
    std::string body;

public:
    explicit lexeme(std::string body);

    lexeme_type get_type() const { return type; }

    const std::string& get_body() const { return body; }
};
