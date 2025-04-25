#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <string>
#include <vector>
#include <utility>

class FileService {
public:
    FileService();  // Constructor

    std::string removeWhitespace(const std::string& str);
    bool isLineEmpty(const std::string& line);

    void compareFilesTwo(const std::vector<std::pair<int, std::string>>& fileOneContents,
                         const std::vector<std::pair<int, std::string>>& fileTwoContents);

    void fancyDiff(int pIndex, int pFileOneLineAmount, int pFileTwoLineAmount,
                   const std::vector<std::pair<int, std::string>>& fileOneContents,
                   const std::vector<std::pair<int, std::string>>& fileTwoContents);

    void diff(std::string pFileName, std::string pFileNameTwo);

    void promptingServ();

    void fusionService(const std::vector<std::pair<int, std::string>>& fileOneContents,
                   const std::vector<std::pair<int, std::string>>& fileTwoContents);

};

#endif // FILESERVICE_H
