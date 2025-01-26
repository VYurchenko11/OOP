#include "CommandParser.h"
#include "Exceptions.h"
#include "SoundProcessor.h"
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        CommandParser parser(argc, argv);
        const bool help = parser.parse();
        if (!help) {
            return 0;
        }
        SoundProcessor processor(parser.getConfigFile(), parser.getInputFiles(), parser.getOutputFile());
        processor.process();
        
    }catch (const FileException &e) {
        std::cerr << "File error: " << e.what() << std::endl;
        return 2;
    } catch (const ConfigException &e) {
        std::cerr << "Configuration error: " << e.what() << std::endl;
        return 3;
    } catch (const ConverterException &e) {
        std::cerr << "Converter error: " << e.what() << std::endl;
        return 4;
    } catch (const std::exception &e) {
       std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 5;
    }
    return 0;
}