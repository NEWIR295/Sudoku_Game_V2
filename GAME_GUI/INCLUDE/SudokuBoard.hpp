/*
Author: Mohamed Newir
Date: 22/12/2025
File: SudokuBoard.hpp
Description:
    o Description of SudokuBoard class which manipulates Sudoku Grid
*/

#ifndef SUDOKU_BOARD_HPP
#define SUDOKU_BOARD_HPP

#include <vector>
#include <string>
#include "../INCLUDE/JsonFileManager.hpp"

constexpr int BOARD_SIZE =  9;

class SudokuBoard
{

public:
    SudokuBoard(void);
    bool is_valid(int row, int col, int value) const;
    int getCell(int row, int col) const;
    bool setCell(int row, int col, int value);
    bool checkComplete(void) const;
    bool printGrid(void) const; // for debuging purposes
    std::vector<std::vector<int>> &getBoardData(void);
private:
    std::vector<std::vector<int>> board;
};

#endif