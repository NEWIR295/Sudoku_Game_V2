/*
Author: Mohamed Newir
Date: 22/12/2025
File: SudokuBoard.cpp
Description:
    o implementation of SudokuBoard class which manipulates Sudoku Grid
*/

#include <iostream>
#include "../INCLUDE/SudokuBoard.hpp"

SudokuBoard::SudokuBoard(void) : board(9, std::vector<int>(BOARD_SIZE, 0)) {};

bool SudokuBoard::is_valid(int row, int col, int value) const
{
    if (value != 0)
    {

        if(value < 1 || value > 9) return false;

        /* check vertical and horizontal lines */
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if ((value == board[row][i]) || (value == board[i][col]))
            {
                return false;
            }
        }

        /* check grid box */
        int rowBox = row - row % 3;
        int colBox = col - col % 3;

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(board[i + rowBox][j + colBox] == value){
                    return false;
                }
            }
        }

    }
    return true;
}

int SudokuBoard::getCell(int row, int col) const
{
    return board[row][col];
}

bool SudokuBoard::setCell(int row, int col, int value)
{
    if (is_valid(row, col, value))
    {
        board[row][col] = value;
        return true;
    }
    return false;
}

bool SudokuBoard::printGrid(void) const // for debuging purposes
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        if (row % 3 == 0)
        {
            std::cout << "-------------------------\n";
        }
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (col % 3 == 0)
            {
                std::cout << "| ";
            }
            if (board[row][col] == 0)
            {
                std::cout << ". ";
            }
            else
            {
                std::cout << board[row][col] << " ";
            }
        }
        std::cout << "|\n";
    }
    std::cout << "-------------------------\n";
    return true;
}

std::vector<std::vector<int>> &SudokuBoard::getBoardData(void)
{
    return this -> board;
}