#ifndef WAVREADERFILE_H
#define WAVREADERFILE_H

#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>

struct WAVHeader {
    char chunkID[4];       
    uint32_t chunkSize;    
    char format[4];        
    char subchunk1ID[4];   
    uint32_t subchunk1Size;
    uint16_t audioFormat;  
    uint16_t numChannels;  
    uint32_t sampleRate;   
    uint32_t byteRate;     
    uint16_t blockAlign;   
    uint16_t bitsPerSample;
    char subchunk2ID[4];   
    uint32_t subchunk2Size;
};

class WAVReaderFile {
private:
    std::string filePath;
    WAVHeader header;
    std::vector<int16_t> samples;

    void validateHeader();

public:
    explicit WAVReaderFile(const std::string& filePath);

    void read();

    const WAVHeader& getHeader() const;

    const std::vector<int16_t>& getSamples() const;
};

#endif
