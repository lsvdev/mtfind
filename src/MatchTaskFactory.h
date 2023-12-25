#ifndef TASK_FACTORY_H
#define TASK_FACTORY_H

#include "MatchTask.h"
#include <string>
#include <regex>
#include <future>
#include <iostream>

class MatchTaskFactory {

public:

    static MatchTask_t MakeTask(uint64_t lineNumber, const std::string& line, std::regex mask) {

        auto regexMask = std::regex(mask);

        auto matchFunction = [lineNumber, line, regexMask] () -> std::vector<Match> {

            const std::vector<std::smatch> matches{
                std::sregex_iterator{line.cbegin(), line.cend(), regexMask},
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
        };

        return std::move(MatchTask_t(matchFunction));
    }
};


#endif // TASK_FACTORY_H