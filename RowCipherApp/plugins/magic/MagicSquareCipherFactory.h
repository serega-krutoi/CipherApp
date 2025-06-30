#pragma once
#include "../../include/ICipherFactory.h"
#include <string>
#include <vector>

using namespace std;

class MagicSquareCipherFactory : public ICipherFactory {
    int n;

public:
    void setParameter(const string& name, const string& value) override;
    ICipher* create() override;
};
