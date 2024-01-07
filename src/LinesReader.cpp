#include "LinesReader.h"

#include <iostream>
#include <exception>

LinesReader::LinesReader(const std::string &fileName, ILinesReaderObserver* linesReaderObserver) : 
    _fileName(fileName), _linesReaderObserver(linesReaderObserver)
{
    _file.open(_fileName, std::ios::in);

    if (!_file.is_open())
    {
        throw std::logic_error("LinesReader::LinesReader() Can't open input file");
    }
}

LinesReader::~LinesReader() {

    if(_file.is_open()) {
        _file.close();
    }
}

void LinesReader::ReadLines()
{
    if (!_file.is_open())
    {
        std::cout << "LinesReader::ReadLines() Input file is not open for reading" << std::endl;
    }

    int lineNumber = 1;
    std::string line;

    while (std::getline(_file, line))
    {    
        _linesReaderObserver->OnNewLine(lineNumber++, line);
    }

    _linesReaderObserver->OnReadingFinished();
}

