#Author: Mohamed Newir
#Date: 23/12/2025
#File Name: CMakelists.txt
#Description: This file is used to compile the source code for the project
#             and set the required version of cmake and the required standard version of C++.
#             It also sets the compile options and the include directories for the project. 

#set the minimum required version of cmake
cmake_minimum_required(VERSION 3.10)

#set the project name
project(Sudoku_Game_V2
        VERSION 1.0.0
        DESCRIPTION "Sudoku Game V2 - A console-based Sudoku game with puzzle generation and solving features."
        LANGUAGES CXX)

#CPP standard version required for the project  
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set the include directory
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/INCLUDE)

#set the sources to be compiled 
set(LIB_SOURCES 
    #./SOURCE/main.cpp
    ./SOURCE/SudokuGame.cpp
    ./SOURCE/SudokuBoard.cpp
    ./SOURCE/SudokuSolver.cpp
    ./SOURCE/SudokuGenerator.cpp
    ./SOURCE/JsonFileManager.cpp
)

# Static library target
add_library(Sudoku_Game_V2_LIB STATIC ${LIB_SOURCES})
target_include_directories(Sudoku_Game_V2_LIB PUBLIC ${INCLUDE_DIR})
target_compile_features(Sudoku_Game_V2_LIB PUBLIC cxx_std_17)

# Set the output directory for the static library to be in the lib folder in GAME_UI directory
set_target_properties(Sudoku_Game_V2_LIB PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

# Set the output directory for the static library to be in the lib folder in GAME_GUI directory for qt project
# set_target_properties(Sudoku_Game_V2_LIB PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../GAME_GUI/lib
# )

#add the executable
add_executable(sudoku ${CMAKE_SOURCE_DIR}/SOURCE/main.cpp)
#add the include directories
target_include_directories(sudoku PRIVATE ${INCLUDE_DIR})
#compile features required for the project
target_compile_features(sudoku PRIVATE cxx_std_17)
#add the compile options
# target_compile_options(sudoku PRIVATE -Wall -Wextra -Werror -Wpedantic)

# Link the static library to the executable
target_link_libraries(sudoku PRIVATE Sudoku_Game_V2_LIB)

# Set the output directory for the executable to be in the game folder in GAME_UI directory
set_target_properties(sudoku PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/game
)
# End of CMakeLists.txt