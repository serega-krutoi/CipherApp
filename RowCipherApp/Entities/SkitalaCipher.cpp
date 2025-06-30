#include "../include/SkitalaCipher.h"
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

SkitalaCipher::SkitalaCipher(int rows) : rows(rows) {}

vector<uint8_t> SkitalaCipher::encrypt(const vector<uint8_t>& data) {
    int length = data.size();
    int cols = ceil(static_cast<double>(length) / rows);
    vector<vector<uint8_t>> matrix(rows, vector<uint8_t>(cols, 0));  // 0 как пустой байт

    int index = 0;
    for (int i = 0; i < rows && index < length; ++i) {
        for (int j = 0; j < cols && index < length; ++j) {
            matrix[i][j] = data[index++];
        }
    }

    vector<uint8_t> result;
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            result.push_back(matrix[i][j]);
        }
    }

    return result;
}

vector<uint8_t> SkitalaCipher::decrypt(const vector<uint8_t>& data) {
    int total = data.size();
    int cols = ceil(static_cast<double>(total) / rows);
    vector<vector<uint8_t>> matrix(rows, vector<uint8_t>(cols, 0));  // 0 как пустой байт

    int index = 0;
    for (int j = 0; j < cols && index < total; ++j) {
        for (int i = 0; i < rows && index < total; ++i) {
            matrix[i][j] = data[index++];
        }
    }

    vector<uint8_t> result;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i * cols + j < total) {
                result.push_back(matrix[i][j]);
            }
        }
    }

    return result;
}

int SkitalaCipher::getRows(const string& rows) {
    for (const auto& a : rows) {
        if (!isdigit(a)) throw runtime_error("Вы должны ввести число!");
    }
    return stoi(rows);
}
