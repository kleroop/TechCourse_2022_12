#ifndef QTWORLD_SERIALIZABLE_H
#define QTWORLD_SERIALIZABLE_H

#include <nlohmann/json.hpp>

class ISerializable
{
protected:
    std::string _error;

public:
    std::string error();

    virtual nlohmann::json serialize() = 0;
    virtual void deserialize(nlohmann::json data) = 0;
};

#endif
