#include "InputParametersReader.h"
#include "MtfindConfig.h"

#include <fstream>
#include <iostream>
#include <regex>

const int ONE_GIGABYTE = 1024 * 1024 * 1024;

std::string ReadFileName(const std::string &input)
{
    std::ifstream file(input);

    if (!file.good())
    {
        throw std::invalid_argument("Can't open input file");
    }

    file.seekg(0, std::ios::end);
    auto fileSize = file.tellg();

    if(fileSize > ONE_GIGABYTE) {
        throw std::invalid_argument("File size should not exceed 1 GB");
    }

    file.close();

    return input;
}

std::regex ReadMask(const std::string &input)
{
    if (input.length() > 1000)
    {
        throw std::invalid_argument("Search mask should be not more than 1000 characters length");
    }

    if(input.find("\n") != std::string::npos) {
        throw std::invalid_argument("Search mask should not contain new line character");
    }

    std::string translatedMask(input);
    std::replace(translatedMask.begin(), translatedMask.end(), '?', '.');

    return std::regex(translatedMask);
}

void PrintVersion(char *argv[])
{
    std::cout << "\tVersion " << Mtfind_VERSION_MAJOR << "." << Mtfind_VERSION_MINOR << std::endl;
    std::cout << "\tUsage: mtfind <FILE_NAME> <SEARCH_MASK>" << std::endl;
}

InputParameters InputParametersReader::Read(int argc, char *argv[])
{
    if (argc < 2)
    {
        PrintVersion(argv);
        exit(1);
    }

    auto fileName = ReadFileName(argv[1]);
    auto searchMask = ReadMask(argv[2]);

    return InputParameters{fileName, searchMask};
}