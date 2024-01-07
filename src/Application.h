#ifndef APPLICATION_H
#define APPLICATION_H

#include "MtfindConfig.h"
#include "SearchTaskQueue.h"
#include "DefaultFactory.h"
#include "LinesReader.h"
#include "LinesReaderThread.h"
#include "ILinesReaderObserver.h"
#include "WorkerThread.h"
#include "InputParametersReader.h"

#include <iostream>
#include <memory>
#include <vector>
#include <sstream>

class Application: public ILinesReaderObserver {

public:

    Application(const InputParameters& inputParameters): _inputParameters(inputParameters) {
        _Init();
    }

    std::shared_ptr<Report> Run() {

        _linesReader->Start();

        for(auto worker : _workers) {
            worker->Start();
        }

        std::vector<Match> matches;
        for(auto worker : _workers) {
            worker->Wait();
        }

        _linesReader->Wait();

        for(auto& threadResult : _results) {

            auto result = threadResult.get();
            if(!result.empty()) {
                matches.insert(matches.end(), result.begin(), result.end());
            }
        }

        return _MakeReport(matches);
    }

    void OnNewLine(uint64_t lineNumber, const std::string& line) override {
        auto task = _searchFactory->MakeSearchTask(_searchStrategy, lineNumber, line);
        _results.push_back(task.get_future());
        _matchTasksQueue->PushBack(std::move(task));
    }

    void OnReadingFinished() override {
        _matchTasksQueue->NotifyFinished();
    }

private:

    void _Init() {
        _matchTasksQueue = std::make_shared<SearchTaskQueue>(_linesQueueCondition, _linesQueueMutex);
        _linesReader = _MakeLinesReader(_inputParameters.fileName);
        _searchFactory = std::make_shared<DefaultFactory>(_inputParameters);
        _searchStrategy = _searchFactory->MakeSearchStrategy();
        _workers = _MakeWorkers(_matchTasksQueue, _linesQueueCondition, _linesQueueMutex);
    }

    std::shared_ptr<Report> _MakeReport(const std::vector<Match>& matches) {

        auto report = std::make_shared<Report>();

        for(auto match : matches) {
            report->matches.insert(std::pair<uint64_t,Match>(match.lineNumber, match));
        }

        return report;
    }

    std::shared_ptr<LinesReaderThread> _MakeLinesReader(const std::string& fileName) {

        auto linesReader = std::make_shared<LinesReader>(fileName, this);
        return std::make_shared<LinesReaderThread>(linesReader);
    }

    unsigned _GetNumberOfWorkers() {
        return std::thread::hardware_concurrency() == 0 ? 2 : std::thread::hardware_concurrency();
    }

    std::string _MakeThreadName(size_t id) {
        std::ostringstream oss;
        oss << id;
        return oss.str();
    }

    std::vector<std::shared_ptr<WorkerThread>> _MakeWorkers(std::shared_ptr<SearchTaskQueue> linesQueue,
                                                            std::condition_variable& linesQueueCondition, std::mutex& linesQueueMutex) {

        auto numberOfWorkers = _GetNumberOfWorkers();

        std::vector<std::shared_ptr<WorkerThread>> workerThreads;

        for(size_t i = 0; i < numberOfWorkers; i++) {
            const std::shared_ptr<WorkerThread> matchSeekerThread = std::make_shared<WorkerThread>(linesQueue, 
                                                linesQueueCondition, linesQueueMutex, _MakeThreadName(i));
            workerThreads.push_back(matchSeekerThread);
        }

        return workerThreads;
    }

private:

    std::condition_variable _linesQueueCondition;
    std::mutex _linesQueueMutex;
    std::shared_ptr<SearchTaskQueue> _matchTasksQueue;
    std::shared_ptr<LinesReaderThread> _linesReader;
    std::vector<std::shared_ptr<WorkerThread>> _workers;
    const InputParameters& _inputParameters;
    std::vector<std::future<std::vector<Match>>> _results;
    std::shared_ptr<SearchFactory> _searchFactory;
    std::shared_ptr<SearchStrategy> _searchStrategy;
};

#endif // APPLICATION_H