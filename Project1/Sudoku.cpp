#include<iostream>
#include<set>
#include<algorithm>
#include<fstream>
#include<sstream>
#include <stdio.h>
#include <windows.h>
#include<iomanip>
#include"getopt.h"
#include "Solution.cpp"
using namespace std;
// 数独类，用这个类来模拟一个数独游戏
class Sudoku {
private:
    int data[9][9] = { 0 };
public:
    bool generateSudoku();
    bool checkMatrix(char m);
    bool checkMatrixUtil(int row_start, int row_end, int col_start, int col_end);
    bool checkRow(int r);
    vector<vector<char>> trans_data_2_char();
    void fillData(vector<vector<char>> data_char);
    bool checkCol(int c);
    void printSudoku();
    bool gen_Sudoku_with_n_empty(int n, bool is_unique);
    void clearData();
    void Solvesudoku();
    void insertData(int row,int col,int data);
    void print2txt();
};

// 传入一个9*9二维字符向量，将它解析为一个数独
void Sudoku::fillData(vector<vector<char>> data_char) {
    for (unsigned int i = 0; i < data_char.size(); i++) {
        for (unsigned int j = 0; j < data_char[i].size(); j++) {
            data[i][j] = int(data_char[i][j] - int('0'));
        }
    }
}

// 将数独类自己保存的数据转换为一个二维字符向量
vector<vector<char>> Sudoku::trans_data_2_char() {
    vector<vector<char>> data_char;
    for (int i = 0; i <= 8; i++) {
        vector<char> row;
        for (int j = 0; j <= 8; j++) {
            if (data[i][j] == 0) {
                row.push_back('.');
                continue;
            }
            else {
                row.push_back(char(data[i][j] + '0'));
            }
        }
        data_char.push_back(row);
    }
    return data_char;
}


// 打印数独
void Sudoku::printSudoku() {
    cout << "+-------+-------+-------+" << endl;
    for (int i = 0; i < 9; i++) {
        cout << "| ";
        for (int j = 0; j < 9; j++) {
            // 如果是待填写字符的话用X代替
            if (data[i][j] == 0) {
                cout << " " << " ";
            }
            else {
                cout << data[i][j] << " ";
            }
            if ((j + 1) % 3 == 0)
                cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0)
            cout << "+-------+-------+-------+" << endl;
    }
}

// 检查一个3*3的小单元格是否正确
bool Sudoku::checkMatrixUtil(int row_start, int row_end, int col_start, int col_end) {
    set<int> record;
    for (int i = row_start; i <= row_end; i++) {
        for (int j = col_start; j <= col_end; j++) {
            if (data[i][j] == 0) {
                continue;
            }
            if (record.count(data[i][j]) == 1) {
                return false;
            }
            record.insert(data[i][j]);
        }
    }
    return true;
}

//检查数独中所有的3*3的小单元格是否正确
bool Sudoku::checkMatrix(char m) {
    switch (m) {
    case 'a':
        return checkMatrixUtil(0, 2, 0, 2);
    case 'b':
        return checkMatrixUtil(0, 2, 3, 5);
    case 'c':
        return checkMatrixUtil(0, 2, 6, 8);
    case 'd':
        return checkMatrixUtil(3, 5, 0, 2);
    case 'e':
        return checkMatrixUtil(3, 5, 3, 5);
    case 'f':
        return checkMatrixUtil(3, 5, 6, 8);
    case 'g':
        return checkMatrixUtil(6, 8, 0, 2);
    case 'h':
        return checkMatrixUtil(6, 8, 3, 5);
    case 'i':
        return checkMatrixUtil(6, 8, 6, 8);
    default:
        throw "ERROR AT CHECKMATRIX";
    }
}

//检查某一行是否正确
bool Sudoku::checkCol(int c) {
    set<int> record;
    for (int i = 0; i <= 8; i++) {
        if (data[i][c] == 0) continue;
        if (record.count(data[i][c]) == 1) {
            return false;
        }
        record.insert(data[i][c]);
    }
    return true;
}

//检查某一列是否正确
bool Sudoku::checkRow(int r) {
    set<int> record;
    for (int i = 0; i <= 8; i++) {
        if (data[r][i] == 0) continue;
        if (record.count(data[r][i]) == 1) {
            return false;
        }
        record.insert(data[r][i]);
    }
    return true;
}

