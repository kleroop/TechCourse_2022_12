#include "DAL.h"
#include <phash.h>
#undef NDEBUG
#include <cassert>

int main()
{
    char pwd[PHASH_SIZE];
    utils_phash(pwd, "admin");
    if (DAL::InitEx(true) != DAL::DAL_OK) {
        puts("Couldn't init DAL connection");
        return EXIT_FAILURE;
    }

    DAL::User u;
    auto r = u.Select("id=$1 OR id=$2", { DAL::bind(1), DAL::bind(2) });
    DAL::User n1("admin", "admin@example.com", pwd, true),
            n2("test1", "test1@example.com", pwd, false);
    n1.Create();
    n2.Create();
    assert(n2.status == DAL::DAL_OK);
    n2.username = "admin";
    n2.Update();
    assert(n2.status = DAL::DAL_OBJECT_EXISTS);
    n2.username = "test1_upd";
    n2.Update();
    assert(n2.status == DAL::DAL_OK);
    n2.Select("username = $1", { DAL::bind("test1_upd") });
    assert(n2.status == DAL::DAL_OK);
    n2.Delete();
    assert(n2.status == DAL::DAL_OK);
    assert(n2.id == DAL_BAD_ID);

    /* Categories */
    DAL::Category cat("test1", false);
    DAL::SubCategory scat("test2", false, &cat);
    DAL::Team team("test3", false, &scat);
    cat.Create();
    scat.Create();
    team.Create();
    cat.Select("name = $1", { DAL::bind("test1") });
    cat.scats[0].isHidden = !cat.scats[0].isHidden;
    bool thidden = !cat.scats[0].teams[0].isHidden;
    assert(cat.scats[0].teams.size() == 1);
    printf("AAA: %d %d\n", thidden, cat.scats[0].teams[0].isHidden);

    cat.scats[0].teams[0].isHidden = thidden;
    cat.Update();
    printf("BBB: %d %d\n", thidden, cat.scats[0].teams[0].isHidden);

    cat.Select("name = $1", { DAL::bind("test1") });

    printf("CCC: %d %d\n", thidden, cat.scats[0].teams[0].isHidden);
    DAL::Quit();
}