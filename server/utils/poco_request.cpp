#include "poco_request.h"

json toJson(std::istream &data)
{
    return nlohmann::json::parse(data);
}
