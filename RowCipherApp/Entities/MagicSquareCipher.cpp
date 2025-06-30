#include "../include/MagicSquareCipher.h"
#include <algorithm>

using namespace std;

MagicSquareCipher::MagicSquareCipher(const vector<vector<int>>& square)
    : square(square) {}

vector<uint8_t> MagicSquareCipher::encrypt(const vector<uint8_t>& data) {
    int n = square.size();
    vector<uint8_t> result;

    vector<pair<int, int>> positionMap(n * n + 1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            positionMap[square[i][j]] = {i, j};

    for (size_t blockStart = 0; blockStart < data.size(); blockStart += n * n) {
        vector<vector<uint8_t>> block(n, vector<uint8_t>(n, 0));

        size_t limit = min(data.size() - blockStart, static_cast<size_t>(n * n));
        for (size_t i = 0; i < limit; ++i) {
            int r = i / n;
            int c = i % n;
            block[r][c] = data[blockStart + i];
        }

        for (int num = 1; num <= n * n; ++num) {
            auto [i, j] = positionMap[num];
            result.push_back(block[i][j]);
        }
    }

    return result;
}

vector<uint8_t> MagicSquareCipher::decrypt(const vector<uint8_t>& data) {
    int n = square.size();
    vector<uint8_t> result;

    vector<pair<int, int>> positionMap(n * n + 1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            positionMap[square[i][j]] = {i, j};

    for (size_t blockStart = 0; blockStart < data.size(); blockStart += n * n) {
        vector<vector<uint8_t>> block(n, vector<uint8_t>(n, 0));

        size_t limit = min(data.size() - blockStart, static_cast<size_t>(n * n));
        for (size_t i = 0; i < limit; ++i) {
            auto [r, c] = positionMap[i + 1];
            block[r][c] = data[blockStart + i];
        }

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (block[i][j] != 0 || (blockStart + i * n + j) < data.size())
                    result.push_back(block[i][j]);
    }

    return result;
}
