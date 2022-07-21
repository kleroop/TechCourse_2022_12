#include <DAL.h>
#include <phash.h>
#undef NDEBUG
#include <cassert>

int main()
{
    char pwd[PHASH_SIZE];
    if (DALInitEx(true) != DAL_OK) {
        puts("Couldn't init DAL connection");
        return EXIT_FAILURE;
    }
    DALUser u;

    utils_phash(pwd, "admin");

    switch (DALUserCreate(&u, "admin", "admin1@example.com", pwd, true)) {
    case DAL_OK:
    case DAL_USER_EXISTS:
        break;
    default:
        exit(1);
    }

    assert(DALUserGetByUsername(&u, "admin") == DAL_OK);
    assert(DALUserGetById(NULL, u.id) == DAL_OK);
    assert(DALUserGetByEmail(NULL, "admin1@example.com") == DAL_OK
           ^ DALUserGetByEmail(NULL, "admin@example.com") == DAL_OK);
    strcpy(u.email, "admin@example.com");
    assert(DALUserEdit(&u) == DAL_OK);
    u.id = 0;
    assert(DALUserEdit(&u) == DAL_NOT_FOUND);

    assert(DALUserDelete(0) == DAL_NOT_FOUND);

    DALQuit();
    puts(pwd);
    return EXIT_SUCCESS;
}