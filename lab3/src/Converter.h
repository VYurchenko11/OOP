#ifndef CONVERTER_H
#define CONVERTER_H

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cstdint>
#include <cmath>

class Converter {
protected:
    const int sampleRate = 44100; // Частота дискретизации

public:
    virtual ~Converter() = default;
    virtual std::vector<int16_t> convert(const std::vector<int16_t> &samples,
                                         const std::vector<std::vector<int16_t>> &extraInputs) const = 0;
    virtual std::string getDescription() const = 0;
};

class MuteConverter : public Converter {
private:
    int start;
    int end;

public:
    MuteConverter() = default;
    explicit MuteConverter(const std::vector<std::string>& parameters);
    std::vector<int16_t> convert(const std::vector<int16_t> &samples,
                                 const std::vector<std::vector<int16_t>> &extraInputs) const override;
    std::string getDescription() const override;
};

class MixConverter : public Converter {
private:
    int fileNumber;
    int start;

public:
    MixConverter() = default;
    explicit MixConverter(const std::vector<std::string>& parameters);
    std::vector<int16_t> convert(const std::vector<int16_t> &samples,
                                 const std::vector<std::vector<int16_t>> &extraInputs) const override;
    std::string getDescription() const override;
};

class SpeedConverter : public Converter {
private:
    int start;
    int end;
    float speedFactor; // Коэффициент изменения скорости
public:
    explicit SpeedConverter(const std::vector<std::string>& parameters);

    std::vector<int16_t> convert(const std::vector<int16_t>& samples, const std::vector<std::vector<int16_t>>& extraInputs) const override;

    std::string getDescription() const override;
};

#endif