//生成一个数独
bool Sudoku::generateSudoku() {
    srand((unsigned)time(NULL));
    int candidate[9] = { 1,2,3,4,5,6,7,8,9 };
    int matrix_a[9];
    std::copy(std::begin(candidate), std::end(candidate), std::begin(matrix_a));
    std::random_shuffle(matrix_a, matrix_a + 9);
    int index = 0;
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            data[i][j] = matrix_a[index];
            index++;
        }
    }
    index = 0;
    bool first_in = true;
    while (first_in | (!checkCol(3) | !checkCol(4) | !checkCol(5) | !checkCol(6) | !checkCol(7) | !checkCol(8) | !checkMatrix('b') | !checkMatrix('c'))) {
        first_in = false;
        for (int i = 0; i <= 2; i++) {
            int candidate_bc[6];
            int index_bc = 0;
            for (int j = 0; j <= 2; j++) {
                for (int k = 0; k <= 2; k++) {
                    if (j == i) {
                        continue;
                    }
                    candidate_bc[index_bc] = data[j][k];
                    index_bc++;
                }
            }
            std::random_shuffle(candidate_bc, candidate_bc + 6);
            for (int j = 3; j <= 8; j++) {
                data[i][j] = candidate_bc[j - 3];
            }
        }
    }

    Solution s;
    vector<vector<char>> complete_data = trans_data_2_char();
    s.solveSudoku(complete_data);
    fillData(complete_data);
    return true;
}


// 在0-81范围内随机生成n个不同的数，以此决定对哪些位置挖空
bool gen_random_num(int n, vector<int>& res)
{
    srand((unsigned)time(NULL));
    const int total_num = 81;
    if (n >= total_num) {
        cout << "wrong input" << endl;
        return false;
    }
    // 标记是否生成
    int book[total_num];
    std::memset(book, 0, sizeof(book));
    // 表示已经生成多少个随机数
    int cnt = 0;
    while (cnt < n) {
        // 随机生成0-80的一个数
        int rand_num = rand() % total_num;
        // 如果没生成过这个数
        if (book[rand_num] == 0) {
            book[rand_num] = 1;
            res.push_back(rand_num);
            cnt += 1;
        }
    }
    return true;
}


// 检查唯一解的条件(必要条件)
bool check_unique(int data[9][9]) {
    //判断是否存在连续三行为空
    int continuous_row_empty_cnt = 0;
    for (int i = 0; i < 9; i++) {
        bool cur_row_all_zero = true;
        for (int j = 0; j < 9; j++) {
            if (data[i][j] != 0) {
                continuous_row_empty_cnt = 0;
                cur_row_all_zero = false;
                break;
            }
        }
        if (cur_row_all_zero) {
            continuous_row_empty_cnt += 1;
        }
    }
    if (continuous_row_empty_cnt >= 3)return false;

    //判断是否存在连续三列为空
    int continuous_col_empty_cnt = 0;
    for (int i = 0; i < 9; i++) {
        bool cur_col_all_zero = true;
        for (int j = 0; j < 9; j++) {
            if (data[j][i] != 0) {
                continuous_col_empty_cnt = 0;
                cur_col_all_zero = false;
                break;
            }
        }
        if (cur_col_all_zero) {
            continuous_col_empty_cnt += 1;
        }
    }
    if (continuous_col_empty_cnt >= 3)return false;

    //判断提示数字是否小于等于7个
    int has_num[9];
    std::memset(has_num, 0, sizeof(has_num));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (has_num[data[i][j]] == 0) {
                has_num[data[i][j]] = 1;
            }
        }
    }
    int exist_num_cnt = 0;
    for (int i = 0; i < 9; i++) {
        if (has_num[i] == 1) {
            exist_num_cnt++;
        }
    }
    if (exist_num_cnt <= 7)return false;

    return true;
}

// 对一个完整的数独进行随机挖空，挖空个数为n，is_unique代表是否要求唯一解
// 调用此函数前需保证数独类中已经生成了完整的数独数据
bool Sudoku::gen_Sudoku_with_n_empty(int n, bool is_unique) {
    int known_num = 81 - n;
    if (is_unique && (known_num < 17)) {
        cout << "wrong input, n too large!" << endl;
        return false;
    }
    //循环，直到满足存在唯一解条件位置
    while (true) {
        vector<int> rand_empty;
        if (!gen_random_num(n, rand_empty))return false;
        // 将数独的随机n个位置挖空，赋值为0
        for (unsigned int i = 0; i < rand_empty.size(); i++) {
            int row_idx = rand_empty[i] / 9;
            int col_idx = rand_empty[i] % 9;
            this->data[row_idx][col_idx] = 0;
        }
        // 如果不需要是唯一解，直接返回即可
        if (!is_unique)return true;
        // 如果要求唯一解，需要进行检查，直到满足为止
        else {
            if (check_unique(this->data))return true;
        }
    }
}

