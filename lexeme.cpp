#include <utility>
#include <unordered_map>

#include "lexer.h"

static const std::unordered_map<std::string, lexeme_type> str_to_lex_type_map = {
        {";", lexeme_type::semicolon}, {",", lexeme_type::comma},
        {"{", lexeme_type::left_brace}, {"}", lexeme_type::right_brace},
        {"(", lexeme_type::left_parenthesis}, {")", lexeme_type::right_parenthesis},
        {"[", lexeme_type::left_square_b}, {"]", lexeme_type::right_square_b},
        {"+", lexeme_type::plus},
        {"-", lexeme_type::minus},
        {"*", lexeme_type::mul},
        {"/", lexeme_type::div},
        {"%", lexeme_type::mod},
        {"++", lexeme_type::plus_plus}, {"--", lexeme_type::minus_minus},
        {"and", lexeme_type::mjs_and},
        {"or", lexeme_type::mjs_or},
        {"not", lexeme_type::mjs_not},
        {"==", lexeme_type::eq}, {"!=", lexeme_type::neq},
        {">", lexeme_type::gr}, {"<", lexeme_type::ls},
        {">=", lexeme_type::ge}, {"<=", lexeme_type::le},
        {"=", lexeme_type::assign},

        {"var", lexeme_type::var},
        {"function", lexeme_type::function},
        {"for", lexeme_type::mjs_for},
        {"while", lexeme_type::mjs_while},
        {"do", lexeme_type::mjs_do},
        {"in", lexeme_type::mjs_in},
        {"if", lexeme_type::mjs_if},
        {"else", lexeme_type::mjs_else},
        {"break", lexeme_type::mjs_break},
        {"continue", lexeme_type::mjs_continue},
        {"return", lexeme_type::mjs_return},
};

lexeme_type str_to_lex_type(const std::string& str){
    if (str.length() == 0) return lexeme_type::empty;

    auto it = str_to_lex_type_map.find(str);
    if (it != str_to_lex_type_map.end()) return it->second;

    if (std::isdigit(str[0]) or (str[0] == '+') or (str[0] == '-')) return lexeme_type::number;
    if ((str[0] == '\'') or ((str[0] == '\"'))) return lexeme_type::string;
    if (str == "false") return lexeme_type::mjs_false;
    if (str == "true") return lexeme_type::mjs_true;

    return lexeme_type::identifier;
}

lexeme::lexeme(std::string body) : body(std::move(body)) {
    type = str_to_lex_type(this->body);
}