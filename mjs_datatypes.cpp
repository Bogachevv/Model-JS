#include "mjs_datatypes.h"

#include <stdexcept>
#include <algorithm>

bool operator==(const mjs_data& lhs, const mjs_data& rhs){
    if (lhs.type == rhs.type){
        switch (lhs.type) {
            case mjs_data_types::mjs_string:
                return dynamic_cast<const mjs_string&>(lhs).operator==(dynamic_cast<const mjs_string&>(rhs));
            case mjs_data_types::mjs_number:
                return dynamic_cast<const mjs_number&>(lhs).operator==(dynamic_cast<const mjs_number&>(rhs));
            case mjs_data_types::mjs_bool:
                return dynamic_cast<const mjs_bool&>(lhs).operator==(dynamic_cast<const mjs_bool&>(rhs));
            default:
                throw std::logic_error("Unexpected type");
        }
    }
    else throw std::logic_error("Not implemented");
    //TODO:
    //  implement for different data types
}

bool operator<(const mjs_data& lhs, const mjs_data& rhs){
    if (lhs.type == rhs.type){
        switch (lhs.type) {
            case mjs_data_types::mjs_string:
                return dynamic_cast<const mjs_string&>(lhs).operator<(dynamic_cast<const mjs_string&>(rhs));
            case mjs_data_types::mjs_number:
                return dynamic_cast<const mjs_number&>(lhs).operator<(dynamic_cast<const mjs_number&>(rhs));
            case mjs_data_types::mjs_bool:
                return dynamic_cast<const mjs_bool&>(lhs).operator<(dynamic_cast<const mjs_bool&>(rhs));
        }
    }
    else throw std::logic_error("Not implemented");
    //TODO:
    //  implement for different data types
}

bool operator<=(const mjs_data& lhs, const mjs_data& rhs){
    if (lhs.type == rhs.type){
        switch (lhs.type) {
            case mjs_data_types::mjs_string:
                return dynamic_cast<const mjs_string&>(lhs).operator<=(dynamic_cast<const mjs_string&>(rhs));
            case mjs_data_types::mjs_number:
                return dynamic_cast<const mjs_number&>(lhs).operator<=(dynamic_cast<const mjs_number&>(rhs));
            case mjs_data_types::mjs_bool:
                return dynamic_cast<const mjs_bool&>(lhs).operator<=(dynamic_cast<const mjs_bool&>(rhs));
        }
    }
    else throw std::logic_error("Not implemented");
    //TODO:
    //  implement for different data types
}

bool operator>(const mjs_data& lhs, const mjs_data& rhs){
    if (lhs.type == rhs.type){
        switch (lhs.type) {
            case mjs_data_types::mjs_string:
                return dynamic_cast<const mjs_string&>(lhs).operator>(dynamic_cast<const mjs_string&>(rhs));
            case mjs_data_types::mjs_number:
                return dynamic_cast<const mjs_number&>(lhs).operator>(dynamic_cast<const mjs_number&>(rhs));
            case mjs_data_types::mjs_bool:
                return dynamic_cast<const mjs_bool&>(lhs).operator>(dynamic_cast<const mjs_bool&>(rhs));
        }
    }
    else throw std::logic_error("Not implemented");
    //TODO:
    //  implement for different data types
}

bool operator>=(const mjs_data& lhs, const mjs_data& rhs){
    if (lhs.type == rhs.type){
        switch (lhs.type) {
            case mjs_data_types::mjs_string:
                return dynamic_cast<const mjs_string&>(lhs).operator>=(dynamic_cast<const mjs_string&>(rhs));
            case mjs_data_types::mjs_number:
                return dynamic_cast<const mjs_number&>(lhs).operator>=(dynamic_cast<const mjs_number&>(rhs));
            case mjs_data_types::mjs_bool:
                return dynamic_cast<const mjs_bool&>(lhs).operator>=(dynamic_cast<const mjs_bool&>(rhs));
        }
    }
    else throw std::logic_error("Not implemented");
    //TODO:
    //  implement for different data types
}

