//
// Created by tommy on 25/06/2022.
//

#ifndef MAIN_GAMEFILEEXCEPTION_H
#define MAIN_GAMEFILEEXCEPTION_H

#include <stdexcept>
#include <string>

class GameFileException : public std::runtime_error {
public:

    GameFileException(std::string whatMsg, std::string fileName, bool f = false);

    std::string getFilename() const { return fileName; };

    void printError() const;

    bool isFatal() { return fatal; };

private:

    std::string fileName;
    bool fatal;
};

#endif //MAIN_GAMEFILEEXCEPTION_H
