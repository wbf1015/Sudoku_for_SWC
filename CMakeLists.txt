cmake_minimum_required(VERSION 3.24)
project(Sudoku_for_SWC)

set(CMAKE_CXX_STANDARD 11)

add_executable(Sudoku_for_SWC Sudoku.cpp Solution.cpp Sudoku.h Solution.h unittests.cpp)

add_subdirectory(./googletest)
include_directories(./googletest/include)
link_directories(${PROJECT_SOURCE_DIR}/googletest)
target_link_libraries(${PROJECT_NAME} gtest)