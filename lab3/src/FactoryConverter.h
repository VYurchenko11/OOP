#ifndef FACTORYCONVERTER_H
#define FACTORYCONVERTER_H

#include <string>
#include "Converter.h"

class ConverterFactory {
public:
    virtual ~ConverterFactory() = default;
    virtual Converter* create(std::vector<std::string> &args) const = 0;
};

class MuteFactory : public ConverterFactory {
public:
    Converter* create(std::vector<std::string> &args) const override;
};

class MixFactory : public ConverterFactory {
public:
    Converter* create(std::vector<std::string> &args) const override;
};

class SpeedFactory : public ConverterFactory {
public:
    Converter* create(std::vector<std::string> &args) const override;
};

#endif