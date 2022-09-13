#include "DAL.h"

#include <Poco/Data/PostgreSQL/PostgreSQLException.h>
#include <Poco/Data/PostgreSQL/Connector.h>
#include <Poco/Data/Session.h>
#include <Poco/Exception.h>
#include <Poco/Data/DataException.h>
#include <cstring>
#define eputs(s) fprintf(stderr, "%s\n", s)
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
using namespace DAL;

Status DAL::InitEx(string host, string port, string username, string dbname, string password,
                   bool dropTables)
{
    Connector::registerConnector();
    try {
        session_ =
                new Data::Session(Connector::KEY,
                                  "host=" + host + " port=" + port + " user="
                                          + username + " dbname=" + dbname + " password=" + password);
    } catch (Data::ConnectionFailedException &e) {
        eputs(e.what());
        return DAL_CONNECTION_FAILED;
    }
    if (dropTables) {
        Statement drop(session);
        for (auto &t : { "DUser", "DCategory", "DSubCategory", "DTeam" }) {
            drop << "DROP TABLE IF EXISTS " << t << " CASCADE;";
            try {
                drop.execute();
            } catch (const Poco::Exception &e) {
                eputs(e.displayText().c_str());
                return DAL_ERROR;
            }
            drop.reset(session);
        }
    }
    string tables[] = {
        "CREATE TABLE IF NOT EXISTS DUser ("
        "   id SERIAL PRIMARY KEY,"
        "   username VARCHAR(32) NOT NULL UNIQUE,"
        "   email VARCHAR(320) NOT NULL UNIQUE,"
        "   pwdHash VARCHAR(32) NOT NULL,"
        "   isAdmin BOOL NOT NULL"
        ")",

        "CREATE TABLE IF NOT EXISTS DCategory ("
        "   id SERIAL PRIMARY KEY,"
        "   name VARCHAR(32) NOT NULL UNIQUE,"
        "   isHidden BOOL NOT NULL"
        ")",
        "CREATE TABLE IF NOT EXISTS DSubCategory ("
        "   id SERIAL PRIMARY KEY,"
        "   name VARCHAR(32) NOT NULL UNIQUE,"
        "   isHidden BOOL NOT NULL,"
        "   categoryId SERIAL NOT NULL,"
        "   FOREIGN KEY(categoryId) REFERENCES DCategory(id) ON DELETE CASCADE"
        ")",
        "CREATE TABLE IF NOT EXISTS DTeam ("
        "   id SERIAL PRIMARY KEY,"
        "   name VARCHAR(32) NOT NULL UNIQUE,"
        "   isHidden BOOL NOT NULL,"
        "   subCategoryId SERIAL NOT NULL,"
        "   location VARCHAR(32),"
        "   dateCreated VARCHAR(32),"
        "   FOREIGN KEY(subCategoryId) REFERENCES DSubCategory(id) ON DELETE CASCADE"
        ")"
    };
    Statement create(session);
    for (auto &table : tables) {
        create << table;
        try {
            create.execute();
        } catch (const Poco::Exception &e) {
            eputs(e.displayText().c_str());
            return DAL_ERROR;
        }
        create.reset(session);
    }

    return DAL_OK;
}

Status DAL::Init(string host, string port, string username, string dbname, string password)
{
    return InitEx(host, port, username, dbname, password, false);
}

void DAL::Quit()
{
    session.close();
    delete session_;
}

static Statement DeleteQueryBuild(const string &table, string query, Bindings binds)
{
    Statement del(session);
    del << "DELETE FROM " << table << (!query.empty() ? " WHERE " : " ") << query, range(0, 1);
    for (auto &bind : binds) {
        del, bind;
    }
    return del;
}

static Statement SelectQueryBuild(const string &table, string query, Bindings binds)
{
    Statement select(session);
    select << "SELECT * FROM " << table << (!query.empty() ? " WHERE " : " ") << query;
    for (auto &bind : binds) {
        select, bind;
    }
    select, range(0, 1);
    return select;
}

static Statement InsertQueryBuild(const string &table, Bindings binds, int32_t &ret)
{
    Statement insert(session);
    string values_placeholder;
    size_t n = binds.size();
    for (size_t i = 0; i < n; i++) {
        values_placeholder += ", $" + std::to_string(i + 1);
    }
    insert << "INSERT INTO " << table << " VALUES (DEFAULT" << values_placeholder
           << ") "
              "ON CONFLICT DO NOTHING "
              "RETURNING id";
    for (auto &bind : binds)
        insert, bind;
    insert, into(ret);
    return insert;
}

