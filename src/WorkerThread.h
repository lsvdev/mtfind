#ifndef MATCH_SEEKER_THREAD_H
#define MATCH_SEEKER_THREAD_H

#include "SearchTaskQueue.h"

#include <memory>
#include <thread>
#include <iostream>

class WorkerThread
{

public:

    WorkerThread(std::shared_ptr<SearchTaskQueue> linesQueue,
                      std::condition_variable& condition, 
                      std::mutex& mutex, const std::string& threadName) : 
                      _tasksQueue(linesQueue), _condition(condition), _mutex(mutex), _name(threadName) {}

    void Start();
    void Wait() {
        if(_thread.joinable()) {
            _thread.join();
        }
    }
    
private:

    void WorkerFunction();

    std::shared_ptr<SearchTaskQueue> _tasksQueue;
    std::condition_variable& _condition;
    std::mutex& _mutex;
    std::string _name;
    std::thread _thread;
};


#endif // LINES_READER_THREAD_H