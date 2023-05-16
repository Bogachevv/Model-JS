cmake_minimum_required(VERSION 3.22)
project(MJS_interpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(MJS_interpreter main.cpp lexer.cpp lexer.h lexeme.cpp Parser.cpp Parser.h Parser_utils.cpp Parser_utils.h Parser_first_functions.cpp Parser_first_functions.h RPN.cpp RPN.h mjs_datatypes.cpp mjs_datatypes.h mjs_data_containers.cpp mjs_data_containers.h mjs_except.h proprietary_functions.cpp proprietary_functions.h)