static Statement InsertQueryBuildNodefault(const string &table, Bindings binds, int32_t &ret)
{
    Statement insert(session);
    string values_placeholder;
    size_t n = binds.size();
    for (size_t i = 0; i < n; i++) {
        values_placeholder += ", $" + std::to_string(i + 1);
    }
    insert << "INSERT INTO " << table << " VALUES (" << values_placeholder
           << ") "
              "ON CONFLICT DO NOTHING "
              "RETURNING id";
    for (auto &bind : binds)
        insert, bind;
    insert, into(ret);
    return insert;
}

static Statement UpdateQueryBuild(const string &table, string set, string query, Bindings binds)
{
    Statement update(session);
    update << "UPDATE " << table << " SET " << set << (!query.empty() ? " WHERE " : " ") << query;
    for (auto &bind : binds)
        update, bind;
    return update;
}

template<typename T>
static void executeInsert(T *model, Statement &statement)
{
    puts(statement.toString().c_str());
    model->status = DAL_OK;
    try {
        if (!statement.execute()) {
            model->status = DAL_OBJECT_EXISTS;
        }
    } catch (const Poco::Exception &e) {
        eputs(e.displayText().c_str());
        model->status = DAL_ERROR;
    }
}
template<typename T>
static void executeDelete(T *model, Statement &statement)
{
    puts(statement.toString().c_str());
    model->status = DAL_OK;
    try {
        if (!statement.execute()) {
            model->status = DAL_NOT_FOUND;
        }
    } catch (const Poco::Exception &e) {
        eputs(e.displayText().c_str());
        model->status = DAL_ERROR;
    }
}

template<typename T>
static std::vector<T> executeSelect(T *model, Statement &statement)
{
    std::vector<T> res;
    puts(statement.toString().c_str());
    model->status = DAL_OK;
    try {
        size_t i = 0;
        while (!statement.done() && statement.execute()) {
            res.push_back(*model);
            i++;
        }
        if (i == 0) {
            model->status = DAL_NOT_FOUND;
        }
    } catch (const Poco::Exception &e) {
        eputs(e.displayText().c_str());
        model->status = DAL_ERROR;
    }
    return res;
}

template<typename T>
static void executeUpdate(T *model, Statement &statement)
{
    puts(statement.toString().c_str());
    model->status = DAL_OK;
    try {
        if (!statement.execute()) {
            model->status = DAL_OBJECT_EXISTS;
        }
    } catch (const Poco::Data::PostgreSQL::StatementException &e) {
        eputs(e.displayText().c_str());
        model->status = DAL_OBJECT_EXISTS;
    }
}

User::User(string username, string email, string pwdHash, bool isAdmin)
{
    this->username = username;
    this->email = email;
    this->pwdHash = pwdHash;
    this->isAdmin = isAdmin;
}

void User::Create()
{
    Statement insert = InsertQueryBuild(
            getTable(),
            { bind(this->username), bind(this->email), bind(this->pwdHash), bind(this->isAdmin) },
            this->id);

    executeInsert(this, insert);
}

std::vector<User> User::Select(string query, Bindings binds)
{
    Statement select = SelectQueryBuild(getTable(), query, binds);

    select, into(this->id), into(this->username), into(this->email), into(this->pwdHash),
            into(this->isAdmin);

    return executeSelect(this, select);
}
void User::Update()
{
    Statement update = UpdateQueryBuild(
            getTable(), "username = $1, email = $2, pwdHash = $3, isAdmin = $4", "id = $5",
            { bind(username), bind(email), bind(pwdHash), bind(isAdmin), bind(id) });
    executeUpdate(this, update);
}

void User::Delete()
{
    Statement del = DeleteQueryBuild(getTable(), "id = $1", { bind(this->id) });
    executeDelete(this, del);
    this->id = DAL_BAD_ID;
}

