/*
Author: Mohamed Newir
Date: 22/12/2025
File: JsonFileManager.hpp
Description:
    o Description of GameJsonFileManager class which saves and load data in .json files
*/

#ifndef JSON_FILE_MANGER_HPP
#define JSON_FILE_MANGER_HPP

#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class GameJsonFileManager
{

public:
    GameJsonFileManager(std::string filename = "Default_Puzzle");
    bool readJsonFile(std::vector<std::vector<int>> &boardData);
    bool writeJsonFile(const std::vector<std::vector<int>> &boardData);

private:
    std::string filename;
    std::ofstream outputFile;
    std::ifstream inputFile;
    nlohmann::json jsonFile;
};

#endif