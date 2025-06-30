#pragma once
#include "../../include/ICipherFactory.h"
#include <string>

using namespace std;

class CodeWordCipherFactory : public ICipherFactory {
    vector<uint8_t> codeword = {};

public:
    void setParameter(const string& name, const string& value) override;
    ICipher* create() override;
};
