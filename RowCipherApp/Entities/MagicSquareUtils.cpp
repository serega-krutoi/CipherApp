#include <cctype>  
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>
#include "../include/MagicSquareUtils.h"

using namespace std;

vector<vector<int>> createOddMagicSquare(const int& n) {
    vector<vector<int>> square(n, vector<int>(n, 0));
    int i = 0, j = n / 2;

    for (int num = 1; num <= n * n; ++num) {
        square[i][j] = num;
        int next_i = (i - 1 + n) % n;
        int next_j = (j + 1) % n;

        if (square[next_i][next_j] != 0) {
            i = (i + 1) % n;
        } else {
            i = next_i;
            j = next_j;
        }
    }
    return square;
}

vector<vector<int>> createDoublyEvenMagicSquare(const int& n) {
    vector<vector<int>> square(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            square[i][j] = i * n + j + 1;

    for (int i = 0; i < n / 4; ++i) {
        for (int j = 0; j < n / 4; ++j) {
            swap(square[i][j], square[n - 1 - i][n - 1 - j]);
            swap(square[i][n - 1 - j], square[n - 1 - i][j]);
        }
    }
    return square;
}

vector<vector<int>> createStracheyMagicSquare(const int& n) {
    int m = n / 2;
    vector<vector<int>> A = createOddMagicSquare(m);
    vector<vector<int>> B(m, vector<int>(m));
    vector<vector<int>> C(m, vector<int>(m));
    vector<vector<int>> D(m, vector<int>(m));

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j) {
            B[i][j] = A[i][j] + 2 * m * m;
            C[i][j] = A[i][j] + 3 * m * m;
            D[i][j] = A[i][j] + m * m;
        }

    int swap_count = m / 2;
    for (int i = 0; i < swap_count; ++i) {
        swap(A[i][0], C[i][0]);
    }
    for (int i = 0; i < swap_count - 1; ++i) {
        swap(A[i][m / 2], C[i][m / 2]);
    }

    vector<vector<int>> result(n, vector<int>(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j) {
            result[i][j] = A[i][j];
            result[i][j + m] = B[i][j];
            result[i + m][j] = C[i][j];
            result[i + m][j + m] = D[i][j];
        }

    return result;
}

int checkMagicSquare(const string& n) {
    size_t x_pos = n.find('x');
    if (x_pos == string::npos || x_pos == 0 || x_pos == n.length() - 1) {
        throw runtime_error("Строка должна быть в формате NxN!");
    }

    string before_x = n.substr(0, x_pos);
    string after_x = n.substr(x_pos + 1);

    for (char c : before_x) {
        if (!isdigit(c)) throw runtime_error("Строка должна быть в формате NxN!");
    }
    for (char c : after_x) {
        if (!isdigit(c)) throw runtime_error("Строка должна быть в формате NxN!");
    }

    int n_before = stoi(before_x);
    int n_after = stoi(after_x);

    if (n_before != n_after) {
        throw runtime_error("Размеры должны быть одинаковыми, квадрат NxN!");
    }

    return n_before;
}

vector<vector<int>> makeMagicSquare(const int& n) {
    if (n % 2 == 1) return createOddMagicSquare(n);
    else if (n % 4 == 0) return createDoublyEvenMagicSquare(n);
    else return createStracheyMagicSquare(n);
}
