#ifndef INPUT_PARAMETERS_H
#define INPUT_PARAMETERS_H

#include <string>
#include <regex>

struct InputParameters {
  std::string fileName;
  std::string searchMask;
  std::regex regexMask;
};

#endif //