// 将自己保存的数独数据清空
void Sudoku::clearData() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            this->data[i][j] = 0;
        }
    }
}

//求解数独
void Sudoku::Solvesudoku() {
    Solution s;
    vector<vector<char>> complete_data = trans_data_2_char();
    s.solveSudoku(complete_data);
    fillData(complete_data);
}

//向指定位置插入值
void Sudoku::insertData(int row,int col,int data) {
    if ((row < 0) | (row>8) | (col < 0) | (col>8) | (data < 0) | (data>9)) {
        cout << "向数独指定位置插入数值失败"<<endl;
        return;
    }
    this->data[row][col] = data;
    return;
}

void Sudoku::print2txt() {
    string filename = "sudoku.txt";
    std::ofstream ofs(filename, std::ios::app);
    if (!ofs) {
        cout << "无法打开文件：" << filename << std::endl;
        return;
    }

    // 获取本地时间并格式化为字符串
    SYSTEMTIME st;
    GetLocalTime(&st);
    std::ostringstream oss;
    oss << st.wYear << "-" << std::setw(2) << std::setfill('0') << st.wMonth << "-" << std::setw(2) << std::setfill('0') << st.wDay << " "
        << std::setw(2) << std::setfill('0') << st.wHour << ":" << std::setw(2) << std::setfill('0') << st.wMinute << ":" << std::setw(2) << std::setfill('0') << st.wSecond << " ";
    oss << "the " << st.wDayOfWeek << " day of a week.\n";

    // 将字符串写入文件
    ofs << oss.str();

    ofs << "+-------+-------+-------+\n";
    for (int i = 0; i < 9; i++) {
        ofs << "| ";
        for (int j = 0; j < 9; j++) {
            // 如果是待填写字符的话用X代替
            if (data[i][j] == 0) {
                ofs << " " << " ";
            }
            else {
                ofs << data[i][j] << " ";
            }
            if ((j + 1) % 3 == 0)
                ofs << "| ";
        }
        ofs << "\n";
        if ((i + 1) % 3 == 0)
            ofs << "+-------+-------+-------+\n";
    }

    ofs.close();
}

// 从txt中读取若干个数独并给出解答，将解答生成到sudoku.txt中
void solve_txt_sudoku(string path) {
    // 这里给出的逻辑是：如果接收到字符X、0、.则认为接收到一个待填充的位置
    // 如果接收到1-9的任意一个字符则认为接收到一个待填充的位置
    ifstream infile(path, ios::in);
    if (!infile) {//文件没打开
        cout<<("无法找到这个文件");
    }
    int index_row = 0;
    int index_col = 0;
    int count = 0;
    string s;
    Sudoku su;
    while (infile >> s) {
        for (unsigned int i = 0; i < s.size(); i++) {
            if ((s[i] == 'X') | (s[i] == 'x') | (s[i] == '0') | (s[i] == '.')) {
                su.insertData(index_row, index_col++, 0);
                if (index_col == 9) {
                    index_row += 1;
                    index_col = 0;
                    if (index_row == 9) {
                        su.Solvesudoku();
                        su.print2txt();
                        cout << "======成功求解第" << count++ << "个数独======" << endl;
                        su.printSudoku();
                        su.clearData();
                        index_row = 0; index_col = 0;
                    }
                }
                continue;
            }
            if (s[i] >= '1' && s[i] <= '9') {
                su.insertData(index_row, index_col++, s[i]-'0');
                if (index_col == 9) {
                    index_row += 1;
                    index_col = 0;
                    if (index_row == 9) {
                        su.Solvesudoku();
                        su.print2txt();
                        cout << "======成功求解第" << count++ << "个数独======" << endl;
                        su.printSudoku();
                        su.clearData();
                        index_row = 0; index_col = 0;
                    }
                }
                continue;
            }
        }
    }
    infile.close();
}
void extractNumbers(const std::string& str, int& num1, int& num2) {
    std::stringstream ss(str); // 将字符串作为输入流
    char dash; // 用于接收中间的破折号
    ss >> num1 >> dash >> num2; // 提取两个整数
}

