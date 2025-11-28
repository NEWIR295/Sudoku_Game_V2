/*
Author: Mohamed Newir
Date: 22/12/2025
File: SudokuGenerator.hpp
Description:
    o Description of SudokuSolver class which generate Sudoku solvable sudoku puzzle
*/

#ifndef SUDOKU_GENERATOR_HPP
#define SUDOKU_GENERATOR_HPP

#include "../INCLUDE/SudokuBoard.hpp"

class SudokuGenerator{

    public:
        static bool generatePuzzle(SudokuBoard& board, int level);
        
    private:
        static bool setDifficulty(SudokuBoard& board, int level);
};

#endif