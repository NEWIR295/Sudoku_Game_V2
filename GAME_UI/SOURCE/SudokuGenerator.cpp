/*
Author: Mohamed Newir
Date: 22/12/2025
File: SudokuGenerator.cpp
Description:
    o implementation of SudokuSolver class which generate Sudoku solvable sudoku puzzle
*/

#include "../INCLUDE/SudokuGenerator.hpp"
#include "../INCLUDE/SudokuSolver.hpp"
#include <vector>

bool SudokuGenerator::generatePuzzle(SudokuBoard& board, int level){
    
    for(int row = 0; row < 9; row++ ){
        for( int col = 0; col < 9; col++ ){
            board.setCell(row, col, 0);
        }
    }

    std::vector<int> numbers = {1,2,3,4,5,6,7,8,9};

    for(int i = 0; i < 9; i++){
        std::random_shuffle(numbers.begin(), numbers.end());
        for(int j = 0; j < 9; j++){
            for(int random : numbers){
                if(board.setCell(i, j, random)){
                    break;
                }
            }
        }
    }

    if(SudokuSolver::sudokuSolver(board)){
        setDifficulty(board, level);
        return true;
    } else {
        return false;
    }
}

bool SudokuGenerator::setDifficulty(SudokuBoard& board, int level){
    int cellsToRemove;

    switch(level){
        case 1: // Easy
            cellsToRemove = 30;
            break;
        case 2: // Medium
            cellsToRemove = 40;
            break;
        case 3: // Hard
            cellsToRemove = 50;
            break;
        default:
            cellsToRemove = 30;
            break;
    }

    while(cellsToRemove > 0){
        int row = rand() % 9;
        int col = rand() % 9;

        if(board.getCell(row, col) != 0){
            board.setCell(row, col, 0);
            cellsToRemove--;
        }
    }

    return true;
}