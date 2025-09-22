//
//  sudoku.hpp
//  sudoku_solver
//
//  Created by Emre Kırcı on 19.09.2025.
//

#include <vector>
#include <string>
// we need to construct mini or full sudoku board so according to boolean data it generates full or mini board.
class Sudoku {
public:
    // constructor
    Sudoku(const std::string& filename, bool is_mini = false);

    // solve function
    bool solve();

    // print function
    void print() const;

private:
    // 2d vector for sudoku table definition
    std::vector<std::vector<int>> grid;
    
    // is the sudoku 6x6 or 9x9 bool value
    bool mini;
    
    // grid size (for 9x9 - 9, for 6x6 6).
    int size;
    
    // each row-col divider (for 9x9 -> 3, for 6x6 -> row=2 col=3).
    int box_size_row;
    int box_size_col;


    // the written number is valid or not
    bool placement(int row, int col, int num) const;
    
    // search for empty cell
    bool find_empty_cell(int& row, int& col) const;
    
    // recursive solve function
    bool solve_recursive();
};

