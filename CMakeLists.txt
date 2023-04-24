cmake_minimum_required(VERSION 3.22)
project(MJS_interpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(MJS_interpreter main.cpp lexer.cpp lexer.h lexeme.cpp Parser.cpp Parser.h)
