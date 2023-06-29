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
// �����࣬���������ģ��һ��������Ϸ
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

// ����һ��9*9��ά�ַ���������������Ϊһ������
void Sudoku::fillData(vector<vector<char>> data_char) {
    for (unsigned int i = 0; i < data_char.size(); i++) {
        for (unsigned int j = 0; j < data_char[i].size(); j++) {
            data[i][j] = int(data_char[i][j] - int('0'));
        }
    }
}

// ���������Լ����������ת��Ϊһ����ά�ַ�����
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


// ��ӡ����
void Sudoku::printSudoku() {
    cout << "+-------+-------+-------+" << endl;
    for (int i = 0; i < 9; i++) {
        cout << "| ";
        for (int j = 0; j < 9; j++) {
            // ����Ǵ���д�ַ��Ļ���X����
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

// ���һ��3*3��С��Ԫ���Ƿ���ȷ
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

//������������е�3*3��С��Ԫ���Ƿ���ȷ
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

//���ĳһ���Ƿ���ȷ
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

//���ĳһ���Ƿ���ȷ
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

//����һ������
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


// ��0-81��Χ���������n����ͬ�������Դ˾�������Щλ���ڿ�
bool gen_random_num(int n, vector<int>& res)
{
    srand((unsigned)time(NULL));
    const int total_num = 81;
    if (n >= total_num) {
        cout << "wrong input" << endl;
        return false;
    }
    // ����Ƿ�����
    int book[total_num];
    std::memset(book, 0, sizeof(book));
    // ��ʾ�Ѿ����ɶ��ٸ������
    int cnt = 0;
    while (cnt < n) {
        // �������0-80��һ����
        int rand_num = rand() % total_num;
        // ���û���ɹ������
        if (book[rand_num] == 0) {
            book[rand_num] = 1;
            res.push_back(rand_num);
            cnt += 1;
        }
    }
    return true;
}


// ���Ψһ�������(��Ҫ����)
bool check_unique(int data[9][9]) {
    //�ж��Ƿ������������Ϊ��
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

    //�ж��Ƿ������������Ϊ��
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

    //�ж���ʾ�����Ƿ�С�ڵ���7��
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

// ��һ��������������������ڿգ��ڿո���Ϊn��is_unique�����Ƿ�Ҫ��Ψһ��
// ���ô˺���ǰ�豣֤���������Ѿ���������������������
bool Sudoku::gen_Sudoku_with_n_empty(int n, bool is_unique) {
    int known_num = 81 - n;
    if (is_unique && (known_num < 17)) {
        cout << "wrong input, n too large!" << endl;
        return false;
    }
    //ѭ����ֱ���������Ψһ������λ��
    while (true) {
        vector<int> rand_empty;
        if (!gen_random_num(n, rand_empty))return false;
        // �����������n��λ���ڿգ���ֵΪ0
        for (unsigned int i = 0; i < rand_empty.size(); i++) {
            int row_idx = rand_empty[i] / 9;
            int col_idx = rand_empty[i] % 9;
            this->data[row_idx][col_idx] = 0;
        }
        // �������Ҫ��Ψһ�⣬ֱ�ӷ��ؼ���
        if (!is_unique)return true;
        // ���Ҫ��Ψһ�⣬��Ҫ���м�飬ֱ������Ϊֹ
        else {
            if (check_unique(this->data))return true;
        }
    }
}

// ���Լ�����������������
void Sudoku::clearData() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            this->data[i][j] = 0;
        }
    }
}

//�������
void Sudoku::Solvesudoku() {
    Solution s;
    vector<vector<char>> complete_data = trans_data_2_char();
    s.solveSudoku(complete_data);
    fillData(complete_data);
}

//��ָ��λ�ò���ֵ
void Sudoku::insertData(int row,int col,int data) {
    if ((row < 0) | (row>8) | (col < 0) | (col>8) | (data < 0) | (data>9)) {
        cout << "������ָ��λ�ò�����ֵʧ��"<<endl;
        return;
    }
    this->data[row][col] = data;
    return;
}

void Sudoku::print2txt() {
    string filename = "sudoku.txt";
    std::ofstream ofs(filename, std::ios::app);
    if (!ofs) {
        cout << "�޷����ļ���" << filename << std::endl;
        return;
    }

    // ��ȡ����ʱ�䲢��ʽ��Ϊ�ַ���
    SYSTEMTIME st;
    GetLocalTime(&st);
    std::ostringstream oss;
    oss << st.wYear << "-" << std::setw(2) << std::setfill('0') << st.wMonth << "-" << std::setw(2) << std::setfill('0') << st.wDay << " "
        << std::setw(2) << std::setfill('0') << st.wHour << ":" << std::setw(2) << std::setfill('0') << st.wMinute << ":" << std::setw(2) << std::setfill('0') << st.wSecond << " ";
    oss << "the " << st.wDayOfWeek << " day of a week.\n";

    // ���ַ���д���ļ�
    ofs << oss.str();

    ofs << "+-------+-------+-------+\n";
    for (int i = 0; i < 9; i++) {
        ofs << "| ";
        for (int j = 0; j < 9; j++) {
            // ����Ǵ���д�ַ��Ļ���X����
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

// ��txt�ж�ȡ���ɸ�������������𣬽�������ɵ�sudoku.txt��
void solve_txt_sudoku(string path) {
    // ����������߼��ǣ�������յ��ַ�X��0��.����Ϊ���յ�һ��������λ��
    // ������յ�1-9������һ���ַ�����Ϊ���յ�һ��������λ��
    ifstream infile(path, ios::in);
    if (!infile) {//�ļ�û��
        cout<<("�޷��ҵ�����ļ�");
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
                        cout << "======�ɹ�����" << count++ << "������======" << endl;
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
                        cout << "======�ɹ�����" << count++ << "������======" << endl;
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
    std::stringstream ss(str); // ���ַ�����Ϊ������
    char dash; // ���ڽ����м�����ۺ�
    ss >> num1 >> dash >> num2; // ��ȡ��������
}

int main(int argc, char* argv[]) {
    const char* optstring = "c:s:n:m:r:u"; // ���ö̲������ͼ��Ƿ���Ҫ����
    int opt;
    bool found_n = false;//�ж��Ƿ��ҵ�����n
    int para_n;
    bool extra_para = false;
    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
        case 'c': {
            int cur_arg = std::atoi(optarg);
            for (int i = 0; i < cur_arg; i++) {
                Sudoku s;
                s.generateSudoku();
                cout << "======�ɹ����ɵ�" << i+1 << "������======" << endl;
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
            // ���û���ҵ�-n���������������Ϣ
            if (!found_n) {
                cout << "���󣺲���-m�����-nһ��ʹ��" << std::endl;
                return -1;
            }
            extra_para = true;
            int m_arg = std::atoi(optarg);
            cout << m_arg << endl;
            switch (m_arg)
            {
            case 1: {
                //���ɼ򵥵�������Ϸ
                for (int i = 0; i < para_n; i++) {
                    Sudoku s;
                    s.generateSudoku();
                    s.gen_Sudoku_with_n_empty(10, false);
                    cout << "======�ɹ����ɵ�" << i+1 << "�����Ѷ�����======" << endl;
                    s.printSudoku();
                    Sleep(1000);
                }
                break;
            }
            case 2: {
                //������ͨ��������Ϸ
                for (int i = 0; i < para_n; i++) {
                    Sudoku s;
                    s.generateSudoku();
                    s.gen_Sudoku_with_n_empty(20, false);
                    cout << "======�ɹ����ɵ�" << i+1 << "����ͨ�Ѷ�����======" << endl;
                    s.printSudoku();
                    Sleep(1000);
                }
                break;
            }
            case 3: {
                //�������ѵ�������Ϸ
                for (int i = 0; i < para_n; i++) {
                    Sudoku s;
                    s.generateSudoku();
                    s.gen_Sudoku_with_n_empty(40, false);
                    cout << "======�ɹ����ɵ�" << i + 1 << "�������Ѷ�����======" << endl;
                    s.printSudoku();
                    Sleep(1000);
                }
                break;
            }
            default:
                cout << "�Ƿ����Ѷ�ָ������" << endl;
            }
            // ����4����
            break;
        }
        case 'r': {
            // ���û���ҵ�-n���������������Ϣ
            if (!found_n) {
                std::cerr << "���󣺲���-r�����-nһ��ʹ��" << std::endl;
                return 1;
            }
            extra_para = true;
            // ��ȡ����-r��ֵ
            string r_arg = std::string(optarg);
            int l_limit, h_limit;
            extractNumbers(r_arg, l_limit, h_limit);
            for (int i = 0; i < para_n; i++) {
                Sudoku s;
                s.generateSudoku();
                int emptyNum = rand() % (h_limit - l_limit + 1) + l_limit;
                cout << "======�ɹ����ɵ�" << i + 1 << "���������ڿ���Ϊ"<<emptyNum<<"======" << endl;
                s.gen_Sudoku_with_n_empty(emptyNum, false);
                s.printSudoku();
                Sleep(1000);
            }
            break;
        }
        case 'u': {
            // ���û���ҵ�-n���������������Ϣ
            if (!found_n) {
                std::cerr << "���󣺲���-u�����-nһ��ʹ��" << std::endl;
                return 1;
            }
            extra_para = true;
            // ����6����
            for (int i = 0; i < para_n; i++) {
                Sudoku s;
                s.generateSudoku();
                s.gen_Sudoku_with_n_empty(20, true);
                cout << "======�ɹ����ɵ�" << i + 1 << "������Ψһ�������======" << endl;
                s.printSudoku();
                Sleep(1000);
            }
            break;
        }
        default:
            // ����δ֪ѡ��
            std::cerr << "����δ֪ѡ��" << std::endl;
            return 1;
        }
    }
    if (found_n & !extra_para) {
        for (int i = 0; i < para_n; i++) {
            Sudoku s;
            s.generateSudoku();
            s.gen_Sudoku_with_n_empty(20, false);
            cout << "======�ɹ����ɵ�" << i + 1 << "������======" << endl;
            s.printSudoku();
            Sleep(1000);
        }
    }

    string input;
    while (true) {
        cout << "������ָ��(exit�˳�����)��";
        cin >> input;
        if (input == "exit") {
            break;
        }
        // TODO: ִ������ָ��
    }
    return 0;
}


