#include "dal.h"

#include <Poco/Data/PostgreSQL/Connector.h>
#include <Poco/Data/Session.h>
using namespace Poco::Data::PostgreSQL;
using namespace Poco;

// dumb but cpp can't static initialize object without constructing
Data::Session *session_ = nullptr;
#define session (*session_)

DALStatus DALInit()
{
    Connector::registerConnector();

    session_ = new Data::Session(Connector::KEY,
                                 "host=localhost port=5433 user=admin password=admin dbname=test");

    return DAL_OK;
}

void DALQuit()
{
    delete session_;
}

DALStatus DALUserCreate(DALUser *out, char *username, char *email, char *pwd_hash, bool is_admin)
{
    return DAL_OK;
}

DALStatus DALUserGetById(DALUser *out, uint32_t id)
{
    return DAL_OK;
}

DALStatus DALUserGetByUsername(DALUser *out, char *username)
{
    return DAL_OK;
}

DALStatus DALUserEdit(DALUser *inout)
{
    return DAL_OK;
}

DALStatus DALUserDelete(uint32_t id)
{
    return DAL_OK;
}
