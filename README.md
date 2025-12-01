# Sudoku Game V2 Project
## Author: [Mohamed Newir](https://www.linkedin.com/in/mohamed-newir-a8a572182)

## Overview
project I made as a fun way to refresh my knowledge after a personal time off I took from engineering ^^, following teaching two rounds at ITI. I chose to refactor and optimize a previous Sudoku game project I had developed as part of my **software development diploma** at **Edges for Training**. I used C++ OOP, Qt6 and CMake to develop the game, adding new features in the process.


## Project Description
This is a Graphical User Interface Application implementation using **Qt** of the popular **Sudoku puzzle**, built in **C++ with CMake** using a modular object-oriented approach. The project emphasizes clean design, separation of concerns, and practical use of the Standard Template Library (STL).

## The game supports the following functionalities:
- **Interactive Graphical  User Interface Application**: Play, solve, load, and save puzzles.
- **Backtracking Solver**: Solve any valid Sudoku puzzle.
- **Input Validation**: Ensures all moves and file inputs are correct.
- **Puzzle Generation**: Generates with different difficulty levels (Easy, Medium, Hard).

## Features
- Enter and validate player moves.
- Solve puzzles automatically using backtracking algorithm.
- Generates new puzzles using backtracking algorithm.
- Save the current puzzle state to a json file.
- Load puzzle from a file.
- Modular class structure to support scalability.

## Default Puzzle

### Upon starting, the Sudoku program displays the default board :

![SudokuGame Image](./Images/SudokuGame.png)

## Project Objectives
- Implement a fully functional Sudoku engine using a clean, modular structure.
- Demonstrate separation of concerns and proper software architecture.

## Functional Requirements
- Build a static library for sudoku main function to be used by the GUI app using CMake
- Display a 9×9 Sudoku Grid using QML format.
- Display game using a Qt based application.
- Validate user inputs (row, column, value).
- Detect and reject invalid moves.
- Display a completed solution or indicate if the puzzle is unsolvable.

## Class Architecture
- **SudokuBoard**: Manages the 9x9 grid, validation, and board display.
- **SudokuSolver**: Implements the recursive backtracking solver.
- **SudokuGame**: Manages the game loop and user interaction.
- **SudokuGenerator**: Generates valid Sudoku puzzles using recursive backtracking Algorithm.

## File Management Architecture

## File Structure

```
Sudoku_Game_V2/
├── Dockerfile                      # Docker configuration for building/running the project
├── sudoku.bash                     # Bash script to launch the game
├── LICENSE                         # License file
├── README.md                       # Project documentation (you are reading it!)
├── Images/                    
│   └──  SudokuGame.png             # Game image
├── Video/    
├── GAME_GUI/                       # Qt6-based graphical version (with animations & sound)
│   ├── CMakeLists.txt              # CMake build configuration
│   ├── res.qrc                     # Qt resource file
│   ├── main.cpp                    # GUI entry point
│   ├── mainwindow.cpp
│   ├── mainwindow.h
│   ├── mainwindow.ui               # Qt Designer form
│   ├── build/                      # Generated build directory (CMake)
│   ├── game/
│   │   ├── Sudoku                  # Compiled GUI executable
│   │   └── sudoku.png
│   ├── INCLUDE/                    # Header files
│   │   ├── JsonFileManager.hpp
│   │   ├── SudokuBoard.hpp
│   │   ├── SudokuGenerator.hpp
│   │   └── SudokuSolver.hpp
│   ├── lib/
│   │   └── libSudoku_Game_V2_LIB.a # Static library with core logic
│   ├── Puzzle/                     # JSON puzzle files
│   │   ├── Default_Puzzle.json
│   │   ├── test.json
│   │   ├── test2.json
│   │   ├── test3.json
│   │   ├── test5.json
│   │   └── test6.json
│   ├── res/
│   │   ├── gif/
│   │   │   └── yes.gif
│   │   ├── icons/                  # UI icons
│   │   │   ├── github.png
│   │   │   ├── linkedin.png
│   │   │   ├── load.png
│   │   │   │   ├── mute.png
│   │   │   ├── new.png
│   │   │   ├── save.png
│   │   │   ├── solve.png
│   │   │   ├── sudoku.png
│   │   │   └── volume.png
│   │   ├── music/
│   │   │   └── music.mp3
│   │   └── qml/
│   │       └── sudokuBoard.qml     # QML component for animated board                  
│
└── GAME_UI/                        # Lightweight terminal/console version
    ├── CMakeLists.txt              # CMake build configuration
    ├── Build/                      # Generated build directory (CMake)
    ├── game/
    │   └── sudoku                  # Compiled console executable
    ├── INCLUDE/
    │   ├── JsonFileManager.hpp
    │   ├── SudokuBoard.hpp
    │   ├── SudokuGame.hpp
    │   ├── SudokuGenerator.hpp
    │   └── SudokuSolver.hpp
    ├── lib/                        
    ├── Puzzle/
    │   ├── Default_Puzzle.json
    │   └── test.json
    └── SOURCE/
        ├── main.cpp
        ├── JsonFileManager.cpp
        ├── SudokuBoard.cpp
        ├── SudokuGame.cpp
        ├── SudokuGenerator.cpp
        └── SudokuSolver.cpp
```

## Demo

![SudokuGame Demo](./Video/SudokuGame.gif)

---
