#ifndef DEFAULT_FACTORY_H
#define DEFAULT_FACTORY_H

#include "SearchTask.h"
#include "SearchStrategy.h"
#include "InputParameters.h"
#include <string>
#include <regex>
#include <future>
#include <iostream>

class SearchFactory {

public:

    virtual SearchTask_t MakeSearchTask(std::shared_ptr<SearchStrategy> searchStrategy, 
                                                uint64_t lineNumber, const std::string& line) = 0;
    virtual std::shared_ptr<SearchStrategy> MakeSearchStrategy() = 0;

};


class DefaultFactory: public SearchFactory {
    
    public:

        DefaultFactory(const InputParameters& inputParameters): _inputParameters(inputParameters) {}

        SearchTask_t MakeSearchTask(std::shared_ptr<SearchStrategy> searchStrategy,
                                          uint64_t lineNumber, const std::string& line) override {

            auto matchFunction = [searchStrategy, lineNumber, line] () -> std::vector<Match> {
                return searchStrategy->Search(lineNumber, line);
            };

            return std::move(SearchTask_t(matchFunction));
        }

        std::shared_ptr<SearchStrategy> MakeSearchStrategy() override {
            return std::make_shared<RegexSearchStrategy>(_inputParameters.regexMask);
        }

    private:

        const InputParameters& _inputParameters;
};

#endif // DEFAULT_FACTORY_H