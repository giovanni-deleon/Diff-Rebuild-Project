// AUTHOR: Giovanni De Leon
// DESC: H FileService For Semester Proj.

#include<iostream>
#include<vector>
using namespace std;

class FileService {

public:
    FileService();// Constructor.
    void compareFilesTwo(const vector<string>& fileOneContents, const vector<string>& fileTwoContents);


    string removeWhitespace(const string& str);

    bool isLineEmpty(const string& line);

    void diff(string pFileName, string pFileNameTwo);// Takes File Name As Parameter.

};
