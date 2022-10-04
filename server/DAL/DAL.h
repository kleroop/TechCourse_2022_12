#ifndef DAL_H
#define DAL_H
#include <cstdint>
#include "dal_export.h"
#include "Poco/Data/AbstractBinding.h"
#include <Poco/Data/Statement.h>
#include <string>
#include <optional>
#include <vector>
using std::string;
using std::vector;

typedef std::vector<Poco::Data::AbstractBinding::Ptr> Bindings;

namespace DAL {
#define DAL_BAD_ID INT32_MAX
using Poco::Data::Keywords::bind;

typedef enum { DAL_OK, DAL_ERROR, DAL_CONNECTION_FAILED, DAL_OBJECT_EXISTS, DAL_NOT_FOUND } Status;

template<typename T>
class IDataModel
{
public:
    virtual inline const string getTable() const = 0;
    Status status;
    virtual void Create() = 0;
    virtual vector<T> Select(string query, Bindings binds) = 0;
    virtual void Update() = 0;
    virtual void Delete() = 0;
};

class DAL_EXPORT User : public IDataModel<User>
{
public:
    inline const string getTable() const override { return "DUser"; };
    int32_t id = DAL_BAD_ID;
    string username, email, pwdHash;
    bool isAdmin;
    User(string username, string email, string pwdHash, bool isAdmin);
    User() = default;
    void Create() override;
    vector<User> Select(string query, Bindings binds) override;
    void Update() override;
    void Delete() override;
};

class DAL_EXPORT Category : public IDataModel<Category>
{
public:
    inline const string getTable() const override { return "DCategory"; };
    int32_t id = DAL_BAD_ID;
    string name;
    bool isHidden;
    vector<class SubCategory> scats;

    Category(string name, bool isHidden);
    Category() = default;
    void Create() override;
    vector<Category> Select(string query, Bindings binds) override;
    void Update() override;
    void Delete() override;
};

class DAL_EXPORT SubCategory : public IDataModel<SubCategory>
{
public:
    inline const string getTable() const override { return "DSubCategory"; };
    int32_t id = DAL_BAD_ID;
    string name;
    bool isHidden;
    Category *cat;
    vector<class Team> teams;

    SubCategory(string name, bool isHidden, Category *cat);
    SubCategory() = default;
    void Create() override;
    vector<SubCategory> Select(string query, Bindings binds) override;
    void Update() override;
    void Delete() override;
};

class DAL_EXPORT Team : public IDataModel<Team>
{
public:
    inline const string getTable() const override { return "DTeam"; };
    int32_t id = DAL_BAD_ID;
    string name;
    bool isHidden;
    SubCategory *scat;
    string location;
    Poco::DateTime dateCreated;
    Poco::Nullable<Poco::Data::BLOB> icon;

    Team(string name, bool isHidden, SubCategory *scat, string location,
         Poco::DateTime dateCreated, Poco::Nullable<Poco::Data::BLOB> icon);
    Team() = default;
    void Create() override;
    vector<Team> Select(string query, Bindings binds) override;
    void Update() override;
    void Delete() override;
};

DAL_EXPORT Status Init(string host, string port, string username, string dbname, string password);

DAL_EXPORT Status InitEx(string host, string port, string username, string dbname, string password,
                         bool dropTables);

DAL_EXPORT void Quit();

}
#endif // DAL_H
