//
// Created by HYX on 2023-06-29.
//
#include "gtest/gtest.h"
//#include "Sudoku.cpp"

//#include "test.h"
#include "Sudoku.h"

//TEST(add,null){
//    int x = 1;
//    int y = 2;
//    EXPECT_EQ(add(x,y), 33);
//}

TEST(sub,null){
    int x = 1;
    int y = 2;
    Sudoku s;
    EXPECT_EQ(s.sub(x,y), 0);
}

TEST(generateSudoku,generateValidSudoku){
    Sudoku s;
    s.generateSudoku();
    EXPECT_TRUE(s.checkMatrix('a'));
    EXPECT_TRUE(s.checkMatrix('b'));
    EXPECT_TRUE(s.checkMatrix('c'));
    EXPECT_TRUE(s.checkMatrix('d'));
    EXPECT_TRUE(s.checkMatrix('e'));
    EXPECT_TRUE(s.checkMatrix('f'));
    EXPECT_TRUE(s.checkMatrix('g'));
    EXPECT_TRUE(s.checkMatrix('h'));
    EXPECT_TRUE(s.checkMatrix('i'));
}



TEST(checkMatrix,testInvaliSudoku){
    Sudoku s;
    s.generateSudoku();
    int row_1 = 0;
    int col_1 = 0;
    int row_2 = 0;
    int col_2 = 1;
    s.set_pos(row_2,col_2,s.get_pos(row_1,col_1));
    EXPECT_FALSE(s.checkMatrix('a'));
    EXPECT_TRUE(s.checkMatrix('b'));
    EXPECT_TRUE(s.checkMatrix('c'));
    EXPECT_TRUE(s.checkMatrix('d'));
    EXPECT_TRUE(s.checkMatrix('e'));
    EXPECT_TRUE(s.checkMatrix('f'));
    EXPECT_TRUE(s.checkMatrix('g'));
    EXPECT_TRUE(s.checkMatrix('h'));
    EXPECT_TRUE(s.checkMatrix('i'));
}

TEST(checkMatrix,testInvaliSudoku2){
    Sudoku s;
    s.generateSudoku();
    int row_1 = 0;
    int col_1 = 0;
    int row_2 = 9;
    int col_2 = 0;
    s.set_pos(row_2,col_2,s.get_pos(row_1,col_1));
    EXPECT_FALSE(s.checkMatrix('a'));
    EXPECT_TRUE(s.checkMatrix('b'));
    EXPECT_TRUE(s.checkMatrix('c'));
    EXPECT_TRUE(s.checkMatrix('d'));
    EXPECT_TRUE(s.checkMatrix('e'));
    EXPECT_TRUE(s.checkMatrix('f'));
    EXPECT_TRUE(s.checkMatrix('g'));
    EXPECT_TRUE(s.checkMatrix('h'));
    EXPECT_TRUE(s.checkMatrix('i'));
}

TEST(checkMatrix,testInvaliSudoku3){
    Sudoku s;
    s.generateSudoku();
    int row_1 = 0;
    int col_1 = 0;
    int row_2 = 0;
    int col_2 = 8;
    s.set_pos(row_2,col_2,s.get_pos(row_1,col_1));
    EXPECT_FALSE(s.checkMatrix('a'));
    EXPECT_TRUE(s.checkMatrix('b'));
    EXPECT_TRUE(s.checkMatrix('c'));
    EXPECT_TRUE(s.checkMatrix('d'));
    EXPECT_TRUE(s.checkMatrix('e'));
    EXPECT_TRUE(s.checkMatrix('f'));
    EXPECT_TRUE(s.checkMatrix('g'));
    EXPECT_TRUE(s.checkMatrix('h'));
    EXPECT_TRUE(s.checkMatrix('i'));
}


TEST(checkMatrix,testValiSudoku){
    vector<vector<int>> valid_sudoku = {
            {1, 2, 3, 4, 5, 6, 7, 8, 9},
            {4, 5, 6, 7, 8, 9, 1, 2, 3},
            {7, 8, 9, 1, 2, 3, 4, 5, 6},
            {2, 1, 4, 3, 6, 5, 8, 9, 7},
            {3, 6, 5, 8, 9, 7, 2, 1, 4},
            {8, 9, 7, 2, 1, 4, 3, 6, 5},
            {5, 3, 1, 6, 4, 2, 9, 7, 8},
            {6, 4, 2, 9, 7, 8, 5, 3, 1},
            {9, 7, 8, 5, 3, 1, 6, 4, 2}
    };
    Sudoku s;
    for(int i=0;i<9;i++){
        for (int j = 0; j < 9; ++j) {
            s.set_pos(i,j,valid_sudoku[i][j]);
        }
    }
    EXPECT_TRUE(s.checkMatrix('a'));
    EXPECT_TRUE(s.checkMatrix('b'));
    EXPECT_TRUE(s.checkMatrix('c'));
    EXPECT_TRUE(s.checkMatrix('d'));
    EXPECT_TRUE(s.checkMatrix('e'));
    EXPECT_TRUE(s.checkMatrix('f'));
    EXPECT_TRUE(s.checkMatrix('g'));
    EXPECT_TRUE(s.checkMatrix('h'));
    EXPECT_TRUE(s.checkMatrix('i'));
}

TEST(gen_Sudoku_with_n_empty,generateSudokuWithEmpty){
    Sudoku s;
    s.generateSudoku();
    int empty_cnt = 20;
    s.gen_Sudoku_with_n_empty(empty_cnt, false);
    EXPECT_EQ(s.empty_cnt(),empty_cnt);

}

TEST(gen_Sudoku_with_n_empty,generateUniqueSudokuWithEmpty){
    Sudoku s;
    s.generateSudoku();
    int empty_cnt = 20;
    s.gen_Sudoku_with_n_empty(empty_cnt, true);
    EXPECT_EQ(s.empty_cnt(),empty_cnt);
    EXPECT_TRUE(s.check_unique(s.get_data()));
}


TEST(gen_Sudoku_with_n_empty,testCheckNotUnique_3emptyRows){
    Sudoku s;
    s.generateSudoku();
    for(int i=0;i<3;i++){
        for(int j=0;j<9;j++){
            s.set_pos(i,j,0);
        }
    }
    EXPECT_FALSE(s.check_unique(s.get_data()));
}

TEST(gen_Sudoku_with_n_empty,testCheckNotUnique_3emptyCols){
    Sudoku s;
    s.generateSudoku();
    for(int i=0;i<9;i++){
        for(int j=0;j<3;j++){
            s.set_pos(i,j,0);
        }
    }
    EXPECT_FALSE(s.check_unique(s.get_data()));
}

TEST(solveSudoku, null){
    Sudoku s;
    s.generateSudoku();
    int data_copy[9][9];
    s.make_data_copy(data_copy);
    s.gen_Sudoku_with_n_empty(20, true);
    s.solveSudoku();
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            EXPECT_EQ(data_copy[i][j],s.get_data()[i][j]);
        }
    }
}

