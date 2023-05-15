#include "mjs_datatypes.h"

#include <stdexcept>

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
    throw std::logic_error("Not implemented");
}

mjs_number operator+(const mjs_number&, const mjs_number&){
    throw std::logic_error("Not implemented");
}
mjs_number operator-(const mjs_number&, const mjs_number&){
    throw std::logic_error("Not implemented");
}

mjs_number operator*(const mjs_number&, const mjs_number&){
    throw std::logic_error("Not implemented");
}
mjs_number operator/(const mjs_number&, const mjs_number&){
    throw std::logic_error("Not implemented");
}
mjs_number operator%(const mjs_number&, const mjs_number&){
    throw std::logic_error("Not implemented");
}

bool mjs_number::operator<(const mjs_number &) const {
    throw std::logic_error("Not implemented");
}

bool mjs_number::operator<=(const mjs_number &) const {
    throw std::logic_error("Not implemented");
}

bool mjs_number::operator>(const mjs_number &) const {
    throw std::logic_error("Not implemented");
}

bool mjs_number::operator>=(const mjs_number &) const {
    throw std::logic_error("Not implemented");
}