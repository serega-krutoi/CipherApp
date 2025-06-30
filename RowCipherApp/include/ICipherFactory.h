#pragma once
#include <string>
#include "ICipher.h"

using namespace std;

class ICipherFactory {
public:
    virtual ~ICipherFactory() = default;
    virtual void setParameter(const string& name, const string& value) = 0;
    virtual ICipher* create() = 0;
};
