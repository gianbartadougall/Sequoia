/**
 * @file fileHandler.h
 * @author Gian Barta-Dougall
 * @brief System file for fileHandler
 * @version 0.1
 * @date --
 *
 * @copyright Copyright (c)
 *
 */
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

/* Public Includes */
#include <string>

namespace fileHandler {

class FileHandler {

    // Private variables

  public:
    FileHandler();
    ~FileHandler();

    void read_text_file(char* filePath, std::string fileData);
};

} // namespace fileHandler

#endif // FILEHANDLER_H