Category::Category(string name, bool isHidden)
{
    this->name = name;
    this->isHidden = isHidden;
}
void Category::Create()
{
    Statement insert =
            InsertQueryBuild(getTable(), { bind(this->name), bind(this->isHidden) }, this->id);

    executeInsert(this, insert);
}
std::vector<Category> Category::Select(string query, Bindings binds)
{
    std::vector<Category> res;
    Statement select = SelectQueryBuild(getTable(), query, binds);
    select, into(this->id), into(this->name), into(this->isHidden);
    res = executeSelect(this, select);
    for (auto &cat : res) {
        cat.scats = SubCategory().Select("categoryId = $1", { bind(cat.id) });
        for (auto &scat : scats) {
            scat.cat = &cat;
        }
        *this = cat;
    }
    return res;
}

void Category::Update()
{
    Statement update = UpdateQueryBuild(getTable(), "name = $1, isHidden = $2", "id = $3",
                                        { bind(name), bind(isHidden), bind(id) });
    executeUpdate(this, update);
    auto id = this->id; /* fixme: preserve id */
    this->Delete(); /* delete all child elements */
    /* re-add this element and its children to db */
    this->Create();
    for (auto &scat : scats) {
        scat.cat = this;
        scat.Create();
        for (auto &team : scat.teams) {
            team.scat = &scat;
            team.Create();
        }
    }
}
void Category::Delete()
{
    Statement del = DeleteQueryBuild(getTable(), "id = $1", { bind(id) });
    executeDelete(this, del);
    this->id = DAL_BAD_ID;
}

SubCategory::SubCategory(string name, bool isHidden, Category *cat)
{
    this->name = name;
    this->isHidden = isHidden;
    this->cat = cat;
}
void SubCategory::Create()
{
    Statement insert = InsertQueryBuild(
            getTable(), { bind(this->name), bind(this->isHidden), bind(cat->id) }, this->id);

    executeInsert(this, insert);
}
std::vector<SubCategory> SubCategory::Select(string query, Bindings binds)
{
    std::vector<SubCategory> res;
    Statement select = SelectQueryBuild(getTable(), query, binds);
    int32_t cat_id;
    select, into(this->id), into(this->name), into(this->isHidden), into(cat_id);
    res = executeSelect(this, select);

    for (auto &scat : res) {
        scat.teams = Team().Select("subCategoryId = $1", { bind(scat.id) });
        for (auto &team : teams) {
            team.scat = &scat;
        }
        *this = scat;
    }

    return res;
}
void SubCategory::Update()
{
    Statement update =
            UpdateQueryBuild(getTable(), "name = $1, isHidden = $2, categoryId = $3", "id = $4",
                             { bind(name), bind(isHidden), bind(cat->id), bind(id) });
    executeUpdate(this, update);
}
void SubCategory::Delete()
{
    Statement del = DeleteQueryBuild(getTable(), "id = $1", { bind(id) });
    executeDelete(this, del);
    this->id = DAL_BAD_ID;
}

Team::Team(string name, bool isHidden, SubCategory *scat, string location, string dateCreated)
{
    this->name = name;
    this->isHidden = isHidden;
    this->scat = scat;
    this->location = location;
    this->dateCreated = dateCreated;
}
void Team::Create()
{
    Statement insert = InsertQueryBuild(getTable(), {
        bind(this->name),
        bind(this->isHidden),
        bind(scat->id),
        bind(this->location),
        bind(this->dateCreated)}, this->id);

    executeInsert(this, insert);
}
std::vector<Team> Team::Select(string query, Bindings binds)
{
    Statement select = SelectQueryBuild(getTable(), query, binds);
    int32_t cat_id;
    select, into(this->id), into(this->name), into(this->isHidden), into(cat_id), into(this->location), into(this->dateCreated);
    return executeSelect(this, select);
}
void Team::Update()
{
    Statement update = UpdateQueryBuild(getTable(),
                                        "name = $1, "
                                        "isHidden = $2, "
                                        "subCategoryId = $3, "
                                        "location = $4, "
                                        "dateCreated = $5",
                                        "id = $6",
                                {
                                        bind(name),
                                        bind(isHidden),
                                        bind(scat->id),
                                        bind(location),
                                        bind(dateCreated),
                                        bind(id)
                                     });
    executeUpdate(this, update);
}
void Team::Delete()
{
    Statement del = DeleteQueryBuild(getTable(), "id = $1", { bind(id) });
    executeDelete(this, del);
    this->id = DAL_BAD_ID;
}
