#pragma once

#include <unordered_set>
#include <unordered_map>
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

//TODO:
//  implement separator lex
class lexeme{
public:
    enum class lexeme_type{
        identifier, service, constant, separator
    };

private:
    std::string body;
    lexeme_type type;

public:
    lexeme(std::string lex_body, lexeme_type lex_type);

    lexeme_type get_type() const { return type; }

    const std::string& get_body() const { return body; }

    virtual bool operator==(const lexeme& right) const = 0;

    virtual bool operator!=(const lexeme& right) const = 0;

    virtual ~lexeme() = default;
};

//TODO:
// fill identifiers_table
class identifier_lexeme : public lexeme {
    static std::unordered_set<std::string> identifiers_table;

public:
    explicit identifier_lexeme(std::string identifier);

    bool operator==(const lexeme& right) const override;

    bool operator!=(const lexeme& right) const override { return not (this->operator==(right)); }

    bool is_described();

};

class service_lexeme : public lexeme{
    static const std::unordered_set<std::string> service_lexemes;

public:
    static bool is_service(const std::string& body);

    explicit service_lexeme(std::string body);

    bool operator==(const lexeme& right) const override;

    bool operator!=(const lexeme& right) const override { return not (this->operator==(right)); }

};

class constant_lexeme : public lexeme{
public:
    enum class constant_type{
        string, integer, real
    };

private:
    constant_type const_type;


public:
    explicit constant_lexeme(std::string body);

    int to_int() const;

    double to_real() const;

    std::string to_string() const;

    constant_type get_const_type() const { return const_type; }

    bool operator==(const lexeme& right) const override;

    bool operator!=(const lexeme& right) const override { return not (this->operator==(right)); }

};
