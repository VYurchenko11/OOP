#ifndef WAVWRITERFILE_H
#define WAVWRITERFILE_H

#include "WAVReaderFile.h"
#include <string>
#include <vector>
#include <cstdint>


class WAVWriterFile {
private:
    std::string filePath;
public:
    explicit WAVWriterFile(const std::string& filePath);
    ~WAVWriterFile();
    void write(const WAVHeader& header, const std::vector<int16_t>& samples);
};

#endif 