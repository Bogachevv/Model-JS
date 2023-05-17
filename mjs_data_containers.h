#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>

#include "mjs_datatypes.h"

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

struct constant{
    mjs_data* data;

public:
    explicit constant(mjs_data* data_ptr = nullptr) : data(data_ptr) {}

    void set_data(mjs_data* new_ptr) { data = new_ptr; }

    mjs_data* get_data() const { return data; }
};



class function{
protected:
    std::string identifier;
    int argc;
    std::vector<std::string> formal_args;

public:
    function(std::string identifier, int argc) : identifier(std::move(identifier)), argc(argc) {}

    virtual mjs_data* operator()(std::vector<mjs_data*> actual_params) = 0;

    const std::string& get_identifier() const { return identifier; }

    int get_argc() const { return argc; }

    const std::vector<std::string> &get_formal_args() const {
        return formal_args;
    }

    void set_formal_args(const std::vector<std::string> &formalArgs) {
        formal_args = formalArgs;
    }
};

class RPN; //extern declaration

class custom_function : public function{
    std::shared_ptr<RPN> body;

public:
    custom_function(std::string identifier, int argc) : function(std::move(identifier), argc) {}

    void set_argc(int new_argc) { argc = new_argc; }

    std::shared_ptr<RPN> get_rpn() { return body; }

    void set_rpn(const std::shared_ptr<RPN>& new_rpn) { body = new_rpn; }

    mjs_data* operator()(std::vector<mjs_data*> actual_params) override;

};

class proprietary_function : public function{
    std::function<mjs_data*(std::vector<mjs_data*>)> body;

public:
    proprietary_function(std::string identifier, int argc, decltype(body) body);

    mjs_data* operator()(std::vector<mjs_data*> actual_params) override;
};