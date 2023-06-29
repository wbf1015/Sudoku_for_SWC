//
// Created by HYX on 2023-06-29.
//

#ifndef SUDOKU_FOR_SWC_SUDOKU_H
#define SUDOKU_FOR_SWC_SUDOKU_H

#endif //SUDOKU_FOR_SWC_SUDOKU_H

#include<iostream>
#include <unistd.h>
#include "Solution.cpp"
#include <set>
#include <cstring>
using namespace std;
class Sudoku{
private:
    int data[9][9]={0};
public:
    bool generateSudoku();
    bool checkMatrix(char m);
    bool checkMatrixUtil(int row_start,int row_end,int col_start,int col_end);
    bool checkRow(int r);
    vector<vector<char>> trans_data_2_char();
    void fillData(vector<vector<char>> data_char);
    bool checkCol(int c);
    void printSudoku();
    bool gen_Sudoku_with_n_empty(int n, bool is_unique);

    int sub(int a, int b);

    int empty_cnt(){
        int cnt = 0;
        for(int i=0;i<9;i++){
            for (int j = 0; j < 9; ++j) {
                if(data[i][j] == 0)cnt++;
            }
        }
        return cnt;
    }
    int get_pos(int row,int col){
        return data[row][col];
    }
    void set_pos(int row,int col, int num){
        data[row][col] = num;
    }
    bool gen_random_num(int n, vector<int>& res);
    bool check_unique(int data[9][9]);

    int (*get_data())[9]{
        return data;
    }
};