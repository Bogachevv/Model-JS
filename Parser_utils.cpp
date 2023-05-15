#include "Parser_utils.h"

std::unordered_set<lexeme_type> merge_sets(const std::vector<std::unordered_set<lexeme_type>>& sets){
    if (sets.empty()) return {};
    if (sets.size() == 1) return sets[0];

    std::unordered_set<lexeme_type> res;
    std::merge(sets[0].begin(), sets[0].end(),
               sets[1].begin(), sets[1].end(),
               std::inserter(res, res.end()));

    for (auto it = sets.begin()+2; it != sets.end(); ++it){
        std::merge(res.begin(), res.end(),
                   (*it).begin(), (*it).end(),
                   std::inserter(res, res.end()));
    }

    return res;
}