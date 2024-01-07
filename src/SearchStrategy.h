#ifndef SEARCH_STRATEGY_H
#define SEARCH_STRATEGY_H

#include "SearchTask.h"
#include <string>
#include <regex>
#include <future>
#include <iostream>


class SearchStrategy {
public:

    virtual std::vector<Match> Search(uint64_t lineNumber, const std::string& line) = 0;
};

class RegexSearchStrategy: public SearchStrategy {

public:

    RegexSearchStrategy(const std::regex& regexMask): _regexMask(regexMask) {}

    std::vector<Match> Search(uint64_t lineNumber, const std::string& line) override {

        const std::vector<std::smatch> matches{
                std::sregex_iterator{line.cbegin(), line.cend(), _regexMask},
                std::sregex_iterator{}
            };

        std::vector<Match> result;
        for (std::size_t i = 0; i < matches.size(); ++i) {
            result.emplace_back(Match {
                lineNumber, 
                static_cast<uint64_t>(matches[i].position()), 
                matches[i].str(0)
            });
        }

        return result;
    }

private:

    std::regex _regexMask;
};


#endif // SEARCH_STRATEGY_H