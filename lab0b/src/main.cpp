#include "App.h"
#include <iostream>
#include <string>

void runApp(const std::string& inputFileName, const std::string& outputFileName) 
{
    App app;
    app.begin(inputFileName, outputFileName);
}

int main(int argc, char* argv[]) 
{
    if (argc != 3) 
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }
    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];

    runApp(inputFileName, outputFileName);

    return 0;
}