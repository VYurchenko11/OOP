#include "WAVWriterFile.h"
#include <fstream>
#include <stdexcept>

WAVWriterFile::WAVWriterFile(const std::string& filePath) : filePath(filePath) {}

WAVWriterFile::~WAVWriterFile() = default;

void WAVWriterFile::write(const WAVHeader& header, const std::vector<int16_t>& samples) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open WAV file for writing: " + filePath);
    }

    // Запись заголовка
    file.write(reinterpret_cast<const char*>(&header), sizeof(WAVHeader));
    if (!file) {
        throw std::runtime_error("Failed to write WAV header to file: " + filePath);
    }

    // Запись аудиоданных
    file.write(reinterpret_cast<const char*>(samples.data()), samples.size() * sizeof(int16_t));
    if (!file) {
        throw std::runtime_error("Failed to write WAV data to file: " + filePath);
    }

    file.close();
}