#ifndef QTWORLD_SERIALIZABLE_H
#define QTWORLD_SERIALIZABLE_H

#include <nlohmann/json.hpp>

using namespace nlohmann;

class ISerializable
{
public:
    std::string error;

    virtual json serialize() = 0;
    virtual void deserialize(json data) = 0;
};

#endif
