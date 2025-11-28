cmake_minimum_required(VERSION 3.19)
project(Sudoku LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic handling of Qt-specific files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets Quick QuickWidgets Multimedia)

qt_standard_project_setup()

set(QML_FILES
    res/qml/sudokuBoard.qml
)

set(Include_Files
    INCLUDE/JsonFileManager.hpp
    INCLUDE/SudokuSolver.hpp
    INCLUDE/SudokuBoard.hpp
    INCLUDE/SudokuGenerator.hpp

)

set(libSudoku_Game_V2_LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/libSudoku_Game_V2_LIB.a)


qt_add_executable(Sudoku
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${Include_Files}
    ${QML_FILES}
    res.qrc
)

target_link_libraries(Sudoku
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Gui
        Qt6::Quick
        Qt6::QuickWidgets
        Qt6::Multimedia
        ${libSudoku_Game_V2_LIB}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/INCLUDE
)

include(GNUInstallDirs)

install(TARGETS Sudoku
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Set the output directory for the executable to be in the game folder in GAME_GUI directory
set_target_properties(Sudoku PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/game
)

qt_generate_deploy_app_script(
    TARGET Sudoku
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
