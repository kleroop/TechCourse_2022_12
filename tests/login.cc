#include <gtest/gtest.h>
#include "api.h"

TEST(LoginTest, SuccessfulLogin) {
    Api api;
    std::string mail = "admin@example.com";
    std::string pass = "admin";
    std::atomic_bool callback_called_flag{false};
    bool loginState = false;

    api.login(mail, pass, [&callback_called_flag, &loginState](const AuthResponse &resp) {
        if (!resp.error.empty()) {
            loginState = true;
        }else{
            perror(resp.error.c_str());
        }
        callback_called_flag = true;
    });

    int retry_count = 100;
    while (!callback_called_flag && retry_count-- > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_TRUE(loginState);
}