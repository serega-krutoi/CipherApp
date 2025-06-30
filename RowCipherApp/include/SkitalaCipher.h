#pragma once
#include "ICipher.h"
#include <vector>
#include <cstdint>

using namespace std;

class SkitalaCipher : public ICipher {
private:
    int rows;

public:
    SkitalaCipher(int rows);
    vector<uint8_t> encrypt(const vector<uint8_t>& data) override;
    vector<uint8_t> decrypt(const vector<uint8_t>& data) override;
    static int getRows(const string& rows);
};
