#include <utility>

#include "lexer.h"

lexeme::lexeme(std::string lex_body, lexeme::lexeme_type lex_type) :
    body(std::move(lex_body)), type(lex_type)
{

}

// <--- identifier_lexeme --->

std::unordered_set<std::string> identifier_lexeme::identifiers_table;

identifier_lexeme::identifier_lexeme(std::string identifier) :
        lexeme(std::move(identifier), lexeme_type::identifier)
{
    identifiers_table.insert(get_body());
}

bool identifier_lexeme::operator==(const lexeme &right) const {
    if (right.get_type() != get_type()) return false;

    return get_body() == right.get_body();
}

bool identifier_lexeme::is_described() {
    return (identifiers_table.find(get_body()) != identifiers_table.end());
}

// <!-- identifier_lexeme --!>



// <--- service_lexeme --->

const std::unordered_set<std::string> service_lexeme::service_lexemes = {

};

bool service_lexeme::is_service(const std::string &body) {
    return service_lexemes.find(body) != service_lexemes.end();
}

service_lexeme::service_lexeme(std::string body) :
        lexeme(std::move(body), lexeme::lexeme_type::service)
{
    if (not is_service(get_body()))
        throw std::runtime_error(get_body() + std::string(" is not service lexeme; \n"
                                                          "Use service_lexeme::is_service(std::string&) before constructing"));
}

bool service_lexeme::operator==(const lexeme &right) const {
    if (right.get_type() != get_type()) return false;

    return get_body() == right.get_body();
}

// <!-- service_lexeme --!>



// <--- constant_lexeme --->

constant_lexeme::constant_type get_const_type(const std::string& str){
    if ((str.at(0) == '\'') or (str.at(0) == '\"')) return constant_lexeme::constant_type::string;
    if ((str.find('.') != std::string::npos) or
        (str.find('e') != std::string::npos) or
        (str.find('E') != std::string::npos))
        return constant_lexeme::constant_type::real;

    return constant_lexeme::constant_type::integer;
}

constant_lexeme::constant_lexeme(std::string body) :
        lexeme(std::move(body), lexeme::lexeme_type::constant)
{
    const_type = ::get_const_type(get_body());
}

int constant_lexeme::to_int() const {
    return std::stoi(get_body());
}

double constant_lexeme::to_real() const {
    return std::stod(get_body());
}

std::string constant_lexeme::to_string() const {
    const std::string& body = get_body();

    return {body.begin() + 1, body.end() - 1};
}

bool strcmp(std::string::const_iterator lb, std::string::const_iterator le,
            std::string::const_iterator rb, std::string::const_iterator re)
{
    while ((lb != le) and (rb != re)){
        if (*lb != *rb) return false;
        ++lb;
        ++rb;
    }
    if ((lb == le) and (rb == re)) return true;
    return false;
}

bool constant_lexeme::operator==(const lexeme &right) const {
    if (right.get_type() != get_type()) return false;
    auto right_casted = dynamic_cast<const constant_lexeme&>(right);
    if (right_casted.get_const_type() != get_const_type()) return false;

    switch (get_const_type()) {
        case constant_type::integer:
            return right_casted.to_int() == to_int();

        case constant_type::real:
            return right_casted.to_real() == to_real();

        case constant_type::string:
            return strcmp(get_body().begin()+1, get_body().end()-1,
                          right_casted.get_body().begin()+1, right_casted.get_body().end()-1);
    }
}

// <!-- constant_lexeme --!>