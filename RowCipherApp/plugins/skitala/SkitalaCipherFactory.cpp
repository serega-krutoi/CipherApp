#include "SkitalaCipherFactory.h"
#include "../../include/SkitalaCipher.h"

using namespace std;

void SkitalaCipherFactory::setParameter(const string& name, const string& value) {
    if (name == "rows") {
        rows = SkitalaCipher::getRows(value);
    }
}

ICipher* SkitalaCipherFactory::create() {
    return new SkitalaCipher(rows);
}

extern "C" ICipherFactory* createFactory() {
    return new SkitalaCipherFactory();
}
