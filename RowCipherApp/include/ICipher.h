#pragma once
#include <string>
#include <vector>
#include <cstdint>

using namespace std;

class ICipher {
public:
    virtual ~ICipher() = default;

    virtual vector<uint8_t> encrypt(const vector<uint8_t>& word) = 0;

    virtual vector<uint8_t> decrypt(const vector<uint8_t>& word) = 0;
};
