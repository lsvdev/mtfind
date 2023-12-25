#include "WorkerThread.h"

#include <chrono>
#include <vector>


void WorkerThread::Start()
{
    _thread = std::move(std::thread(&WorkerThread::WorkerFunction, this));
}

void WorkerThread::WorkerFunction() {

    while(true) {

        std::unique_lock<std::mutex> lock(_mutex);
        _condition.wait_for(lock, std::chrono::milliseconds(50), 
            [this] { return !_tasksQueue->IsEmpty() || _tasksQueue->IsFinished(); });

        if(_tasksQueue->IsFinished() && _tasksQueue->IsEmpty()) {
            lock.unlock();
            break;
        } else if (!_tasksQueue->IsEmpty()) {

            MatchTask_t matchTask = _tasksQueue->PopFront();
            lock.unlock();

            matchTask();
        }
    }
}