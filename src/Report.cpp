#include "Report.h"

std::ostream& operator << (std::ostream& ostr, const Report& report) {

    ostr << report.matches.size() << std::endl;

    for(auto& match: report.matches) {
        ostr << match.first << " " 
             << match.second.position << " "
             << match.second.matchedString
             << std::endl;
    }

    return ostr;
}