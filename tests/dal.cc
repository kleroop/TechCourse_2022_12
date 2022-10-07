#include <gtest/gtest.h>
#include <phash.h>
#include <DAL.h>
#include <utility>

DAL::User n1, n2;
char pwd[PHASH_SIZE];

TEST(DAL, UserCreate)
{
    n1 = DAL::User("admin", "admin@example.com", pwd, true);
    n2 = DAL::User("test1", "test1@example.com", pwd, false);
    n1.Create();
    n2.Create();
    ASSERT_EQ(n2.status, DAL::DAL_OK);
    ASSERT_EQ(n2.username, "test1");
}

TEST(DAL, UserUpdate)
{
    n2.username = "admin";
    n2.Update();
    ASSERT_TRUE(n2.status == DAL::DAL_OBJECT_EXISTS);
    n2.username = "test1_upd";
    n2.Update();
    ASSERT_TRUE(n2.status == DAL::DAL_OK);
}

TEST(DAL, UserSelect)
{
    n2.Select("username = $1", { DAL::bind("test1_upd") });
    ASSERT_TRUE(n2.status == DAL::DAL_OK);
    ASSERT_TRUE(n2.username == "test1_upd");
}

TEST(DAL, UserDelete)
{
    n2.Delete();
    ASSERT_TRUE(n2.status == DAL::DAL_OK);
    ASSERT_TRUE(n2.id == DAL_BAD_ID);
}

DAL::Category cat;
DAL::SubCategory scat;
DAL::Team team;

TEST(DAL, CategoryCreate)
{
    cat = DAL::Category("test1", false);
    scat = DAL::SubCategory("test2", false, &cat);
    team = DAL::Team("test3", false, &scat, "Dallas", Poco::DateTime(2022, 11, 11), {});
    cat.Create();
    scat.Create();
    team.Create();
    ASSERT_TRUE(cat.status == DAL::DAL_OK);
    ASSERT_TRUE(scat.status == DAL::DAL_OK);
    ASSERT_TRUE(team.status == DAL::DAL_OK);
    cat.Select("name = $1", { DAL::bind("test1") });
    team.Select("name = $1", { DAL::bind("test3") });
    ASSERT_TRUE(team.status == DAL::DAL_OK);
    ASSERT_EQ(team.name, "test3");
}
bool thidden;
TEST(DAL, CategoryUpdate)
{
    DAL::Team *tp = &cat.scats[0].teams[0];
    thidden = !tp->isHidden;
    tp->isHidden = thidden;
    cat.Update();
    ASSERT_TRUE(cat.status == DAL::DAL_OK);
}

TEST(DAL, CategorySelect)
{

    cat.Select("name = $1", { DAL::bind("test1") });
    ASSERT_EQ(cat.scats[0].teams.size(), 1);
    ASSERT_EQ(cat.scats[0].teams[0].isHidden, thidden);
}

TEST(DAL, CategoryDelete)
{
    cat.Delete();
    cat.Select("name = $1", { DAL::bind("test1") });
    ASSERT_TRUE(cat.status == DAL::DAL_NOT_FOUND);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    if (argc != 6) {
        printf("Can't connect to db, required command line options are: host port username dbname "
               "password. Number of args: %d\n",
               argc);
        return EXIT_FAILURE;
    }
    char *host = argv[1], *port = argv[2], *username = argv[3], *dbname = argv[4],
         *password = argv[5];
    if (DAL::InitEx(host, port, username, dbname, password, true) != DAL::DAL_OK) {
        puts("Couldn't init DAL connection");
        return EXIT_FAILURE;
    }

    utils_phash(pwd, "admin");

    int status = RUN_ALL_TESTS();

    DAL::Quit();
    return status;
}
