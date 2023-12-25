#include "MatchTaskQueue.h"
#include <iostream>

void MatchTaskQueue::PushBack(MatchTask_t task) {

    std::lock_guard<std::mutex> lock(_mutex);
    _queue.push_back(std::move(task));
    _condition.notify_all();
}

MatchTask_t MatchTaskQueue::PopFront() 
{ 
    auto task = std::move(_queue.front());
    _queue.pop_front();
    return std::move(task);
}

void MatchTaskQueue::NotifyFinished() {
    std::lock_guard<std::mutex> lock(_mutex);
    _readingFinished = true;
    _condition.notify_all();
}