bool mjs_data::is_ident(const mjs_data &other) const {
    if (type != other.type) return false;
    return *this == other;
}

mjs_number::mjs_number(const std::string &str) {
    if (str.empty()) return;
    if ((str[0] == '+') or (str[0] == '-')){
        is_decimal = std::all_of(str.begin()+1, str.end(), ::isdigit);
    }
    else{
        is_decimal = std::all_of(str.begin(), str.end(), ::isdigit);
    }

    if (is_decimal){
        decimal = std::stoi(str);
        real = 0.0;
    }else{
        decimal = 0;
        real = std::stod(str);
    }
}

mjs_number operator+(const mjs_number& lhs, const mjs_number& rhs){
    if (lhs.is_decimal and rhs.is_decimal){
        return mjs_number(lhs.decimal + rhs.decimal);
    }
    else{
        return mjs_number((lhs.is_decimal ? (double)lhs.decimal : lhs.real) +
        (rhs.is_decimal ? (double)rhs.decimal : rhs.real));
    }
}

mjs_number operator-(const mjs_number& lhs, const mjs_number& rhs){
    if (lhs.is_decimal and rhs.is_decimal){
        return mjs_number(lhs.decimal - rhs.decimal);
    }
    else{
        return mjs_number((lhs.is_decimal ? (double)lhs.decimal : lhs.real) -
                          (rhs.is_decimal ? (double)rhs.decimal : rhs.real));
    }
}

mjs_number operator*(const mjs_number& lhs, const mjs_number& rhs){
    if (lhs.is_decimal and rhs.is_decimal){
        return mjs_number(lhs.decimal * rhs.decimal);
    }
    else{
        return mjs_number((lhs.is_decimal ? (double)lhs.decimal : lhs.real) *
                          (rhs.is_decimal ? (double)rhs.decimal : rhs.real));
    }
}

mjs_number operator/(const mjs_number& lhs, const mjs_number& rhs){
    if (lhs.is_decimal and rhs.is_decimal){
        return mjs_number(lhs.decimal / rhs.decimal);
    }
    else{
        return mjs_number((lhs.is_decimal ? (double)lhs.decimal : lhs.real) /
                          (rhs.is_decimal ? (double)rhs.decimal : rhs.real));
    }
}

mjs_number operator%(const mjs_number& lhs, const mjs_number& rhs){
    if (lhs.is_decimal and rhs.is_decimal){
        return mjs_number(lhs.decimal % rhs.decimal);
    }
    else throw type_error("Can't execute % operation for non-decimal numbers");
}

bool mjs_number::operator<(const mjs_number &rhs) const {
    if (is_decimal and rhs.is_decimal){
        return decimal < rhs.decimal;
    }
    else{
        return ((is_decimal ? (double)decimal : real) < (rhs.is_decimal ? (double)rhs.decimal : rhs.real));
    }
}

bool mjs_number::operator<=(const mjs_number &rhs) const {
    if (is_decimal and rhs.is_decimal){
        return decimal <= rhs.decimal;
    }
    else{
        return ((is_decimal ? (double)decimal : real) <= (rhs.is_decimal ? (double)rhs.decimal : rhs.real));
    }
}

bool mjs_number::operator>(const mjs_number &rhs) const {
    if (is_decimal and rhs.is_decimal){
        return decimal > rhs.decimal;
    }
    else{
        return ((is_decimal ? (double)decimal : real) > (rhs.is_decimal ? (double)rhs.decimal : rhs.real));
    }
}

bool mjs_number::operator>=(const mjs_number &rhs) const {
    if (is_decimal and rhs.is_decimal){
        return decimal >= rhs.decimal;
    }
    else{
        return ((is_decimal ? (double)decimal : real) >= (rhs.is_decimal ? (double)rhs.decimal : rhs.real));
    }
}