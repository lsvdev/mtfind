#include "Application.h"

int main(int argc, char *argv[])
{
    try
    {
        InputParametersReader paramsReader;
        auto inputParameters = paramsReader.Read(argc, argv);

        Application app(&inputParameters);
        auto report = app.Run();

        std::cout << *(report);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    return 0;
}