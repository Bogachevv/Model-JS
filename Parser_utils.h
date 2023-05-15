#pragma once

#include "Parser.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
bool in_set(const std::unordered_set<T>& set, T elm){
    return set.find(elm) != set.end();
}

std::unordered_set<lexeme_type> merge_sets(const std::vector<std::unordered_set<lexeme_type>>& sets);