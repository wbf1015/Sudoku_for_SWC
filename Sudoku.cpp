//
// Created by 魏伯繁 on 2023/5/17.
//
#include <bits/stdc++.h>
#include "Solution.cpp"
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
};

void Sudoku::fillData(vector<vector<char>> data_char) {
    for(int i=0;i<data_char.size();i++){
        for(int j=0;j<data_char[i].size();j++){
            data[i][j] = int(data_char[i][j]-int('0'));
        }
    }
}

vector<vector<char>> Sudoku::trans_data_2_char() {
    vector<vector<char>> data_char;
    for(int i=0;i<=8;i++){
        vector<char> row;
        for(int j=0;j<=8;j++){
            if(data[i][j]==0){
                row.push_back('.');
                continue;
            }else{
                row.push_back(char(data[i][j]+'0'));
            }
        }
        data_char.push_back(row);
    }
    return data_char;
}



//打印数独内容
void Sudoku::printSudoku() {
    cout << "+-------+-------+-------+" << endl;
    for (int i = 0; i < 9; i++) {
        cout << "| ";
        for (int j = 0; j < 9; j++) {
            cout << data[i][j] << " ";
            if ((j + 1) % 3 == 0)
                cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0)
            cout << "+-------+-------+-------+" << endl;
    }
}


//用于判断一个3X3的矩阵内是否有重复元素，提出一个函数主要是不想让checkMatrix太冗长
bool Sudoku::checkMatrixUtil(int row_start, int row_end, int col_start, int col_end) {
    set<int> record;//用于记录已经存了哪些数字
    for(int i=row_start;i<=row_end;i++){
        for(int j=col_start;j<=col_end;j++){
            if(data[i][j]==0){
                continue;
            }
            if(record.count(data[i][j])==1){
                return false;
            }
            record.insert(data[i][j]);
        }
    }
    return true;
}
// 判断一个3X3的小矩阵内是否有重复元素
bool Sudoku::checkMatrix(char m) {
    switch(m){
        case 'a':
            return checkMatrixUtil(0,2,0,2);
        case 'b':
            return checkMatrixUtil(0,2,3,5);
        case 'c':
            return checkMatrixUtil(0,2,6,8);
        case 'd':
            return checkMatrixUtil(3,5,0,2);
        case 'e':
            return checkMatrixUtil(3,5,3,5);
        case 'f':
            return checkMatrixUtil(3,5,6,8);
        case 'g':
            return checkMatrixUtil(6,8,0,2);
        case 'h':
            return checkMatrixUtil(6,8,3,5);
        case 'i':
            return checkMatrixUtil(6,8,6,8);
        default:
            throw "ERROR AT CHECKMATRIX";
    }
}
// 判断一列内是否有重复元素
bool Sudoku::checkCol(int c) {
    set<int> record;//用于记录已经存了哪些数字
    for(int i=0;i<=8;i++){
        if(data[i][c]==0) continue;
        if(record.count(data[i][c])==1){
            return false;
        }
        record.insert(data[i][c]);
    }
    return true;
}

//判断一行内是否有重复元素
bool Sudoku::checkRow(int r) {
    set<int> record;
    for(int i=0;i<=8;i++){
        if(data[r][i]==0) continue;
        if(record.count(data[r][i])==1){
            return false;
        }
        record.insert(data[r][i]);
    }
}
// 生成数组
bool Sudoku::generateSudoku() {
     srand((unsigned)time(NULL));
     int candidate[9] = {1,2,3,4,5,6,7,8,9};
     int matrix_a[9];
     std::copy(std::begin(candidate),std::end(candidate),std::begin(matrix_a));
     std::random_shuffle(matrix_a,matrix_a+9);
     int index=0;
     for(int i=0;i<=2;i++){
        for(int j=0;j<=2;j++){
            data[i][j] = matrix_a[index];
            index++;
        }
     }
     index=0;
     bool first_in = true;
     while(first_in|(!checkCol(3)|!checkCol(4)|!checkCol(5)|!checkCol(6)|!checkCol(7)|!checkCol(8)|!checkMatrix('b')|!checkMatrix('c'))){
        first_in = false;
        for(int i=0;i<=2;i++){
            int candidate_bc[6];
            int index_bc=0;
            for(int j=0;j<=2;j++){
                for(int k=0;k<=2;k++){
                    if(j==i){
                        continue;
                    }
                    candidate_bc[index_bc]=data[j][k];
                    index_bc++;
                }
            }
        std::random_shuffle(candidate_bc,candidate_bc+6);
            for(int j=3;j<=8;j++){
            data[i][j]=candidate_bc[j-3];
         }
        }
     }

     Solution s;
     vector<vector<char>> complete_data = trans_data_2_char();
     s.solveSudoku(complete_data);
    fillData(complete_data);
}


int main(){
    Sudoku s;
    s.generateSudoku();
    s.printSudoku();
}
