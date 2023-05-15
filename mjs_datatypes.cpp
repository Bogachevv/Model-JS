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