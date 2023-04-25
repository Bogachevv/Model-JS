#include "lexer.h"

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <utility>
#include <sstream>

enum class state{
    start,
    separator,
    id,
    eq, eq_sec,
    plus, plus_sec,
    minus, minus_sec,
    md,
    pipe, pipe_sec,
    amper, amper_sec,
    quot_first, quot_sym, quot_last,
    dquot_first, dquot_sym, dquot_last,
    digit_beg, digit_float, digit_exp_beg, digit_exp,
    invalid
};

typedef std::function<state (char)> delta_func_t;

static const std::unordered_set<state> final_states = {state::id,
                                                       state::separator,
                                                       state::eq, state::eq_sec,
                                                       state::plus, state::plus_sec,
                                                       state::minus, state::minus_sec,
                                                       state::md,
                                                       state::pipe_sec,
                                                       state::amper_sec,
                                                       state::quot_last,
                                                       state::dquot_last,
                                                       state::digit_beg, state::digit_float, state::digit_exp};

state start(char ch);
state id_func(char ch);
state minus(char ch);
state quot_sym(char ch);
state dquot_sym(char ch);
state digit_beg(char ch);
state digit_float(char ch);
state digit_exp_beg(char ch);
state digit_exp(char ch);

delta_func_t one_sym_delta(char sym, state new_state);
state terminal(char ch);

static const std::unordered_map<state, delta_func_t> delta_funcs{
        {state::start, start},
        {state::separator, terminal},
        {state::id, id_func},
        {state::eq, one_sym_delta('=', state::eq_sec)},
        {state::eq_sec, terminal},
        {state::plus, one_sym_delta('+', state::plus_sec)},
        {state::plus_sec, terminal},
        {state::minus, minus},
        {state::minus_sec, terminal},
        {state::md, terminal},
        {state::pipe, one_sym_delta('|', state::pipe_sec)},
        {state::pipe_sec, terminal},
        {state::amper, one_sym_delta('&', state::pipe_sec)},
        {state::amper_sec, terminal},
        {state::quot_first, quot_sym},
        {state::quot_sym, quot_sym},
        {state::quot_last, terminal},
        {state::dquot_first, dquot_sym},
        {state::dquot_sym, dquot_sym},
        {state::dquot_last, terminal},
        {state::digit_beg, digit_beg},
        {state::digit_float, digit_float},
        {state::digit_exp_beg, digit_exp_beg},
        {state::digit_exp, digit_exp},
};

bool in_alphabet(char ch){
    static const std::unordered_set<char> special = {'_', '*', '/', '+', '-', '.', '\'', '\"',
                                                     '|', '&', '>', '<', '!', '=', ' ',
                                                     '(', ')', '[', ']', '{', '}', ';', ','};
    if (special.find(ch) != special.end()) return true;
    return
        ((ch >= 'a') and (ch <= 'z')) or
        ((ch >= 'A') and (ch <= 'Z')) or
        ((ch >= '0') and (ch <= '9'));
}

bool is_digit(char ch){
    return (ch >= '0') and (ch <= '9');
}

bool is_letter(char ch){
    return ((ch >= 'a') and (ch <= 'z')) or ((ch >= 'A') and (ch <= 'Z'));
}

bool is_separator(char ch){
    static const std::unordered_set<char> separators = {'(', ')', '[', ']', '{', '}',
                                                     ';', ',', '.'};

    return separators.find(ch) != separators.end();
}

state step(state prev_state, char ch){
    if (prev_state == state::invalid) return state::invalid;
    return delta_funcs.at(prev_state)(ch);
}


// <<---- delta functions ---->>

delta_func_t one_sym_delta(char sym, state new_state){
    return [sym, new_state](char ch) { return (ch == sym) ? new_state : state::invalid; };
}

state terminal(char ch){
    return state::invalid;
}

state start(char ch){
    if (is_letter(ch)) return state::id;
    if ((ch == '=') or (ch == '!') or (ch == '>') or (ch == '<')) return state::eq;
    if (ch == '+') return state::plus;
    if ((ch == '*') or (ch == '/')) return state::md;
    if (ch == '|') return state::pipe;
    if (ch == '&') return state::amper;
    if (ch == '\'') return state::quot_first;
    if (ch == '\"') return state::dquot_first;
    if (ch == '-') return state::minus;
    if (is_digit(ch)) return state::digit_beg;
    if (is_separator(ch)) return state::separator;

    return state::invalid;
}

state id_func(char ch){
    if (is_letter(ch) or is_digit(ch) or (ch == '_')) return state::id;

    return state::invalid;
}

state minus(char ch){
    if (ch == '-') return state::minus_sec;
    if (is_digit(ch)) return state::digit_beg;

    return state::invalid;
}

state quot_sym(char ch){
    static const std::unordered_set<char> special = {'_', '*', '/', '+', '-', '.', '\"',
                                                     '|', '&', '>', '<', '!', '=', ' '};

    if (is_letter(ch) or is_digit(ch) or (special.find(ch) != special.end())) return state::quot_sym;
    if (ch == '\'') return state::quot_last;

    return state::invalid;
}

state dquot_sym(char ch){
    static const std::unordered_set<char> special = {'_', '*', '/', '+', '-', '.', '\'',
                                                     '|', '&', '>', '<', '!', '=', ' '};

    if (is_letter(ch) or is_digit(ch) or (special.find(ch) != special.end())) return state::quot_sym;
    if (ch == '\"') return state::quot_last;

    return state::invalid;
}

state digit_beg(char ch){
    if (is_digit(ch)) return state::digit_beg;
    if (ch == '.') return state::digit_float;
    if ((ch == 'e') or (ch == 'E')) return state::digit_exp_beg;

    return state::invalid;
}

state digit_float(char ch){
    if (is_digit(ch)) return state::digit_float;
    if ((ch == 'e') or (ch == 'E')) return state::digit_exp_beg;

    return state::invalid;
}

state digit_exp_beg(char ch){
    if (is_digit(ch) or (ch == '-')) return state::digit_exp;

    return state::invalid;
}

state digit_exp(char ch){
    if (is_digit(ch)) return state::digit_exp;

    return state::invalid;
}

// <<!--- delta functions ---!>>

lexer::lexer(const std::string& path) : file(path){
    if (file.bad()) throw std::runtime_error("Can't open file");
    it = std::istreambuf_iterator<char>(file);
    seq_end = std::istreambuf_iterator<char>();
}

lexer::~lexer() {
    file.close();
}

lexeme lexer::get_lex() {
//    if (is_empty()) throw StopIteration();
    if (is_empty()) return lexeme::eof;

    state st = state::start;
    while ((not is_empty()) and ((*it == ' ') or (*it == '\n'))) ++it;
    std::stringstream res;

    while (not is_empty()){ // lex processing loop
        if (not in_alphabet(*it)) break;
        auto new_st = step(st, *it);
        if (new_st == state::invalid){
            break;
        } else{
            st = new_st;
            res << *it;
            ++it;
        }
    }

    if (final_states.find(st) == final_states.end()){ // automate stopped in non-final state
        throw std::runtime_error("Invalid word");
    }

    return lexeme(res.str());
}