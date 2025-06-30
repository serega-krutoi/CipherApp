#pragma once
#include "ICipher.h"
#include <vector>
#include <cstdint>

using namespace std;

class MagicSquareCipher : public ICipher {
private:
    vector<vector<int>> square;

public:
    MagicSquareCipher(const vector<vector<int>>& square);

    vector<uint8_t> encrypt(const vector<uint8_t>& data) override;
    vector<uint8_t> decrypt(const vector<uint8_t>& data) override;
};