int main(int argc, char* argv[]) {
    const char* optstring = "c:s:n:m:r:u"; // 设置短参数类型及是否需要参数
    int opt;
    bool found_n = false;//判断是否找到参数n
    int para_n;
    bool extra_para = false;
    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
        case 'c': {
            int cur_arg = std::atoi(optarg);
            for (int i = 0; i < cur_arg; i++) {
                Sudoku s;
                s.generateSudoku();
                cout << "======成功生成第" << i+1 << "个数独======" << endl;
                s.printSudoku();
                cout << endl;
                Sleep(1000);
            }
            break;
        }
        case 's': {
            string s_path = std::string(optarg);
            solve_txt_sudoku(s_path);
            //cout << "here" << endl;
            break;
        }
        case 'n': {
            found_n = true;
            para_n = std::atoi(optarg);
            break;
        }
        case 'm': {
            // 如果没有找到-n参数则输出错误信息
            if (!found_n) {
                cout << "错误：参数-m必须和-n一起使用" << std::endl;
                return -1;
            }
            extra_para = true;
            int m_arg = std::atoi(optarg);
            cout << m_arg << endl;
            switch (m_arg)
            {
            case 1: {
                //生成简单的数独游戏
                for (int i = 0; i < para_n; i++) {
                    Sudoku s;
                    s.generateSudoku();
                    s.gen_Sudoku_with_n_empty(10, false);
                    cout << "======成功生成第" << i+1 << "个简单难度数独======" << endl;
                    s.printSudoku();
                    Sleep(1000);
                }
                break;
            }
            case 2: {
                //生成普通的数独游戏
                for (int i = 0; i < para_n; i++) {
                    Sudoku s;
                    s.generateSudoku();
                    s.gen_Sudoku_with_n_empty(20, false);
                    cout << "======成功生成第" << i+1 << "个普通难度数独======" << endl;
                    s.printSudoku();
                    Sleep(1000);
                }
                break;
            }
            case 3: {
                //生成困难的数独游戏
                for (int i = 0; i < para_n; i++) {
                    Sudoku s;
                    s.generateSudoku();
                    s.gen_Sudoku_with_n_empty(40, false);
                    cout << "======成功生成第" << i + 1 << "个困难难度数独======" << endl;
                    s.printSudoku();
                    Sleep(1000);
                }
                break;
            }
            default:
                cout << "非法的难度指定参数" << endl;
            }
            // 任务4代码
            break;
        }
        case 'r': {
            // 如果没有找到-n参数则输出错误信息
            if (!found_n) {
                std::cerr << "错误：参数-r必须和-n一起使用" << std::endl;
                return 1;
            }
            extra_para = true;
            // 获取参数-r的值
            string r_arg = std::string(optarg);
            int l_limit, h_limit;
            extractNumbers(r_arg, l_limit, h_limit);
            for (int i = 0; i < para_n; i++) {
                Sudoku s;
                s.generateSudoku();
                int emptyNum = rand() % (h_limit - l_limit + 1) + l_limit;
                cout << "======成功生成第" << i + 1 << "个数独，挖空数为"<<emptyNum<<"======" << endl;
                s.gen_Sudoku_with_n_empty(emptyNum, false);
                s.printSudoku();
                Sleep(1000);
            }
            break;
        }
        case 'u': {
            // 如果没有找到-n参数则输出错误信息
            if (!found_n) {
                std::cerr << "错误：参数-u必须和-n一起使用" << std::endl;
                return 1;
            }
            extra_para = true;
            // 任务6代码
            for (int i = 0; i < para_n; i++) {
                Sudoku s;
                s.generateSudoku();
                s.gen_Sudoku_with_n_empty(20, true);
                cout << "======成功生成第" << i + 1 << "个具有唯一解的数独======" << endl;
                s.printSudoku();
                Sleep(1000);
            }
            break;
        }
        default:
            // 处理未知选项
            std::cerr << "错误：未知选项" << std::endl;
            return 1;
        }
    }
    if (found_n & !extra_para) {
        for (int i = 0; i < para_n; i++) {
            Sudoku s;
            s.generateSudoku();
            s.gen_Sudoku_with_n_empty(20, false);
            cout << "======成功生成第" << i + 1 << "个数独======" << endl;
            s.printSudoku();
            Sleep(1000);
        }
    }

    string input;
    while (true) {
        cout << "请输入指令(exit退出程序)：";
        cin >> input;
        if (input == "exit") {
            break;
        }
        // TODO: 执行其他指令
    }
    return 0;
}


