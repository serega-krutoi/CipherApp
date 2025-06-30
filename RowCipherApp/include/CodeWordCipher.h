#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include "ICipher.h"

using namespace std;

class CodeWordCipher : public ICipher {
private:
    vector<uint8_t> codeWordBytes;

    uint8_t encryptByte(uint8_t b) const;
    uint8_t decryptByte(uint8_t b) const;

public:
    CodeWordCipher(const vector<uint8_t>& codeWordBytes);

    vector<uint8_t> encrypt(const vector<uint8_t>& data) override;
    vector<uint8_t> decrypt(const vector<uint8_t>& data) override;

    static bool hasUniqueBytes(const vector<uint8_t>& bytes);
};