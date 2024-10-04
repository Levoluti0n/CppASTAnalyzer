#include "FileHandler.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::string FileHandler::readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if(!file) {
        std::cerr << "[-] Error: Unable to open file " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
