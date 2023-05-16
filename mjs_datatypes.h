#pragma once

#include <string>
#include <utility>
#include <vector>
#include <stdexcept>

enum class mjs_data_types{
    mjs_string, mjs_number, mjs_bool
};

struct type_error : std::runtime_error{
    explicit type_error(const std::string& msg) : std::runtime_error(msg) {}
};

class mjs_data{
protected:
    mjs_data_types type;
public:
    mjs_data_types get_type() const { return type; }

    virtual std::string convert_to_string() const = 0;

    virtual explicit operator bool() const = 0;

    friend mjs_data* operator+(const mjs_data&, const mjs_data&);
    friend mjs_data* operator-(const mjs_data&, const mjs_data&);

    friend bool operator==(const mjs_data&, const mjs_data&);
    friend bool operator!=(const mjs_data& lhs, const mjs_data& rhs) { return not (lhs == rhs); }

    friend bool operator<(const mjs_data&, const mjs_data&);
    friend bool operator<=(const mjs_data&, const mjs_data&);

    friend bool operator>(const mjs_data&, const mjs_data&);
    friend bool operator>=(const mjs_data&, const mjs_data&);

    virtual bool is_ident(const mjs_data& other) const;
    virtual bool is_not_ident(const mjs_data& other) const { return not is_ident(other); }

    virtual ~mjs_data()  = default;
};

class mjs_string : public mjs_data{
    std::string body;
public:
    mjs_string() { type = mjs_data_types::mjs_string; }

    explicit mjs_string(std::string str) : body(std::move(str)) { type = mjs_data_types::mjs_string; }

    std::string convert_to_string() const override { return body; }

    explicit operator bool() const override { return not body.empty(); }

    friend mjs_string operator+(const mjs_string& rhs, const mjs_string& lhs) { return mjs_string(lhs.body + rhs.body);}

    bool operator==(const mjs_string& rhs) const { return body == rhs.body; }
    bool operator!=(const mjs_string& rhs) const { return body != rhs.body; }

    bool operator<(const mjs_string& rhs) const { return body < rhs.body; }
    bool operator<=(const mjs_string& rhs) const { return body <= rhs.body; }

    bool operator>(const mjs_string& rhs) const { return body > rhs.body; }
    bool operator>=(const mjs_string& rhs) const { return body >= rhs.body; }

    ~mjs_string() override = default;
};

class mjs_bool : public mjs_data{
    bool body;
public:
    explicit mjs_bool(bool val = false) : body(val) {type = mjs_data_types::mjs_bool;}

    std::string convert_to_string() const override { return std::to_string(body); }

    explicit operator bool() const override { return body; }

    friend mjs_bool operator||(const mjs_bool& lhs, const mjs_bool& rhs) { return mjs_bool(lhs.body || rhs.body);}
    friend mjs_bool operator&&(const mjs_bool& lhs, const mjs_bool& rhs) { return mjs_bool(lhs.body || rhs.body);}

    mjs_bool operator!() const {return mjs_bool(!body);}

    bool operator==(const mjs_bool& rhs) const { return body == rhs.body;}
    bool operator!=(const mjs_bool& rhs) const { return body != rhs.body;}

    bool operator<(const mjs_bool& rhs) const { return body < rhs.body;}
    bool operator<=(const mjs_bool& rhs) const { return body <= rhs.body;}

    bool operator>(const mjs_bool& rhs) const { return body > rhs.body;}
    bool operator>=(const mjs_bool& rhs) const { return body >= rhs.body;}

    ~mjs_bool() override = default;
};

class mjs_number : public mjs_data{
    bool is_decimal;
    double real;
    int decimal;

public:
    mjs_number(){type = mjs_data_types::mjs_number; is_decimal = true; decimal = 0; real = 0;}

    explicit mjs_number(const std::string& str);

    explicit mjs_number(int val) : is_decimal(true), real(0.0), decimal(val) {type = mjs_data_types::mjs_number;}

    explicit mjs_number(double val) : is_decimal(false), real(val), decimal(0) {type = mjs_data_types::mjs_number;}

    explicit mjs_number(const mjs_bool& logic) : mjs_number((int)bool(logic)) {}

    mjs_string to_mjs_string() const{
        if (is_decimal) return mjs_string(std::to_string(decimal));
        else return mjs_string(std::to_string(real));
    }

    std::string convert_to_string() const override {
        if (is_decimal) return std::to_string(decimal);
        else return std::to_string(real);
    }

    explicit operator bool() const override {return (is_decimal and (decimal != 0)) or (not is_decimal and (real != 0));}

    friend mjs_number operator+(const mjs_number&, const mjs_number&);
    friend mjs_number operator-(const mjs_number&, const mjs_number&);

    friend mjs_number operator*(const mjs_number&, const mjs_number&);
    friend mjs_number operator/(const mjs_number&, const mjs_number&);
    friend mjs_number operator%(const mjs_number&, const mjs_number&);

    mjs_number operator++() {
        if (is_decimal) ++decimal;
        else ++real;
        return *this;
    }
    mjs_number operator++(int){
        mjs_number tmp(*this);
        if (is_decimal) ++tmp.decimal;
        else ++tmp.real;
        return tmp;
    }
    mjs_number operator--(){
        if (is_decimal) --decimal;
        else --real;
        return *this;
    }
    mjs_number operator--(int){
        mjs_number tmp(*this);
        if (is_decimal) --tmp.decimal;
        else --tmp.real;
        return tmp;
    }

    mjs_number operator-() const{
        if (is_decimal) return mjs_number(-decimal);
        else return mjs_number(-real);
    }

    bool operator==(const mjs_number& rhs) const{
        if (is_decimal == rhs.is_decimal){
            if (is_decimal) return decimal == rhs.decimal;
            else return real == rhs.real;
        }
        double l, r;
        if (is_decimal) {l = (double)decimal; r = rhs.real;}
        else {l = real; r = (double)rhs.decimal;}
        return l == r;
    }

    bool operator!=(const mjs_number& rhs) const { return not (*this == rhs);}

    bool operator<(const mjs_number&) const;
    bool operator<=(const mjs_number&) const;

    bool operator>(const mjs_number&) const;
    bool operator>=(const mjs_number&) const;

    ~mjs_number() override = default;
};

struct variable{ //fast and dirty
    std::string identifier;
    mjs_data* data;

public:
    explicit variable(std::string identifier, mjs_data *data_ptr = nullptr) :
            identifier(std::move(identifier)), data(data_ptr)
    {}

    void set_data(mjs_data* new_ptr) { data = new_ptr; }

    mjs_data* get_data() const { return data; }

};

struct function{
    std::string identifier;
    int argc;

public:
    function(std::string identifier, int argc) :
            identifier(std::move(identifier)), argc(argc)
    {}
};

struct constant{
    mjs_data* data;

public:
    explicit constant(mjs_data* data_ptr = nullptr) : data(data_ptr) {}

    void set_data(mjs_data* new_ptr) { data = new_ptr; }

    mjs_data* get_data() const { return data; }
};