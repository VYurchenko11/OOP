#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

// Базовый класс исключений
class BaseException : public std::exception {
protected:
    std::string message;

public:
    explicit BaseException(const std::string& msg);
    virtual const char* what() const noexcept override;
};

class FileException : public BaseException {
public:
    explicit FileException(const std::string& msg);
};

class ConfigException : public BaseException {
public:
    explicit ConfigException(const std::string& msg);
};

class ConverterException : public BaseException {
public:
    explicit ConverterException(const std::string& msg);
};

class UnsupportedFormatException : public BaseException {
public:
    explicit UnsupportedFormatException(const std::string& msg);
};

#endif // EXCEPTIONS_H
