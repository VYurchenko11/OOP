cmake_minimum_required(VERSION 3.26)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(lab3
        src/main.cpp
        src/CommandParser.cpp
        src/Converter.cpp
        src/ConfigParser.cpp
        src/FactoryConverter.cpp
        src/Exceptions.cpp
        src/SoundProcessor.cpp
        src/WAVReaderFile.cpp
        src/WAVWriterFile.cpp)

