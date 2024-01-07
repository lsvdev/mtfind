#ifndef LINES_QUEUE_H
#define LINES_QUEUE_H

#include "SearchTask.h"
#include <string>
#include <deque>
#include <mutex>
#include <atomic>

class SearchTaskQueue
{
public:

    SearchTaskQueue(std::condition_variable& condition, std::mutex& mutex): 
        _condition(condition), _mutex(mutex), _readingFinished(false) {}

    void PushBack(SearchTask_t task);
    SearchTask_t PopFront();
    bool IsEmpty() const { return _queue.empty(); }
    bool IsFinished() const { return _readingFinished; }
    void NotifyFinished();

private:

    std::deque<SearchTask_t> _queue;
    std::condition_variable& _condition;
    std::mutex& _mutex;
    std::atomic_bool _readingFinished;
};


#endif //LINES_QUEUE_H