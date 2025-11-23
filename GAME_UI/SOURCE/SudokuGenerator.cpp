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
#include <algorithm>
#include <random>

bool SudokuGenerator::generatePuzzle(SudokuBoard& board, int level){
    
    for(int row = 0; row < 9; row++ ){
        for( int col = 0; col < 9; col++ ){
            board.setCell(row, col, 0);
        }
    }

    std::vector<int> numbers = {1,2,3,4,5,6,7,8,9};
    
    for(int i = 0; i < 9; i++){
        std::shuffle(numbers.begin(), numbers.end(), std::mt19937(std::random_device()())); // Modern shuffle
        for(int j = 0; j < 9; j++){
            for(int random : numbers){
                if(board.setCell(i, j, random)){

                    if(SudokuSolver::sudokuSolver(board)){
                        break;
                    } else {
                        board.setCell(i, j, 0); // reset cell
                    }
                }
            }
        }
    }

    if(setDifficulty(board, level)){
        return true;
    } else {
        return false;
    }
}

bool SudokuGenerator::setDifficulty(SudokuBoard& board, int level){
    int cellsToRemove = 0;

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
        case 4: // Expert
            cellsToRemove = 60;
            break;
        default:
            cellsToRemove = 30;
            break;
    }

    /*
        we create pair container to store the positions of the 81 cells
    */
    std::vector<std::pair<int, int>> positions;
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            positions.push_back({row, col});
        }
    }
    /*
        then we shuffle the vector and delete the first emptyCells number of cells
        this way we are sure that we will not delete the same cell more than once
        and we are sure that the cells are random
        */
   // std::random_shuffle(positions.begin(), positions.end()); // not allowed in c++17
    std::shuffle(positions.begin(), positions.end(), std::mt19937(std::random_device()())); // Modern shuffle
    for (int i = 0; i < cellsToRemove; i++)
    {
        board.setCell(positions[i].first, positions[i].second, 0);
    }

    return true;
}