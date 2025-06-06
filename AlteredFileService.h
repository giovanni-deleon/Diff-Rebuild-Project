// AUTHOR: Giovanni De Leon
// DESC: H FileService For Semester Proj.

#include<iostream>
#include<vector>
#include <string>
using namespace std;

class FileService {

public:
    FileService();// Constructor.
    void compareFilesTwo(const vector<pair<int, string>>& fileOneContents, const vector<pair<int, string>>& fileTwoContents);

    void fancyDiff(int pIndex, int fileOneLineAmount, int fileTwoLineAmount, const vector<pair<int, string>>& fileOneContents, const vector<pair<int, string>>& fileTwoContents);

    string removeWhitespace(const string& str);

    bool isLineEmpty(const string& line);

    void diff(string pFileName, string pFileNameTwo);// Takes File Name As Parameter.

};
