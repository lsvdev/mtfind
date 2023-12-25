#ifndef REPORT_H
#define REPORT_H

#include <cstdint>
#include <vector>
#include <string>
#include <map>
#include <iostream>

struct Match {
    uint64_t lineNumber;
    uint64_t position;
    std::string matchedString;
};

struct Report {
    std::multimap<uint64_t,Match> matches;
    friend std::ostream& operator << (std::ostream& ostr, const Report& report);
};

#endif // REPORT_H