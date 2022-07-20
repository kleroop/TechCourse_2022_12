#include <openssl/evp.h>
#include <cstdio>

#include <phash.h>

int utils_phash(char out[PHASH_SIZE], const std::string &password)
{
    static const unsigned char salt[] = "super\0secret\0salt";
    const int iter = 4096;
    unsigned char result[16];
    int success = PKCS5_PBKDF2_HMAC(password.c_str(), (int)password.size(), salt, sizeof(salt) - 1,
                                    iter, EVP_sha1(), 16, result);

    if (success) {
        char *it = out;
        for (size_t i = 0; i < 16; i++) {
            sprintf(it, "%02X", result[i]);
            it += 2;
        }
    }
    // will output 56fa6aa75548099dcc37d7f03425e0c3
    return success;
}
