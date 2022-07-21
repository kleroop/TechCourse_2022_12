#include "DAL.h"

#include <Poco/Data/PostgreSQL/PostgreSQLException.h>
#include <Poco/Data/PostgreSQL/Connector.h>
#include <Poco/Data/Session.h>
#include <Poco/Exception.h>
#include <Poco/Data/DataException.h>
#include <cstring>

using Poco::Data::PostgreSQL::ConnectionException;
using Poco::Data::PostgreSQL::Connector;
using Poco::Data::PostgreSQL::PostgreSQLException;
using Poco::Data::PostgreSQL::StatementException;
using namespace Poco;

// dumb but cpp can't static initialize object without constructing
Data::Session *session_ = nullptr;
#define session (*session_)

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

using std::string;

class DUser
{
public:
    int32_t id;
    // max length defined by the standard + nul terminator
    string username, email, pwdHash;
    bool isAdmin;
    DALUser toPOD()
    {
        DALUser r;
        r.id = id;
        strcpy(r.username, username.c_str());
        strcpy(r.email, email.c_str());
        strcpy(r.pwdHash, pwdHash.c_str());
        r.isAdmin = isAdmin;
        return r;
    };
};

DALStatus DALInitEx(bool dropTables)
{
    Connector::registerConnector();
    try {
        session_ = new Data::Session(
                Connector::KEY,
                "host=localhost port=5432 user=postgres password=admin dbname=test");
    } catch (Data::ConnectionFailedException &e) {
        puts(e.what());
        return DAL_CONNECTION_FAILED;
    }
    if (dropTables) {
        Statement drop(session);
        drop << "DROP TABLE IF EXISTS DUser CASCADE;";
        try {
            drop.execute();
        } catch (const Poco::Exception &e) {
            puts(e.displayText().c_str());
            return DAL_ERROR;
        }
    }

    Statement create(session);
    create << "CREATE TABLE IF NOT EXISTS DUser ("
              "    id SERIAL PRIMARY KEY,"
              "    username VARCHAR(32) NOT NULL UNIQUE,"
              "    email VARCHAR(320) NOT NULL UNIQUE,"
              "    pwdHash VARCHAR(32) NOT NULL,"
              "    isAdmin BOOL NOT NULL"
              ")";
    try {
        create.execute();
    } catch (const Poco::Exception &e) {
        puts(e.displayText().c_str());
        return DAL_ERROR;
    }

    return DAL_OK;
}

DALStatus DALInit()
{
    return DALInitEx(false);
}

void DALQuit()
{
    session.close();
    delete session_;
}

DALStatus DALUserCreate(DALUser *out, const char *username, const char *email, const char *pwdHash,
                        bool isAdmin)
{
    DUser du;
    Statement insert(session);
    insert << "INSERT INTO DUser (username, email, pwdHash, isAdmin) "
              "VALUES ($1, $2, $3, $4) "
              "ON CONFLICT DO NOTHING "
              "RETURNING id ",
            use(username), use(email), use(pwdHash), use(isAdmin), into(du.id);
    try {
        if (!insert.execute()) {
            return DAL_USER_EXISTS;
        }
    } catch (const Poco::Exception &e) {
        puts(e.displayText().c_str());
        return DAL_ERROR;
    }
    if (out) {
        du.username = username;
        du.email = email;
        du.pwdHash = pwdHash;
        du.isAdmin = isAdmin;
        *out = du.toPOD();
    }
    return DAL_OK;
}

DALStatus DALUserGetById(DALUser *out, uint32_t id)
{
    DUser du;
    Statement select(session);
    select << "SELECT id, username, email, pwdHash, isAdmin FROM DUser WHERE id=$1", into(du.id),
            into(du.username), into(du.email), into(du.pwdHash), into(du.isAdmin), use(id);
    try {
        if (!select.execute()) {
            return DAL_NOT_FOUND;
        }

    } catch (const Poco::Exception &e) {
        puts(e.displayText().c_str());
        return DAL_ERROR;
    }
    if (out)
        *out = du.toPOD();
    return DAL_OK;
}

DALStatus DALUserGetByUsername(DALUser *out, const char *username)
{
    DUser du;
    Statement select(session);
    select << "SELECT id, username, email, pwdHash, isAdmin FROM DUser WHERE username=$1",
            into(du.id), into(du.username), into(du.email), into(du.pwdHash), into(du.isAdmin),
            use(username);
    try {
        if (!select.execute()) {
            return DAL_NOT_FOUND;
        }

    } catch (const Poco::Exception &e) {
        puts(e.displayText().c_str());
        return DAL_ERROR;
    }
    if (out)
        *out = du.toPOD();
    return DAL_OK;
}

DALStatus DALUserGetByEmail(DALUser *out, const char *email)
{
    DUser du;
    Statement select(session);
    select << "SELECT id, username, email, pwdHash, isAdmin FROM DUser WHERE email=$1", into(du.id),
            into(du.username), into(du.email), into(du.pwdHash), into(du.isAdmin), use(email);
    try {
        if (!select.execute()) {
            return DAL_NOT_FOUND;
        }

    } catch (const Poco::Exception &e) {
        puts(e.displayText().c_str());
        return DAL_ERROR;
    }
    if (out)
        *out = du.toPOD();
    return DAL_OK;
}

DALStatus DALUserEdit(const DALUser *in)
{
    Statement select(session);
    select << "UPDATE DUser SET (username, email, pwdHash, isAdmin) = ($1, $2, $3, $4) "
              "WHERE id=$5",
            bind(in->username), bind(in->email), bind(in->pwdHash), bind(in->isAdmin), bind(in->id);
    try {
        if (!select.execute()) {
            return DAL_NOT_FOUND;
        }

    } catch (const Poco::Exception &e) {
        puts(e.displayText().c_str());
        return DAL_ERROR;
    }
    return DAL_OK;
}

DALStatus DALUserDelete(uint32_t id)
{
    Statement select(session);
    select << "DELETE FROM DUser WHERE id=$1", use(id);
    try {
        if (!select.execute()) {
            return DAL_NOT_FOUND;
        }

    } catch (const Poco::Exception &e) {
        puts(e.displayText().c_str());
        return DAL_ERROR;
    }
    return DAL_OK;
}
