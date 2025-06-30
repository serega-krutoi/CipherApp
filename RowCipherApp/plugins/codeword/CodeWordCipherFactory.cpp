#include "CodeWordCipherFactory.h"
#include "../../include/CodeWordCipher.h"
#include <sstream>
#include <stdexcept>

using namespace std;

static vector<uint8_t> parseBytes(const string& s) {
    vector<uint8_t> bytes;
    istringstream iss(s);
    string token;

    while (iss >> token) {
        for (char a : token) {
            if (!isdigit(a)) throw invalid_argument("В строке должны быть только числа!");
        }
        int val = stoi(token);
        if (val < 0 || val > 255) {
            throw invalid_argument("Значение байта вне диапазона 0-255: " + token);
        }
        bytes.push_back(static_cast<uint8_t>(val));
    }

    return bytes;
}

void CodeWordCipherFactory::setParameter(const string& name, const string& value) {
    if (name == "codeword") {
        codeword = parseBytes(value);
    }
}

ICipher* CodeWordCipherFactory::create() {
    return new CodeWordCipher(codeword);
}

extern "C" ICipherFactory* createFactory() {
    return new CodeWordCipherFactory();
}