//
// Created by HYX on 2023-06-29.
//

#ifndef CLIONTEST_SOLUTION_H
#define CLIONTEST_SOLUTION_H

#endif //CLIONTEST_SOLUTION_H
#include<vector>
#include<bitset>
using namespace std;
class Solution {
public:
    bitset<9> getPossibleStatus(int x, int y);

    vector<int> getNext(vector<vector<char>>& board);

    void fillNum(int x, int y, int n, bool fillFlag);

    bool dfs(vector<vector<char>>& board, int cnt);

    void solveSudoku(vector<vector<char>>& board);

private:
    vector<bitset<9>> rows;
    vector<bitset<9>> cols;
    vector<vector<bitset<9>>> cells;
};