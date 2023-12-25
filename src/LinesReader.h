#ifndef LINES_READER_H
#define LINES_READER_H

#include "ILinesReaderObserver.h"

#include <memory>
#include <string>
#include <thread>
#include <fstream>
#include <mutex>
#include <utility>

class LinesReader
{
public:

    LinesReader(const std::string& fileName, ILinesReaderObserver* linesReaderObserver);
    ~LinesReader();

    void ReadLines();
    
private:

    const std::string _fileName;
    std::ifstream _file;
    ILinesReaderObserver* _linesReaderObserver;
};

#endif // LINES_READER_H