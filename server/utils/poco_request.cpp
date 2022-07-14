#include "poco_request.h"

nlohmann::json toJson(std::istream &data)
{
    return nlohmann::json::parse(data);
}
