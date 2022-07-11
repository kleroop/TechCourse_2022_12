#include "serialization.h"
#include<QDebug>

using namespace std;

void loginReq::serialize(){

}

json loginReq::deserialize(string email, string password){ //mail pass -> json
    json j = {
            {"email", email},
            {"password", password}
    };
    return j;
}

string loginRes::serialize(json j){
    string token = j["token"];
    return token;
}

void loginRes::deserialize(){

}

