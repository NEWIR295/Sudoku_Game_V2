gt/*
Author: Mohamed Newir
Date: 22/12/2025
File: SudokuSolver.cpp
Description:
    o implementation of SudokuSolver class which solves Sudoku Grid or deduce that the board is in solvable
*/

#include "../INCLUDE/SudokuSolver.hpp"
#include "../INCLUDE/SudokuBoard.hpp"

bool SudokuSolver::sudokuSolver(SudokuBoard &board)
{
    /* backtracking algorithm */
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 0; col < BOARD_SIZE; col++){

            if(board.getCell(row, col) == 0){

                for(int value = 1; value <= 9; value++){
                    if(board.setCell(row, col, value)){
                        if(sudokuSolver(board)){
                            return true;
                        } else {
                            board.setCell(row, col, 0);
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}
