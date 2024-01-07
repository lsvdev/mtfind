#include "SearchTaskQueue.h"
#include <iostream>

void SearchTaskQueue::PushBack(SearchTask_t task) {

    std::lock_guard<std::mutex> lock(_mutex);
    _queue.push_back(std::move(task));
    _condition.notify_all();
}

SearchTask_t SearchTaskQueue::PopFront() 
{ 
    auto task = std::move(_queue.front());
    _queue.pop_front();
    return std::move(task);
}

void SearchTaskQueue::NotifyFinished() {
    std::lock_guard<std::mutex> lock(_mutex);
    _readingFinished = true;
    _condition.notify_all();
}