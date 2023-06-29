//
// Created by κ���� on 2023/5/17.
//
//#include <bits/stdc++.h>

#include "gtest/gtest.h"

#define TEST_SUDOKU




#include "Sudoku.h"




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



//��ӡ��������
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


//�����ж�һ��3X3�ľ������Ƿ����ظ�Ԫ�أ����һ��������Ҫ�ǲ�����checkMatrix̫�߳�
bool Sudoku::checkMatrixUtil(int row_start, int row_end, int col_start, int col_end) {
    set<int> record;//���ڼ�¼�Ѿ�������Щ����
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
// �ж�һ��3X3��С�������Ƿ����ظ�Ԫ��
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
// �ж�һ�����Ƿ����ظ�Ԫ��
bool Sudoku::checkCol(int c) {
    set<int> record;//���ڼ�¼�Ѿ�������Щ����
    for(int i=0;i<=8;i++){
        if(data[i][c]==0) continue;
        if(record.count(data[i][c])==1){
            return false;
        }
        record.insert(data[i][c]);
    }
    return true;
}

//�ж�һ�����Ƿ����ظ�Ԫ��
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
// ��������
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


// 在0-81范围内随机生成n个不同的数，以此决定对哪些位置挖空
bool Sudoku::gen_random_num(int n, vector<int>& res)
{
    srand((unsigned)time(NULL));
    const int total_num = 81;
    if(n >= total_num){
        cout<<"wrong input"<<endl;
        return false;
    }
    // 标记是否生成
    int book[total_num];
    std::memset(book,0,sizeof(book));
    // 表示已经生成多少个随机数
    int cnt = 0;
    while(cnt<n){
        // 随机生成0-80的一个数
        int rand_num =  rand() % total_num;
        // 如果没生成过这个数
        if(book[rand_num] == 0){
            book[rand_num] = 1;
            res.push_back(rand_num);
            cnt += 1;
        }
    }
    return true;
}


// 检查唯一解的条件(必要条件)
bool Sudoku::check_unique(int data[9][9]){
    //判断是否存在连续三行为空
    int continuous_row_empty_cnt = 0;
    for(int i=0;i<9;i++){
        bool cur_row_all_zero = true;
        for(int j=0;j<9;j++){
            if(data[i][j]!=0){
                continuous_row_empty_cnt=0;
                cur_row_all_zero = false;
                break;
            }
        }
        if(cur_row_all_zero){
            continuous_row_empty_cnt += 1;
        }
    }
    if(continuous_row_empty_cnt>=3)return false;

    //判断是否存在连续三列为空
    int continuous_col_empty_cnt = 0;
    for(int i=0;i<9;i++){
        bool cur_col_all_zero = true;
        for(int j=0;j<9;j++){
            if(data[j][i]!=0){
                continuous_col_empty_cnt=0;
                cur_col_all_zero = false;
                break;
            }
        }
        if(cur_col_all_zero){
            continuous_col_empty_cnt += 1;
        }
    }
    if(continuous_col_empty_cnt>=3)return false;

    //判断提示数字是否小于等于7个
    int has_num[9];
    std::memset(has_num,0,sizeof(has_num));
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(has_num[data[i][j]] == 0){
                has_num[data[i][j]] = 1;
            }
        }
    }
    int exist_num_cnt = 0;
    for(int i=0;i<9;i++){
        if(has_num[i] == 1){
            exist_num_cnt ++;
        }
    }
    if(exist_num_cnt <= 7)return false;

    return true;
}

// 对一个完整的数独进行随机挖空，挖空个数为n，is_unique代表是否要求唯一解
bool Sudoku::gen_Sudoku_with_n_empty(int n, bool is_unique){
    int known_num = 81 - n;
    if(is_unique && (known_num<17)){
        cout<<"wrong input, n too large!"<<endl;
        return false;
    }
    //循环，直到满足存在唯一解条件位置
    while(true){
        vector<int> rand_empty;
        if(!gen_random_num(n,rand_empty))return false;
        // 将数独的随机n个位置挖空，赋值为0
        for(int i=0; i<rand_empty.size(); i++){
            int row_idx = rand_empty[i] / 9;
            int col_idx = rand_empty[i] % 9;
            this->data[row_idx][col_idx] = 0;
        }
        // 如果不需要是唯一解，直接返回即可
        if(!is_unique)return true;
        // 如果要求唯一解，需要进行检查，直到满足为止
        else{
            if(check_unique(this->data))return true;
        }
    }

}

int Sudoku::sub(int a, int b) {
    return 0;
}

void Sudoku::solveSudoku() {
    Solution s;
    vector<vector<char>> complete_data = trans_data_2_char();
    s.solveSudoku(complete_data);
    fillData(complete_data);
}


#ifndef TEST_SUDOKU
int main(){
        Sudoku s;
    s.generateSudoku();
    s.printSudoku();
//    s.gen_Sudoku_with_n_empty(28, true);
//    s.printSudoku();

//    for(int i=0;i<argc;i++)
//        cout<<"Argument "<<i<<" is "<<argv[i]<<endl;
//    return 0;

//    const char *optstring = "c:s:n:m:r:u"; // 设置短参数类型及是否需要参数
//    int opt;

//    while ((opt = getopt(argc, argv, optstring)) != -1) {
//        printf("opt = %c\n", opt);  // 命令参数，亦即 -a -b -c -d
//        printf("optarg = %s\n", optarg); // 参数内容
//        printf("optind = %d\n", optind); // 下一个被处理的下标值
//        printf("argv[optind - 1] = %s\n\n",  argv[optind - 1]); // 参数内容
//    }

    // 循环读取命令行的参数和参数内容
//    while((opt = getopt(argc, argv, optstring)) != -1){
//        // 如果参数为-c 5，则生成5个终局
//        if(opt == 'c'){
//            int cur_arg = std::atoi(optarg);
//            for(int i=0;i<cur_arg;i++){
//                Sudoku s;
//                s.generateSudoku();
//                s.printSudoku();
//            }
//        }
//    }
}
#endif

#ifdef TEST_SUDOKU

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif