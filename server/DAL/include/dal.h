#ifndef DAL_H
#define DAL_H

#include <dal_export.h>
#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { DAL_OK, DAL_USER_EXISTS } DALStatus;

typedef struct
{
    int32_t id;
    // max length defined by the standard + nul terminator
    char username[32 + 1], email[320 + 1], pwd_hash[60 + 1];
    bool is_admin;
} DALUser;

DAL_EXPORT DALStatus DALInit();

DAL_EXPORT void DALQuit();

DAL_EXPORT DALStatus DALUserCreate(DALUser *out, char username[32 + 1], char email[320 + 1],
                                   char pwd_hash[60 + 1], bool is_admin);

DAL_EXPORT DALStatus DALUserGetById(DALUser *out, uint32_t id);

DAL_EXPORT DALStatus DALUserGetByUsername(DALUser *out, char username[32 + 1]);

DAL_EXPORT DALStatus DALUserEdit(DALUser *inout);

DAL_EXPORT DALStatus DALUserDelete(uint32_t id);

#ifdef __cplusplus
}
#endif

#endif // DAL_H
