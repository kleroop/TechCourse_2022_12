#ifndef PHASH_H
#define PHASH_H

#include <string>

#define PHASH_SIZE 32 + 1

int utils_phash(char out[PHASH_SIZE], const std::string& password);

#endif // PHASH_H
