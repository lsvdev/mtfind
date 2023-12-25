#include "LinesReaderThread.h"

void LinesReaderThread::Start()
{
    _thread = std::move(std::thread(&LinesReader::ReadLines, _linesReader));
}