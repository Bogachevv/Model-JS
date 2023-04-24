#include "Parser.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
bool in_set(const std::unordered_set<T>& set, T elm){
    return set.find(elm) != set.end();
}

std::unordered_set<lexeme_type> merge_sets(const std::vector<std::unordered_set<lexeme_type>>& sets){
    if (sets.empty()) return {};
    if (sets.size() == 1) return sets[0];

    std::unordered_set<lexeme_type> res;
    std::merge(sets[0].begin(), sets[0].end(),
               sets[1].begin(), sets[1].end(),
               std::inserter(res, res.end()));

    for (auto it = sets.begin()+2; it != sets.end(); ++it){
        std::merge(res.begin(), res.end(),
                   (*it).begin(), (*it).end(),
                   std::inserter(res, res.end()));
    }

    return res;
}

const std::unordered_set<lexeme_type>& S_first();
const std::unordered_set<lexeme_type>& Func_first();
const std::unordered_set<lexeme_type>& Oper_first();
const std::unordered_set<lexeme_type>& Var_first();
const std::unordered_set<lexeme_type>& Empty_first();
const std::unordered_set<lexeme_type>& Scope_first();
const std::unordered_set<lexeme_type>& If_first();
const std::unordered_set<lexeme_type>& Loop_first();
const std::unordered_set<lexeme_type>& Jump_first();
const std::unordered_set<lexeme_type>& OpExpr_first();
const std::unordered_set<lexeme_type>& Expr_first();
const std::unordered_set<lexeme_type>& Const_first();
const std::unordered_set<lexeme_type>& Arifm_first();
const std::unordered_set<lexeme_type>& A1_first();
const std::unordered_set<lexeme_type>& A2_first();
const std::unordered_set<lexeme_type>& A3_first();

const std::unordered_set<lexeme_type>& S_first(){
    static std::unordered_set<lexeme_type> S_first_set;
    if (S_first_set.empty()){
        S_first_set = merge_sets({Func_first(), Oper_first()});
    }

    return S_first_set;
}

const std::unordered_set<lexeme_type>& Func_first(){
    static const std::unordered_set<lexeme_type> Func_first_set = {lexeme_type::function};

    return Func_first_set;
}

const std::unordered_set<lexeme_type>& Oper_first(){
    static std::unordered_set<lexeme_type> Oper_first_set;
    if (Oper_first_set.empty()){
        Oper_first_set = merge_sets({Var_first(), Empty_first(), Scope_first(), If_first(),
                                     Loop_first(), Jump_first(), OpExpr_first()});
    }

    return Oper_first_set;
}

const std::unordered_set<lexeme_type>& Var_first(){
    static const std::unordered_set<lexeme_type> Var_first_set = {lexeme_type::var};

    return Var_first_set;
}

const std::unordered_set<lexeme_type>& Empty_first(){
    static const std::unordered_set<lexeme_type> Empty_first_set = {lexeme_type::semicolon};

    return Empty_first_set;
}

const std::unordered_set<lexeme_type>& Scope_first(){
    static const std::unordered_set<lexeme_type> Scope_first_set = {lexeme_type::left_brace};

    return Scope_first_set;
}

const std::unordered_set<lexeme_type>& If_first(){
    static const std::unordered_set<lexeme_type> Scope_first_set = {lexeme_type::left_brace};

    return Scope_first_set;
}

const std::unordered_set<lexeme_type>& Loop_first(){
    static const std::unordered_set<lexeme_type> Loop_first_set =
            {lexeme_type::mjs_while, lexeme_type::mjs_for, lexeme_type::mjs_do};

    return Loop_first_set;
}

const std::unordered_set<lexeme_type>& Jump_first(){
    static const std::unordered_set<lexeme_type> Jump_first_set =
            {lexeme_type::mjs_break, lexeme_type::mjs_continue, lexeme_type::mjs_return};

    return Jump_first_set;
}

const std::unordered_set<lexeme_type>& OpExpr_first(){
    return Expr_first();
}

const std::unordered_set<lexeme_type>& Expr_first(){
    static std::unordered_set<lexeme_type> Expr_first_set;
    if (Expr_first_set.empty()){
        Expr_first_set = {lexeme_type::identifier};
        Expr_first_set = merge_sets({Expr_first_set, Const_first()});
    }

    return Expr_first_set;
}

const std::unordered_set<lexeme_type>& Const_first(){
    static const std::unordered_set<lexeme_type> Const_first_set =
            {lexeme_type::number, lexeme_type::string,
             lexeme_type::mjs_true, lexeme_type::mjs_false};

    return Const_first_set;
}

const std::unordered_set<lexeme_type>& Arifm_first(){
    return A1_first();
}

const std::unordered_set<lexeme_type>& A1_first(){
    return A2_first();
}
const std::unordered_set<lexeme_type>& A2_first(){
    return A3_first();
}
const std::unordered_set<lexeme_type>& A3_first(){
    static std::unordered_set<lexeme_type> A3_first_set;
    if (A3_first_set.empty()){
        A3_first_set = {lexeme_type::mjs_not, lexeme_type::plus_plus, lexeme_type::minus_minus};
        A3_first_set = merge_sets({A3_first_set, Expr_first()});
    }

    return A3_first_set;
}

struct parse_error : std::runtime_error{
    explicit parse_error(const std::string& msg) : std::runtime_error(msg) {}
};

parser::parser(const std::string& path) : lex(path), cur("") {
    cur = lex.get_lex();
}

void parser::error() {
    error("Unexpected lexeme" + cur.get_body());
}

