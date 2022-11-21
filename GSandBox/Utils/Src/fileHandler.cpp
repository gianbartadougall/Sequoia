/**
 * @file fileHandler.cpp
 * @author Gian Barta-Dougall
 * @brief System file for fileHandler
 * @version 0.1
 * @date --
 *
 * @copyright Copyright (c)
 *
 */
/* Public Includes */
#include <iostream>
#include <fstream>

/* Private Includes */
#include "fileHandler.h"

using namespace fileHandler;

FileHandler::FileHandler() {}

FileHandler::~FileHandler() {}

void FileHandler::read_text_file(char* filePath, std::string fileData) {

    // The file path is relative to the environment you call the executable from
    std::ifstream textFile(filePath);

    if (textFile.is_open() != true) {
        std::cout << "Unable to open '" << filePath << "'\n";
        return;
    }

    while (std::getline(textFile, fileData)) {}

    std::cout << "IN FUNC: " << fileData << "\n";
    textFile.close();
}