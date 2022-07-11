#ifndef QTWORLD_SERIALIZATION_H
#define QTWORLD_SERIALIZATION_H
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

class loginReq{
public:
    void serialize();
    static json deserialize(string email, string password);
};

class loginRes{
public:
    static string serialize(json j);
    void deserialize();
};

#endif //QTWORLD_SERIALIZATION_H
