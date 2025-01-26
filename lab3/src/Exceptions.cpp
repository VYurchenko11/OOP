#include "Exceptions.h"

BaseException::BaseException(const std::string& msg) : message(msg) {}

const char* BaseException::what() const noexcept {
    return message.c_str();
}


FileException::FileException(const std::string& msg) : BaseException("File error: " + msg) {}


ConfigException::ConfigException(const std::string& msg) : BaseException("Config error: " + msg) {}

ConverterException::ConverterException(const std::string& msg) : BaseException("Converter error: " + msg) {}

UnsupportedFormatException::UnsupportedFormatException(const std::string& msg) : BaseException("Unsupported format error: " + msg) {}
