#ifndef INPUT_PARAMETERS_READER_H
#define INPUT_PARAMETERS_READER_H

#include "InputParameters.h"

class InputParametersReader {

public:

    InputParameters Read(int argc, char* argv[]);
};


#endif // INPUT_PARAMETERS_READER_H