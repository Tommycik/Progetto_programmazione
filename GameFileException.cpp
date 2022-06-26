//
// Created by tommy on 25/06/2022.
//


#include <iostream>
#include "GameFileException.h"


GameFileException::GameFileException(std::string whatMsg, std::string file_name, bool f) : std::runtime_error{whatMsg}, fileName{file_name}, fatal{f} {
    // ... more code if needed
}

void GameFileException::printError() const {
    std::cerr << "Missing file: " << fileName << std::endl;
}