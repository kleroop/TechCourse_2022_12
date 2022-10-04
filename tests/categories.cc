#include <gtest/gtest.h>
#include "api.h"
#include <QEventLoop>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <utility>

bool getRequest(std::string token) {
    int a0 = 0;
    QCoreApplication a((int &) a0, nullptr);
    auto *manager = new QNetworkAccessManager;
    QEventLoop loop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    Api api(manager);
    api.token = std::move(token);
    bool rtrn = false;

    api.getCategories([&rtrn](const CategoriesTreeResponse &resp) {
        for (auto &cat : resp.categoriesTree.categories){
            std::cout << cat.title << std::endl;
        }
        std::cout << resp.error;
        rtrn = resp.error.empty();
    });

    loop.exec();
    return rtrn;
}

TEST(GetCat, SuccessGet) {
    EXPECT_TRUE(getRequest("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6ImFkbWluQGV4YW1wbGUuY29tIiwiaWF0IjoxNjYxMzc"
                           "wNjcwLjExOCwic3ViIjoiYWRtaW4ifQ.E9AEDCWuVSrbPKS9CBeG0H4PD56tcqY4PhX5bMWnP4k"));
}

TEST(GetCat, UnauthorizedGet) {
    EXPECT_FALSE(getRequest("error"));
}