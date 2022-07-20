#include "DAL.h"

#include <Poco/Data/PostgreSQL/PostgreSQLException.h>
#include <Poco/Data/PostgreSQL/Connector.h>
#include <Poco/Data/Session.h>
#include <Poco/Exception.h>
#include <Poco/Data/DataException.h>
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
    string username, email, pwd_hash;
    bool is_admin;
    DALUser toPOD()
    {
        DALUser r;
        r.id = id;
        strcpy(r.username, username.c_str());
        strcpy(r.email, email.c_str());
        strcpy(r.pwd_hash, pwd_hash.c_str());
        r.is_admin = is_admin;
        return r;
    };
};

DALStatus DALInit()
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
    try {
        session << "CREATE TABLE IF NOT EXISTS DUser ("
                   "    id SERIAL PRIMARY KEY,"
                   "    username VARCHAR(32) NOT NULL UNIQUE,"
                   "    email VARCHAR(320) NOT NULL UNIQUE,"
                   "    pwd_hash VARCHAR(32) NOT NULL,"
                   "    is_admin BOOL NOT NULL"
                   ")",
                now;
    } catch (Poco::Exception &e) {
        puts(e.displayText().c_str());
        return DAL_ERROR;
    }
    return DAL_OK;
}

void DALQuit()
{
    session.close();
    delete session_;
}

DALStatus DALUserCreate(DALUser *out, const char *username, const char *email, const char *pwd_hash,
                        bool is_admin)
{
    DUser du;
    Statement insert(session);
    insert << "INSERT INTO DUser (username, email, pwd_hash, is_admin) "
              "VALUES ($1, $2, $3, $4) "
              "ON CONFLICT DO NOTHING "
              "RETURNING id ",
            use(username), use(email), use(pwd_hash), use(is_admin), into(du.id);
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
        du.pwd_hash = pwd_hash;
        du.is_admin = is_admin;
        *out = du.toPOD();
    }
    return DAL_OK;
}

DALStatus DALUserGetById(DALUser *out, uint32_t id)
{
    DUser du;
    Statement select(session);
    select << "SELECT id, username, email, pwd_hash, is_admin FROM DUser WHERE id=$1", into(du.id),
            into(du.username), into(du.email), into(du.pwd_hash), into(du.is_admin), use(id);
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
    select << "SELECT id, username, email, pwd_hash, is_admin FROM DUser WHERE username=$1",
            into(du.id), into(du.username), into(du.email), into(du.pwd_hash), into(du.is_admin),
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
    select << "SELECT id, username, email, pwd_hash, is_admin FROM DUser WHERE email=$1",
            into(du.id), into(du.username), into(du.email), into(du.pwd_hash), into(du.is_admin),
            use(email);
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
    select << "UPDATE DUser SET (username, email, pwd_hash, is_admin) = ($1, $2, $3, $4) "
              "WHERE id=$5",
            bind(in->username), bind(in->email), bind(in->pwd_hash), bind(in->is_admin),
            bind(in->id);
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
