#include "SoundProcessor.h"
#include "WAVReaderFile.h"
#include "WAVWriterFile.h"
#include <stdexcept>
#include <memory> // Для использования умных указателей

SoundProcessor::SoundProcessor(const std::string& configFile, const std::vector<std::string>& inputFiles, const std::string& outputFile)
    : configFile(configFile), inputFiles(inputFiles), outputFile(outputFile) {
    inputSamples.resize(inputFiles.size());
}

void SoundProcessor::initializeConverters() {
    ConfigParser parser(configFile);

    for (int i = 0; i < parser.getLinesCount(); ++i) {
        std::vector<std::string> args = parser.parseLine(i);

        if (args.empty() || (args[0].front() == '#')) {
            continue; // Игнорируем пустые строки и комментарии
        }

        Converter* converter = nullptr;
        if (args[0] == "mute") {
            MuteFactory muteFactory;
            converter = muteFactory.create(args);
        } else if (args[0] == "mix") {
            MixFactory mixFactory;
            converter = mixFactory.create(args);
        } else if (args[0] == "speed") {
            SpeedFactory speedFactory;
            converter = speedFactory.create(args);
        } else {
            throw std::invalid_argument("Unsupported converter type: " + args[0]);
        }

        if (converter) {
            converters.push_back(converter);
        }
    }
}

void SoundProcessor::loadInputFiles() {
    for (int i = 0; i < inputFiles.size(); i++) {
        WAVReaderFile reader(inputFiles[i]);
        reader.read();
        inputSamples[i] = reader.getSamples();
    }
}

void SoundProcessor::executeProcessing() {
    WAVReaderFile mainReader(inputFiles[0]);
    mainReader.read();

    std::vector<int16_t> processedSamples = mainReader.getSamples();
    loadInputFiles();
    initializeConverters();

    for (const auto& converter : converters) {
        processedSamples = converter->convert(processedSamples, inputSamples);
    }

    WAVWriterFile writer(outputFile);
    WAVHeader header = mainReader.getHeader();
    header.subchunk2Size = processedSamples.size() * sizeof(int16_t);
    writer.write(header, processedSamples);
}

void SoundProcessor::process() {
    try {
        executeProcessing();
    } catch (const std::exception& e) {
        throw std::runtime_error("Error during processing: " + std::string(e.what()));
    }
}
