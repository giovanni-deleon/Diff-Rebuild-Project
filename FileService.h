// AUTHOR: Giovanni De Leon
// DESC: H FileService For Semester Proj.

#ifndef FILESERVICE_H
#define FILESERVICE_H

#include<iostream>
#include<vector>
#include <string>
using namespace std;

class FileService {

public:
    FileService();// Constructor.
    void compareFilesTwo(const std::vector<std::pair<int, std::string>>& fileOneContents, const std::vector<std::pair<int, std::string>>& fileTwoContents);

    void fancyDiff(int pIndex, int fileOneLineAmount, int fileTwoLineAmount, const std::vector<pair<int, string>>& fileOneContents, const std::vector<pair<int, string>>& fileTwoContents);

    std::string removeWhitespace(const std::string& str);

    bool isLineEmpty(const std::string& line);

    void diff(std::string pFileName, std::string pFileNameTwo);// Takes File Name As Parameter.
    
    void promptingServ();

};

#endif // FILESERVICE_H
