#pragma once
#include <vector>
#include "ICipher.h"

using namespace std;

vector<vector<int>> makeMagicSquare(const int& n);
vector<vector<int>> createOddMagicSquare(const int& n);
vector<vector<int>> createDoublyEvenMagicSquare(const int& n);
vector<vector<int>> createStracheyMagicSquare(const int& n);
int chooseMagicSquare(string& n);
int checkMagicSquare(const string& n);