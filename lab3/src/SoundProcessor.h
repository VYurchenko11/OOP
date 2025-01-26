#ifndef SOUNDPROCESSOR_H
#define SOUNDPROCESSOR_H

#include <string>
#include <vector>
#include <memory>
#include "ConfigParser.h"
#include "FactoryConverter.h"

class SoundProcessor {
private:
    std::string configFile;
    std::vector<std::string> inputFiles;
    std::string outputFile;
    std::vector<Converter*> converters;
    std::vector<std::vector<int16_t>> inputSamples;

public:
    SoundProcessor(const std::string& configFile, const std::vector<std::string>& inputFiles, const std::string& outputFile);
    ~SoundProcessor() = default;
    void initializeConverters();
    void loadInputFiles();
    void executeProcessing();
    void process();

};

#endif
