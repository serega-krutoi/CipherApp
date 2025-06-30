#pragma once
#include "../../include/ICipherFactory.h"
#include <string>

using namespace std;

class SkitalaCipherFactory : public ICipherFactory {
    int rows;

public:
    void setParameter(const string& name, const string& value) override;
    ICipher* create() override;
};
