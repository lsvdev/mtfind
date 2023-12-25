#ifndef ILINES_READER_OBSERVER_H
#define ILINES_READER_OBSERVER_H

#include <string>

class ILinesReaderObserver {

    public:
        
        virtual void OnNewLine(uint64_t lineNumber, const std::string& line) = 0;
        virtual void OnReadingFinished() = 0;
};

#endif