
#include <iostream>
#include "../INCLUDE/JsonFileManager.hpp"

GameJsonFileManager::GameJsonFileManager(std::string filename = "Default_Puzzle")
    : filename(filename)
{
}

bool GameJsonFileManager::readJsonFile(std::vector<std::vector<int>> &boardData)
{
    inputFile.open("../Puzzle/" + this->filename + ".json");
    if (!inputFile)
    {
        std::cerr << "../Puzzle/" + this->filename + ".json doesn't exist" << std::endl;
        return false;
    }

    if (!inputFile.is_open())
    {
        std::cerr << "../Puzzle/" + this->filename + ".json is corrupted can't be opened" << std::endl;
        return false;
    }

    inputFile >> jsonFile;

    for (int i = 0; i < 9; i++)
    {

        const auto &row = jsonFile["Grid"][i];
        for (int j = 0; j < 9; j++)
        {
            boardData[i][j] = row[j].get<int>();
        }
    }

    std::cout << "Game Loaded" << std::endl;
    
    inputFile.close();
    return true;
}

bool GameJsonFileManager::writeJsonFile(const std::vector<std::vector<int>> &boardData)
{
    outputFile.open("../Puzzle/" + filename + ".json");

    if (!outputFile)
    {
        std::cerr << "../Puzzle/" + this->filename + ".json doesn't exist" << std::endl;
        return false;
    }

    if (!outputFile.is_open())
    {
        std::cerr << "../Puzzle/" + this->filename + ".json is corrupted can't be opened" << std::endl;
        return false;
    }

    jsonFile["Puzzle_Name"] = this->filename; 
    jsonFile["Grid"] = boardData;
    
    outputFile << jsonFile.dump(4);
    
    std::cout << "Game Saved Successfully" << std::endl;
    
    outputFile.close();
    return true;
}