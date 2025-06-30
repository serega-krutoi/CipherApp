#include "MagicSquareCipherFactory.h"
#include "../../include/MagicSquareCipher.h"
#include "../../include/MagicSquareUtils.h"

using namespace std;

void MagicSquareCipherFactory::setParameter(const string& name, const string& value) {
    if (name == "n") {
        n = checkMagicSquare(value);
    }
}

ICipher* MagicSquareCipherFactory::create() {
    auto square = makeMagicSquare(n);
    return new MagicSquareCipher(square);
}

extern "C" ICipherFactory* createFactory() {
    return new MagicSquareCipherFactory();
}
