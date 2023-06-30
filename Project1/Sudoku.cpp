#include<iostream>
#include<set>
#include<algorithm>
#include<fstream>
#include<sstream>
#include <stdio.h>
#include <windows.h>
#include<iomanip>
#include"getopt.h"
#include "solution.cpp"
using namespace std;
// �����࣬���������ģ��һ��������Ϸ
class Sudoku {
private:
    int data[9][9] = { 0 };
public:
    bool GenerateSudoku();
    bool CheckMatrix(char m);
    bool CheckMatrixUtil(int row_start, int row_end, int col_start, int col_end);
    bool CheckRow(int r);
    vector<vector<char>> TransData2Char();
    void FillData(vector<vector<char>> data_char);
    bool CheckCol(int c);
    void PrintSudoku();
    bool GenSudokuWithNEmpty(int n, bool is_unique);
    void ClearData();
    void SolveSudoku();
    void InsertData(int row,int col,int data);
    void Print2TXT(string path);
};

// ����һ��9*9��ά�ַ���������������Ϊһ������
void Sudoku::FillData(vector<vector<char>> data_char) {
    for (unsigned int i = 0; i < data_char.size(); i++) {
        for (unsigned int j = 0; j < data_char[i].size(); j++) {
            data[i][j] = int(data_char[i][j] - int('0'));
        }
    }
}

