#include "../include/CodeWordCipher.h"
#include <stdexcept>
#include <algorithm>

using namespace std;

CodeWordCipher::CodeWordCipher(const vector<uint8_t>& codeWordBytes)
    : codeWordBytes(codeWordBytes)
{
    if (codeWordBytes.empty()) {
        throw runtime_error("Кодовое слово не может быть пустым");
    }
    if (!hasUniqueBytes(codeWordBytes)) {
        throw runtime_error("Кодовое слово не должно содержать повторяющихся байтов");
    }
}

bool CodeWordCipher::hasUniqueBytes(const vector<uint8_t>& bytes) {
    vector<uint8_t> tmp = bytes;
    sort(tmp.begin(), tmp.end());
    return adjacent_find(tmp.begin(), tmp.end()) == tmp.end();
}

uint8_t CodeWordCipher::encryptByte(uint8_t b) const {
    for (size_t i = 0; i < codeWordBytes.size(); ++i) {
        if (codeWordBytes[i] == b) {
            return static_cast<uint8_t>(i);
        }
    }

    size_t pos = 0;
    for (uint16_t val = 0; val <= 255; ++val) {
        uint8_t val8 = static_cast<uint8_t>(val);
        if (find(codeWordBytes.begin(), codeWordBytes.end(), val8) != codeWordBytes.end()) {
            continue;
        }
        if (val8 == b) {
            return static_cast<uint8_t>(codeWordBytes.size() + pos);
        }
        pos++;
    }

    throw runtime_error("Не удалось зашифровать байт");
}

uint8_t CodeWordCipher::decryptByte(uint8_t b) const {
    if (b < codeWordBytes.size()) {
        return codeWordBytes[b];
    }

    size_t targetPos = b - codeWordBytes.size();
    size_t pos = 0;
    for (uint16_t val = 0; val <= 255; ++val) {
        uint8_t val8 = static_cast<uint8_t>(val);
        if (find(codeWordBytes.begin(), codeWordBytes.end(), val8) != codeWordBytes.end()) {
            continue;
        }
        if (pos == targetPos) {
            return val8;
        }
        pos++;
    }

    throw runtime_error("Не удалось расшифровать байт");
}

vector<uint8_t> CodeWordCipher::encrypt(const vector<uint8_t>& data) {
    vector<uint8_t> result;
    result.reserve(data.size());
    for (uint8_t b : data) {
        result.push_back(encryptByte(b));
    }
    return result;
}

vector<uint8_t> CodeWordCipher::decrypt(const vector<uint8_t>& data) {
    vector<uint8_t> result;
    result.reserve(data.size());
    for (uint8_t b : data) {
        result.push_back(decryptByte(b));
    }
    return result;
}