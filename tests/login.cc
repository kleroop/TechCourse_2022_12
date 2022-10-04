#include <gtest/gtest.h>
#include "api.h"
#include <QEventLoop>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <utility>

bool loginRequest(std::string mail, std::string pass){
    int a0 = 0;
    QCoreApplication a((int &) a0, nullptr);
    auto *manager = new QNetworkAccessManager;
    QEventLoop loop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    Api api(manager);
    bool rtrn = false;

    api.login(std::move(mail), std::move(pass), [&rtrn](const AuthResponse &resp) {
        std::cout << resp.token << std::endl;
        std::cout << resp.error << std::endl;
        rtrn = resp.error.empty();
    });

    loop.exec();
    return rtrn;
}

TEST(LoginTest, SuccessfullLogin) {
    EXPECT_TRUE(loginRequest("admin@example.com", "admin"));
}

TEST(LoginTest, InvalidEmail) {
    EXPECT_FALSE(loginRequest("error", "admin"));
}

TEST(LoginTest, InvalidPassword) {
    EXPECT_FALSE(loginRequest("admin@example.com", "error"));
}