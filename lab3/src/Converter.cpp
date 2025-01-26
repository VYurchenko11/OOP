#include "Converter.h"
#include "Exceptions.h"
#include "WAVReaderFile.h"
#include <cctype>
#include <algorithm>
#include <cstdint>

bool isNumber(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

bool isFileReference(const std::string& str) {
    return str.size() > 1 && str[0] == '$' && isNumber(str.substr(1));
}

MuteConverter::MuteConverter(const std::vector<std::string>& parameters) {
    if (parameters.size() != 3) {
        throw ConverterException("Mute Converter requires exactly 3 arguments: mute <start> <end>");
    }
    if (!isNumber(parameters[1]) || !isNumber(parameters[2])) {
        throw ConverterException("Mute Converter: start and end must be positive integers");
    }
    start = std::stoi(parameters[1]);
    end = std::stoi(parameters[2]);
    if (start >= end) {
        throw ConverterException("Mute Converter: start time must be less than end time");
    }
}

MixConverter::MixConverter(const std::vector<std::string>& parameters) {
    if (parameters.size() != 3) {
        throw ConverterException("Mix Converter requires exactly 3 arguments: mix <fileNumber> <start>");
    }
    if (!isFileReference(parameters[1])) {
        throw ConverterException("Mix Converter: fileNumber must be in the format $<number>");
    }
    if (!isNumber(parameters[2])) {
        throw ConverterException("Mix Converter: start must be a positive integer");
    }
    fileNumber = std::stoi(parameters[1].substr(1)); // Убираем '$' и преобразуем в число
    start = std::stoi(parameters[2]);
}

SpeedConverter::SpeedConverter(const std::vector<std::string>& parameters) {
    if (parameters.size() != 4) {
        throw std::invalid_argument("Speed Converter requires exactly 4 arguments: speed <start> <end> <factor>");
    }
    try {
        start = std::stoi(parameters[1]);
        end = std::stoi(parameters[2]);
        speedFactor = std::stof(parameters[3]);
    } catch (const std::exception&) {
        throw std::invalid_argument("Speed Converter: start, end, and factor must be valid numbers");
    }

    if (start < 0 || end <= start) {
        throw std::invalid_argument("Speed Converter: invalid interval (start must be >= 0 and end > start)");
    }
    if (speedFactor <= 0) {
        throw std::invalid_argument("Speed Converter: speed factor must be greater than 0");
    }
}

std::vector<int16_t> MuteConverter::convert(const std::vector<int16_t> &samples, const std::vector<std::vector<int16_t>> &extraInputs) const {
    std::vector<int16_t> result = samples;
    const int startMute = start * sampleRate;
    const int endMute = end * sampleRate;
    for (int i = startMute; i < endMute; i++) {
        result[i] = 0;
    }
    return result;
}

std::vector<int16_t> MixConverter::convert(const std::vector<int16_t> &samples, const std::vector<std::vector<int16_t>> &extraInputs) const {
    std::vector<int16_t> result = samples;
    const std::vector<int16_t>& secondStream = extraInputs[fileNumber - 1];
    const int startMix = start * sampleRate;
    const int minSize = std::min(result.size() - startMix, secondStream.size());
    for (int i = 0; i < minSize; i++) {
        result[startMix + i] = (result[startMix + i] + secondStream[i]) / 2;
    }
    return result;
}

std::vector<int16_t> SpeedConverter::convert(const std::vector<int16_t> &samples, const std::vector<std::vector<int16_t>> &extraInputs) const {
    if (samples.empty()) {
        return {};
    }

    int startSample = start * sampleRate;
    int endSample = end * sampleRate;

    if (startSample < 0 || endSample > static_cast<int>(samples.size()) || startSample >= endSample) {
        throw std::out_of_range("SpeedConverter: invalid interval");
    }

    std::vector<int16_t> fragment(samples.begin() + startSample, samples.begin() + endSample);

    size_t newSize = static_cast<size_t>(fragment.size() / speedFactor);
    std::vector<int16_t> acceleratedFragment(newSize);

    for (size_t i = 0; i < newSize; ++i) {
        size_t originalIndex = static_cast<size_t>(i * speedFactor);
        acceleratedFragment[i] = fragment[originalIndex];
    }

    std::vector<int16_t> result;
    
    result.insert(result.end(), samples.begin(), samples.begin() + startSample);
    result.insert(result.end(), acceleratedFragment.begin(), acceleratedFragment.end());
    result.insert(result.end(), samples.begin() + endSample, samples.end());

    return result;
}



std::string MuteConverter::getDescription() const {
    return "Mute Converter\nMutes audio fragment of input1.wav\n"
           "Usage: mute <start second> <end second>\n\n";
}

std::string MixConverter::getDescription() const {
    return "Mix Converter\nMixes audio fragment of input1.wav with other input.wav\n"
           "Usage: mix $<input file number> <start second>\n\n";
}

std::string SpeedConverter::getDescription() const {
    return "Speed Converter\nAccelerates audio fragment of input1.wav by integer multiplier\n"
           "Usage: speed <start second> <end second>\n\n";
}