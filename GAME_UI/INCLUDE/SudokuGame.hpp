/*
Author: Mohamed Newir
Date: 22/11/2025
File: SudokuGame.hpp
Description:
    o Presents console menu, reads/writes user input.
    o Coordinates SudokuBoard and SudokuSolver.
    o Handles error-checking for moves and file operations.
*/

#ifndef SUDOKU_GAME
#define SUDOKU_GAME

#include "SudokuBoard.hpp"
#include "JsonFileManager.hpp"

class SudokuGame
{
private:
    SudokuBoard board;
    GameJsonFileManager fileManager;

public:
    void showMenu(void);
    void initGame(void);
};

#endif