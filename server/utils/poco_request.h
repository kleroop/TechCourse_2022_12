#ifndef QTWORLD_POCO_REQUEST_H
#define QTWORLD_POCO_REQUEST_H

#include <nlohmann/json.hpp>
#include <streambuf>

using namespace nlohmann;

json toJson(std::istream &data);

#endif
