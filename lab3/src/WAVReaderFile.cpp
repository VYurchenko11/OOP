#include "WAVReaderFile.h"
#include "Exceptions.h"
#include <fstream>
#include <iostream>
#include <cstring>

WAVReaderFile::WAVReaderFile(const std::string& filePath) : filePath(filePath) {}

void WAVReaderFile::validateHeader() {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open WAV file: " + filePath);
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

    if (file.gcount() < sizeof(WAVHeader)) {
        throw std::runtime_error("Incomplete WAV header in file: " + filePath);
    }

    if (std::strncmp(header.chunkID, "RIFF", 4) != 0 ||
        std::strncmp(header.format, "WAVE", 4) != 0) {
        throw UnsupportedFormatException("Invalid WAV file format in file: " + filePath);
    }

    char subchunkID[4];
    uint32_t subchunkSize;

    while (file.read(subchunkID, 4)) {
        if (!file.read(reinterpret_cast<char*>(&subchunkSize), 4)) {
            throw FileException("Error reading subchunk size in WAV file: " + filePath);
        }

        if (std::strncmp(subchunkID, "data", 4) == 0) {
            std::memcpy(header.subchunk2ID, subchunkID, 4);
            header.subchunk2Size = subchunkSize;
            std::cout << "Found 'data' chunk!" << std::endl;
            break;
        }

        file.seekg(subchunkSize, std::ios::cur);
        if (file.eof()) {
            throw UnsupportedFormatException("No 'data' chunk found in WAV file: " + filePath);
        }
    }


    if (file.eof()) {
        throw UnsupportedFormatException("No 'data' block found in WAV file: " + filePath);
    }
}

void WAVReaderFile::read() {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw FileException("Cannot open WAV file: " + filePath);
    }

    file.read(reinterpret_cast<char *>(&header.chunkID), 4);
    file.read(reinterpret_cast<char *>(&header.chunkSize), 4);
    file.read(reinterpret_cast<char *>(&header.format), 4);

    if (std::strncmp(header.chunkID, "RIFF", 4) != 0 ||
        std::strncmp(header.format, "WAVE", 4) != 0) {
        throw UnsupportedFormatException("Invalid WAV file format: " + filePath);
    }

    file.read(reinterpret_cast<char *>(&header.subchunk1ID), 4);
    file.read(reinterpret_cast<char *>(&header.subchunk1Size), 4);
    file.read(reinterpret_cast<char *>(&header.audioFormat), 2);
    if (header.audioFormat != 1) {
        throw UnsupportedFormatException("Must be uncompressed PCM: " + filePath);
    }

    file.read(reinterpret_cast<char *>(&header.numChannels), 2);
    if (header.numChannels != 1) {
        throw UnsupportedFormatException("Must be mono: " + filePath);
    }

    file.read(reinterpret_cast<char *>(&header.sampleRate), 4);
    if (header.sampleRate != 44100) {
        throw UnsupportedFormatException("Must be 44100 Hz: " + filePath);
    }

    file.read(reinterpret_cast<char *>(&header.byteRate), 4);
    file.read(reinterpret_cast<char *>(&header.blockAlign), 2);
    file.read(reinterpret_cast<char *>(&header.bitsPerSample), 2);
    if (header.bitsPerSample != 16) {
        throw UnsupportedFormatException("Must be 16 bits per sample: " + filePath);
    }

    if (std::strncmp(header.subchunk1ID, "fmt ", 4) != 0) {
        throw UnsupportedFormatException("Unsupported WAV format: " + filePath);
    }

    uint32_t subchunkSize;
    while (true) {
        char subchunkID[4];
        file.read(subchunkID, 4);
        if (!file.read(reinterpret_cast<char *>(&subchunkSize), 4)) {
            throw FileException("Error reading subchunk size in WAV file: " + filePath);
        }

        if (std::strncmp(subchunkID, "data", 4) == 0) {
            std::memcpy(header.subchunk2ID, subchunkID, 4);
            header.subchunk2Size = subchunkSize;
            break;
        }

        if (subchunkSize > 0 && file.seekg(subchunkSize, std::ios::cur)) {
            continue;
        } else {
            throw FileException("Error seeking past subchunk in WAV file: " + filePath);
        }
    }

    const int numSamples = header.subchunk2Size / (header.bitsPerSample / 8);
    samples.resize(numSamples);
    file.read(reinterpret_cast<char *>(samples.data()), header.subchunk2Size);

    if (!file) {
        throw FileException("Error reading WAV file data: " + filePath);
    }

}

const WAVHeader& WAVReaderFile::getHeader() const {
    return header;
}

const std::vector<int16_t>& WAVReaderFile::getSamples() const {
    return samples;
}