// ���������Լ����������ת��Ϊһ����ά�ַ�����
vector<vector<char>> Sudoku::TransData2Char() {
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
void Sudoku::PrintSudoku() {
    cout << "+-------+-------+-------+" << endl;
    for (int i = 0; i < 9; i++) {
        cout << "| ";
        for (int j = 0; j < 9; j++) {
            // ����Ǵ���д�ַ��Ļ���X����
            if (data[i][j] == 0) {
                cout << "$" << " ";
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
bool Sudoku::CheckMatrixUtil(int row_start, int row_end, int col_start, int col_end) {
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
bool Sudoku::CheckMatrix(char m) {
    switch (m) {
    case 'a':
        return CheckMatrixUtil(0, 2, 0, 2);
    case 'b':
        return CheckMatrixUtil(0, 2, 3, 5);
    case 'c':
        return CheckMatrixUtil(0, 2, 6, 8);
    case 'd':
        return CheckMatrixUtil(3, 5, 0, 2);
    case 'e':
        return CheckMatrixUtil(3, 5, 3, 5);
    case 'f':
        return CheckMatrixUtil(3, 5, 6, 8);
    case 'g':
        return CheckMatrixUtil(6, 8, 0, 2);
    case 'h':
        return CheckMatrixUtil(6, 8, 3, 5);
    case 'i':
        return CheckMatrixUtil(6, 8, 6, 8);
    default:
        throw "ERROR AT CheckMatrix";
    }
}

//���ĳһ���Ƿ���ȷ
bool Sudoku::CheckCol(int c) {
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
bool Sudoku::CheckRow(int r) {
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
bool Sudoku::GenerateSudoku() {
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
    while (first_in | (!CheckCol(3) | !CheckCol(4) | !CheckCol(5) | !CheckCol(6) | !CheckCol(7) | !CheckCol(8) | !CheckMatrix('b') | !CheckMatrix('c'))) {
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
    vector<vector<char>> complete_data = TransData2Char();
    s.solveSudoku(complete_data);
    FillData(complete_data);
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
bool Sudoku::GenSudokuWithNEmpty(int n, bool is_unique) {
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
void Sudoku::ClearData() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            this->data[i][j] = 0;
        }
    }
}

//�������
void Sudoku::SolveSudoku() {
    Solution s;
    vector<vector<char>> complete_data = TransData2Char();
    s.solveSudoku(complete_data);
    FillData(complete_data);
}

//��ָ��λ�ò���ֵ
void Sudoku::InsertData(int row,int col,int data) {
    if ((row < 0) | (row>8) | (col < 0) | (col>8) | (data < 0) | (data>9)) {
        cout << "������ָ��λ�ò�����ֵʧ��"<<endl;
        return;
    }
    this->data[row][col] = data;
    return;
}

void Sudoku::Print2TXT(string path) {
    string filename = path;
    std::ofstream ofs(filename, std::ios::app);
    if (!ofs) {
        cout << "�޷����ļ���" << filename << endl;
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
                ofs << "$" << " ";
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
void SolveTXTSudoku(string path) {
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
            if (s[i]=='$') {
                su.InsertData(index_row, index_col++, 0);
                if (index_col == 9) {
                    index_row += 1;
                    index_col = 0;
                    if (index_row == 9) {
                        su.SolveSudoku();
                        su.Print2TXT("sudoku.txt");
                        cout << "======�ɹ�����" << ++count << "������======" << endl;
                        su.PrintSudoku();
                        su.ClearData();
                        index_row = 0; index_col = 0;
                    }
                }
                continue;
            }
            if (s[i] >= '1' && s[i] <= '9') {
                su.InsertData(index_row, index_col++, s[i]-'0');
                if (index_col == 9) {
                    index_row += 1;
                    index_col = 0;
                    if (index_row == 9) {
                        su.SolveSudoku();
                        su.Print2TXT("sudoku.txt");
                        cout << "======�ɹ�����" << ++count << "������======" << endl;
                        su.PrintSudoku();
                        su.ClearData();
                        index_row = 0; index_col = 0;
                    }
                }
                continue;
            }
        }
    }
    infile.close();
}
void ExtractNumbers(const std::string& str, int& num1, int& num2) {
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
            if ((cur_arg <= 0)||(cur_arg>1000000)) {
                cout << "�Ƿ��Ĳ���" << endl;
                return -1;
            }
            for (int i = 0; i < cur_arg; i++) {
                Sudoku s;
                s.GenerateSudoku();
                cout << "======�ɹ����ɵ�" << i+1 << "������======" << endl;
                s.PrintSudoku();
                s.Print2TXT("endGame.txt");
                cout << endl;
                Sleep(1000);
            }
            break;
        }
        case 's': {
            string s_path = std::string(optarg);
            SolveTXTSudoku(s_path);
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
            //cout << m_arg << endl;
            switch (m_arg)
            {
            case 1: {
                //���ɼ򵥵�������Ϸ
                if ((para_n <= 0) || (para_n>10000)) {
                    cout << "�Ƿ��Ĳ���" << endl;
                    return -1;
                }
                for (int i = 0; i < para_n; i++) {
                    Sudoku s;
                    s.GenerateSudoku();
                    s.GenSudokuWithNEmpty(10, false);
                    cout << "======�ɹ����ɵ�" << i+1 << "�����Ѷ�����======" << endl;
                    s.PrintSudoku();
                    Sleep(1000);
                }
                break;
            }
            case 2: {
                //������ͨ��������Ϸ
                if ((para_n <= 0) || (para_n > 10000)) {
                    cout << "�Ƿ��Ĳ���" << endl;
                    return -1;
                }
                for (int i = 0; i < para_n; i++) {
                    Sudoku s;
                    s.GenerateSudoku();
                    s.GenSudokuWithNEmpty(20, false);
                    cout << "======�ɹ����ɵ�" << i+1 << "����ͨ�Ѷ�����======" << endl;
                    s.PrintSudoku();
                    Sleep(1000);
                }
                break;
            }
            case 3: {
                //�������ѵ�������Ϸ
                if ((para_n <= 0) || (para_n > 10000)) {
                    cout << "�Ƿ��Ĳ���" << endl;
                    return -1;
                }
                for (int i = 0; i < para_n; i++) {
                    Sudoku s;
                    s.GenerateSudoku();
                    s.GenSudokuWithNEmpty(40, false);
                    cout << "======�ɹ����ɵ�" << i + 1 << "�������Ѷ�����======" << endl;
                    s.PrintSudoku();
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
            ExtractNumbers(r_arg, l_limit, h_limit);
            if (l_limit < 20) {
                cout << "�Ƿ����½磬�½��Ѹ���Ϊ20" << endl;
                l_limit = 20;
            }
            if (h_limit > 55) {
                cout << "������������������ޣ������Ѿ�����Ϊ55" << endl;
                h_limit = 55;
            }
            if ((para_n <= 0) || (para_n > 10000)) {
                cout << "�Ƿ��Ĳ���" << endl;
                return -1;
            }
            for (int i = 0; i < para_n; i++) {
                Sudoku s;
                s.GenerateSudoku();
                int emptyNum = rand() % (h_limit - l_limit + 1) + l_limit;
                cout << "======�ɹ����ɵ�" << i + 1 << "���������ڿ���Ϊ"<<emptyNum<<"======" << endl;
                s.GenSudokuWithNEmpty(emptyNum, false);
                s.PrintSudoku();
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
            if ((para_n <= 0) || (para_n > 10000)) {
                cout << "�Ƿ��Ĳ���" << endl;
                return -1;
            }
            for (int i = 0; i < para_n; i++) {
                Sudoku s;
                s.GenerateSudoku();
                s.GenSudokuWithNEmpty(20, true);
                cout << "======�ɹ����ɵ�" << i + 1 << "������Ψһ�������======" << endl;
                s.PrintSudoku();
                Sleep(1000);
            }
            break;
        }
        default:
            // ����δ֪ѡ��
            std::cerr << "����δ֪ѡ��" << std::endl;
            return -1;
        }
    }
    if (found_n & !extra_para) {
        if ((para_n <= 0) || (para_n > 10000)) {
            cout << "�Ƿ��Ĳ���" << endl;
            return -1;
        }
        for (int i = 0; i < para_n; i++) {
            Sudoku s;
            s.GenerateSudoku();
            s.GenSudokuWithNEmpty(20, false);
            cout << "======�ɹ����ɵ�" << i + 1 << "������======" << endl;
            s.PrintSudoku();
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


