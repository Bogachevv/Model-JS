#pragma once

#include <stdexcept>

struct mjs_error : std::runtime_error{
    explicit mjs_error(const std::string& msg) : std::runtime_error(msg) {}
};

struct type_error : mjs_error{
    explicit type_error(const std::string& msg) : mjs_error(msg) {}
};

struct mjs_runtime_error : mjs_error{
    explicit mjs_runtime_error(const std::string& msg) : mjs_error(msg) {}
};