void parser::error(const std::string &msg) {
    throw parse_error(msg);
}

bool parser::next(bool silent) {
    if (lex.is_empty()) {
        if (silent) return false;
        throw parse_error("Unexpected end of file");
    }
    cur = lex.get_lex();
    return true;
}

bool parser::analyze() {
    try{
        S();
    }
    catch (parse_error& err) {
        std::cout << err.what() << std::endl;
        return false;
    }

    return true;
}

void parser::S() {
    if (in_set(Func_first(), cur.get_type())) Func();
    else if (in_set(Oper_first(), cur.get_type())) Oper();
    else error();
}

void parser::Func() {
    if (cur.get_type() != lexeme_type::function) error();
    next();
    if (cur.get_type() != lexeme_type::identifier) error();
    std::cout << "Declaring function " << cur.get_body() << " with args: ";
    next();
    if (cur.get_type() != lexeme_type::left_parenthesis) error();
    next();

    do{
        if (cur.get_type() != lexeme_type::identifier) error();
        std::cout << cur.get_body() << ", ";
        next();
    } while (cur.get_type() != lexeme_type::right_parenthesis);
    next();
    std::cout << std::endl;

    if (in_set(Scope_first(), cur.get_type())) Scope();
    else error();
}

void parser::Oper() {
    if (in_set(Var_first(), cur.get_type())) return Var();
    if (in_set(Empty_first(), cur.get_type())) return Empty();
    if (in_set(Scope_first(), cur.get_type())) return Scope();
    if (in_set(If_first(), cur.get_type())) return If();
    if (in_set(Loop_first(), cur.get_type())) return Loop();
    if (in_set(Jump_first(), cur.get_type())) return Jump();
    if (in_set(OpExpr_first(), cur.get_type())) return OpExpr();
    error();
}

void parser::Var() {
    if (cur.get_type() != lexeme_type::var) error();
    next();

    if (cur.get_type() != lexeme_type::identifier) error();
    next();

    if (cur.get_type() == lexeme_type::assign){ // <Name> = <Expr>
        next();
        if (in_set(Expr_first(), cur.get_type())) Expr();
        else error();
    }

    while (cur.get_type() == lexeme_type::comma){
        next();

        if (cur.get_type() != lexeme_type::identifier) error();
        next();

        if (cur.get_type() == lexeme_type::assign){ // <Name> = <Expr>
            next();
            if (in_set(Expr_first(), cur.get_type())) Expr();
            else error();
        }
    }

    if (cur.get_type() != lexeme_type::semicolon) error();
    next();
}

void parser::Empty() {
    if (cur.get_type() != lexeme_type::semicolon) error();
    next();
}

void parser::Scope() {
    if (cur.get_type() != lexeme_type::left_brace) error();
    next();

    if (in_set(Oper_first(), cur.get_type())) Oper();
    else error();

    while (in_set(Oper_first(), cur.get_type())){
        Oper();
    }

    if (cur.get_type() != lexeme_type::right_brace) error();
    next();
}

void parser::If() {
    if (cur.get_type() != lexeme_type::mjs_if) error();
    next();
    if (cur.get_type() != lexeme_type::left_parenthesis) error();
    next();
    if (in_set(Expr_first(), cur.get_type())) Expr();
    else error();
    if (cur.get_type() != lexeme_type::right_parenthesis) error();
    next();
    if (in_set(Oper_first(), cur.get_type())) Oper();
    else error();

    if (cur.get_type() == lexeme_type::mjs_else){
        next();
        if (in_set(Oper_first(), cur.get_type())) Oper();
        else error();
    }
}

void parser::Loop() {
    if (cur.get_type() == lexeme_type::mjs_while){
        next();
        if (cur.get_type() != lexeme_type::left_parenthesis) error();
        next();
        if (in_set(Expr_first(), cur.get_type())) Expr();
        else error();
        if (cur.get_type() != lexeme_type::right_parenthesis) error();
        next();
        if (in_set(Oper_first(), cur.get_type())) Oper();
        else error();
    }
    else if (cur.get_type() == lexeme_type::mjs_for){
        next();
        if (cur.get_type() != lexeme_type::left_parenthesis) error();
        next();

        if (cur.get_type() != lexeme_type::semicolon){ //Expr1
            if (in_set(Expr_first(), cur.get_type())) Expr();
            else error();
            if (cur.get_type() != lexeme_type::semicolon) error();
            next();
        } else next();

        if (cur.get_type() != lexeme_type::semicolon){ //Expr2
            if (in_set(Expr_first(), cur.get_type())) Expr();
            else error();
            if (cur.get_type() != lexeme_type::semicolon) error();
            next();
        } else next();

        if (cur.get_type() != lexeme_type::right_parenthesis){ //Expr3
            if (in_set(Expr_first(), cur.get_type())) Expr();
            else error();
            if (cur.get_type() != lexeme_type::right_parenthesis) error();
            next();
        } else next();

        if (in_set(Oper_first(), cur.get_type())) Oper();
        else error();
    }
    else if (cur.get_type() == lexeme_type::mjs_do){
        next();
        if (in_set(Oper_first(), cur.get_type())) Oper();
        else error();

        if (cur.get_type() != lexeme_type::mjs_while) error();
        next();
        if (cur.get_type() != lexeme_type::left_parenthesis) error();
        next();
        if (in_set(Expr_first(), cur.get_type())) Expr();
        else error();
        if (cur.get_type() != lexeme_type::right_parenthesis) error();
        next();

        if (cur.get_type() != lexeme_type::semicolon) error();
        next();
    }
    else error();
}