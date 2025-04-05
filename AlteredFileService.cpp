#include "FileService.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <utility>  // For std::pair
using namespace std;

// File Service Constructor.
FileService::FileService() {}

// Helper function to remove all whitespace characters from a string and check if the line is empty after stripping whitespace
string FileService::removeWhitespace(const std::string& str) {
    string result;
    for (char c : str) {
        if (!isspace(c)) {  // If the character is not a whitespace (space, tab, newline, etc.)
            result.push_back(c);
        }
    }
    return result;
}

// Function to check if a line is empty after removing whitespace
bool FileService::isLineEmpty(const std::string& line) {
    return removeWhitespace(line).empty();
}

// Function that compares the files and displays the differences.
void FileService::compareFilesTwo(const vector<pair<int, string>>& fileOneContents, const vector<pair<int, string>>& fileTwoContents) {
    int fileOneSize = fileOneContents.size();
    int fileTwoSize = fileTwoContents.size();

    // Compare lines in fileOneContents with fileTwoContents
    for (int i = 0; i < fileOneSize; i++) {
        string fileOneLine = fileOneContents[i].second;  // Get line content
        int lineNumber = fileOneContents[i].first;  // Get line number
        bool foundMatch = false;

        // Skip empty lines after removing whitespace
        if (isLineEmpty(fileOneLine)) {
            continue;
        }

        // Compare with each line of fileTwoContents
        for (int j = 0; j < fileTwoSize; j++) {
            string fileTwoLine = fileTwoContents[j].second;
            // Skip empty lines after removing whitespace
            if (isLineEmpty(fileTwoLine)) {
                continue;
            }

            // Remove whitespace from both lines for comparison
            string fileOneLineStripped = removeWhitespace(fileOneLine);
            string fileTwoLineStripped = removeWhitespace(fileTwoLine);

            // If lines match after stripping whitespace
            if (fileOneLineStripped == fileTwoLineStripped) {
                foundMatch = true;
                break;  // Stop checking further lines in fileTwo
            }
        }

        // If no match is found, print the difference
        if (!foundMatch) {
            //cout << "DIFF at line " << lineNumber << " in File 1: " << fileOneLine << endl;
            cout << fileOneLine << " : " << "File 2 Line " << lineNumber << " - null" << endl;
        }
    }

    // Now compare lines in fileTwoContents with fileOneContents
    for (int i = 0; i < fileTwoSize; i++) {
        string fileTwoLine = fileTwoContents[i].second;
        int lineNumber = fileTwoContents[i].first;
        bool foundMatch = false;

        // Skip empty lines after removing whitespace
        if (isLineEmpty(fileTwoLine)) {
            continue;
        }

        // Compare with each line of fileOneContents
        for (int j = 0; j < fileOneSize; j++) {
            string fileOneLine = fileOneContents[j].second;

            // Skip empty lines after removing whitespace
            if (isLineEmpty(fileOneLine)) {
                continue;
            }

            // Remove whitespace from both lines for comparison
            string fileOneLineStripped = removeWhitespace(fileOneLine);
            string fileTwoLineStripped = removeWhitespace(fileTwoLine);

            // If lines match after stripping whitespace
            if (fileOneLineStripped == fileTwoLineStripped) {
                foundMatch = true;
                break;  // Stop checking further lines in fileOne
            }
        }

        // If no match is found, print the difference
        if (!foundMatch) {
            //cout << "DIFF at line " << lineNumber << " in File 2: " << fileTwoLine << endl;
            cout << fileTwoLine << " : " << "File 1 Line " << lineNumber << " - null" << endl;
        }
    }
}

// Function to read files and compare them.
void FileService::diff(string pFileName, string pFileNameTwo) {
    vector<pair<int, string>> fileOneContents;
    vector<pair<int, string>> fileTwoContents;

    // Get filenames from user.
    cout << "Filename: ";
    getline(cin, pFileName);
    cout << "Filename: ";
    getline(cin, pFileNameTwo);

    ifstream inFile, inFileTwo; // File stream variables.
    inFile.open(pFileName); // Opening the first file.
    inFileTwo.open(pFileNameTwo); // Opening the second file.

    if (inFile.fail() || inFileTwo.fail()) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    int lineNumber = 1;
    // Store the contents of both files into vectors with line numbers.
    while (getline(inFile, line)) {
        fileOneContents.push_back(make_pair(lineNumber++, line));
    }
    lineNumber = 1;  // Reset line number for the second file.
    while (getline(inFileTwo, line)) {
        fileTwoContents.push_back(make_pair(lineNumber++, line));
    }

    // Close the files after reading.
    inFile.close();
    inFileTwo.close();

    // CALLS MY JANKY FILE
    compareFilesTwo(fileOneContents, fileTwoContents);
}
