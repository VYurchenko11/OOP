#include "FactoryConverter.h"
#include <vector>

Converter *MuteFactory::create(std::vector<std::string> &args) const {
    return new MuteConverter(args);
}

Converter *MixFactory::create(std::vector<std::string> &args) const {
    return new MixConverter(args);
}

Converter *SpeedFactory::create(std::vector<std::string> &args) const {
    return new SpeedConverter(args);
}