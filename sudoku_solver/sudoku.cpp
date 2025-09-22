//
//  sudoku.cpp
//  sudoku_solver
//
//  Created by Emre Kırcı on 19.09.2025.
//

#include "sudoku.hpp"
#include <iostream>
#include <fstream>
#include <vector>

// constructor
Sudoku::Sudoku(const std::string& filename, bool is_mini) : mini(is_mini) {
    // generating size and row,col size with short if
    size = mini ? 6 : 9;
    box_size_col = mini ? 3 : 3;
    box_size_row = mini ? 2 : 3;


    // start the grid vector
    grid.resize(size, std::vector<int>(size, 0));

    //  reading from main.php for mini.dat or sudoku.dat to grid vector
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: 404" << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            file >> grid[i][j];
        }
    }
    file.close();
}

// searching for empty 0 cell.
bool Sudoku::find_empty_cell(int& row, int& col) const {
    for (row = 0; row < size; ++row) {
        for (col = 0; col < size; ++col) {
            if (grid[row][col] == 0) {
                return true; // this is empty cell
            }
        }
    }
    return false; // all cells are filled
}

// placement function
bool Sudoku::placement(int row, int col, int num) const {
    // first lets check row no parameter will be affect
    //std::cout << "Trying Row: " << row << " Col: " << col << std::endl;
    for (int x = 0; x < size; ++x) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // second lets check column no parameter will be affect
    for (int x = 0; x < size; ++x) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // third lets check grid-area (may not be a rectangle) no parameter will be affect
    int start_row = row - row % box_size_row;
    int start_col = col - col % box_size_col;
    for (int i = 0; i < box_size_row; ++i) {
        for (int j = 0; j < box_size_col; ++j) {
            if (grid[i + start_row][j + start_col] == num) {
                return false;
            }
        }
    }

    return true; // we can write num to this location
}

// recursive sudoku function
bool Sudoku::solve_recursive() {
    int row, col;
    // check empty cell if all cells are full (!=0) sudoku solved! Else recursive loop flows.
    if (find_empty_cell(row, col)==false) {
        return true; // sudoku solved.
    }

    // bruteforce from 1 to size to get a valid placement
    for (int num = 1; num <= size; ++num) {
        // placement test with bruteforce
        if (placement(row, col, num)) {
            // if not false place the num into grid
            grid[row][col] = num;
            std::cout << "Trying Row: " << row << " Col: " << col << "  ✅ Find: " << num << std::endl;
            // continue to next empty cell
            if (solve_recursive()) {
                return true;
            }

            //if cant find the solution reset
            grid[row][col] = 0;
        }
    }
    //no num is suitable for the solution there may be an error for tirgger backtracking return false

    return false;
}

// main public function calls recursive
bool Sudoku::solve() {
    return solve_recursive();
}

// grid printer for both problem and solution
void Sudoku::print() const {
    for (int i = 0; i < size; ++i) {
        if (i % box_size_row == 0 && i != 0) {
            for(int k=0; k < size + box_size_row - 1; ++k) std::cout << " -";
            std::cout << std::endl;
        }
        for (int j = 0; j < size; ++j) {
            if (j % box_size_col == 0 && j != 0) {
                std::cout << " / ";
            }
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
