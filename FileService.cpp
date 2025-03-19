#include "FileService.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

// File Service Constructor.
FileService::FileService() {};


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

vector<int> FileService::compareFiles(const std::vector<std::string>& fileOneContents, const std::vector<std::string>& fileTwoContents) {
    vector<int> diffIndices; // Vector to store indices where differences are found.

    size_t maxSize = std::max(fileOneContents.size(), fileTwoContents.size());

    // Compare the files line by line.
    for (size_t i = 0; i < maxSize; ++i) {
        // Get the lines to compare
        std::string lineOne = (i < fileOneContents.size()) ? fileOneContents[i] : "";
        std::string lineTwo = (i < fileTwoContents.size()) ? fileTwoContents[i] : "";

        // Skip empty lines (lines with only whitespace)
        if (isLineEmpty(lineOne) && isLineEmpty(lineTwo)) {
            continue;  // Skip this line if both lines are empty
        }

        // Remove whitespace from both lines
        std::string strippedLineOne = removeWhitespace(lineOne);
        std::string strippedLineTwo = removeWhitespace(lineTwo);

        // If the lines are different after removing whitespace
        if (strippedLineOne != strippedLineTwo) {
            // Report the difference
            std::cout << "Difference found at line " << i + 1 << ":\n";
            std::cout << "File 1: " << lineOne << "\n";
            std::cout << "File 2: " << lineTwo << "\n";
            diffIndices.push_back(i);  // Add the index of the difference to the vector
        }
    }

    return diffIndices; // Return the vector containing the indices of differences.
}

// Function to read files and compare them.
void FileService::diff(string pFileName, string pFileNameTwo) {
    vector<string> fileOneContents;
    vector<string> fileTwoContents;

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
    // Store the contents of both files into vectors.
    while (getline(inFile, line)) fileOneContents.push_back(line);
    while (getline(inFileTwo, line)) fileTwoContents.push_back(line);

    // Close the files after reading.
    inFile.close();
    inFileTwo.close();

    // Call the compareFiles function to get the differences.
    vector<int> diffIndices = compareFiles(fileOneContents, fileTwoContents);

    // Output the differences (if any).
    if (diffIndices.empty()) {
        cout << "The files are identical." << endl;
    } else {
        cout << "Differences found at indices: ";
        for (int index : diffIndices) {
            cout << index << " ";
        }
        cout << endl;
    }
}

