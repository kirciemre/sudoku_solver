//
//  main.cpp
//  sudoku_solver
//
//  Created by Emre Kırcı on 19.09.2025.
//

#include <iostream>
#include "sudoku.hpp"

int main() {
    // calling constructor with a filename dat.
    //Sudoku puzzle("mini.dat", true); // mini sudoku - true, 2nd parameter is -> is_mini
    Sudoku puzzle("sudoku.dat", false); // full sudoku - false, 2nd parameter is -> is_mini


    std::cout << "Given sudoku problem:" << std::endl;
    puzzle.print();
    std::cout << "\n===========================\n" << std::endl;

    // if it solved
    if (puzzle.solve()) {
        std::cout << "Sudoku solved! 👍" << std::endl;
        puzzle.print();


    } else {
        std::cout << "There is no solution for this board! 😅" << std::endl;
    }

    return 0; //program ended without error.
}
