#ifndef DAL_H
#define DAL_H

#include <dal_export.h>
#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { DAL_OK, DAL_ERROR, DAL_CONNECTION_FAILED, DAL_USER_EXISTS, DAL_NOT_FOUND } DALStatus;

typedef struct
{
    int32_t id;
    // max length defined by the standard + nul terminator
    char username[32 + 1], email[320 + 1], pwdHash[32 + 1];
    bool isAdmin;
} DALUser;

DAL_EXPORT DALStatus DALInit();

DAL_EXPORT DALStatus DALInitEx(bool dropTables);

DAL_EXPORT void DALQuit();

DAL_EXPORT DALStatus DALUserCreate(DALUser *out, const char username[32 + 1],
                                   const char email[320 + 1], const char pwdHash[32 + 1],
                                   bool isAdmin);

DAL_EXPORT DALStatus DALUserGetById(DALUser *out, uint32_t id);

DAL_EXPORT DALStatus DALUserGetByUsername(DALUser *out, const char username[32 + 1]);

DAL_EXPORT DALStatus DALUserGetByEmail(DALUser *out, const char email[320 + 1]);

DAL_EXPORT DALStatus DALUserEdit(const DALUser *in);

DAL_EXPORT DALStatus DALUserDelete(uint32_t id);

#ifdef __cplusplus
}
#endif

#endif // DAL_H
