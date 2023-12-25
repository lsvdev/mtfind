#ifndef LINES_READER_THREAD_H
#define LINES_READER_THREAD_H

#include "LinesReader.h"

#include <memory>
#include <thread>
#include <iostream>

class LinesReaderThread
{

public:

    LinesReaderThread(std::shared_ptr<LinesReader> linesReader) : _linesReader(linesReader) {}

    void Start();

    void Wait() {
        if(_thread.joinable()) {
            _thread.join();
        }
    }
    
private:

    std::shared_ptr<LinesReader> _linesReader;
    std::thread _thread;
};


#endif // LINES_READER_THREAD_H