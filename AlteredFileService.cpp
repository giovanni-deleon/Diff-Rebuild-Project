#include "FileService.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <utility>  // For std::pair
#include <iomanip>
using namespace std;

// Constructor for the FileService class.
FileService::FileService() {}

// Helper function to remove all whitespace characters from a string.
// This function iterates over each character and excludes whitespace characters.
string FileService::removeWhitespace(const std::string& str) {
    string result;
    for (char c : str) {
        if (!isspace(c)) {  // Check if the character is not a whitespace (space, tab, newline, etc.)
            result.push_back(c);
        }
    }
    return result;
}

// Function to check if a line is empty after removing whitespace.
// It calls removeWhitespace to remove whitespace and checks if the result is empty.
bool FileService::isLineEmpty(const std::string& line) {
    return removeWhitespace(line).empty();
}

// Function that compares the lines from two files and displays the differences.
void FileService::compareFilesTwo(const vector<pair<int, string>>& fileOneContents, const vector<pair<int, string>>& fileTwoContents) {
    int fileOneSize = fileOneContents.size();  // Get the number of lines in the first file.
    int fileTwoSize = fileTwoContents.size();  // Get the number of lines in the second file.

    // Compare lines in fileOneContents with fileTwoContents
    for (int i = 0; i < fileOneSize; i++) {
        string fileOneLine = fileOneContents[i].second;  // Get the content of the line.
        int lineNumber = fileOneContents[i].first;  // Get the line number.
        bool foundMatch = false;  // Boolean flag to check if a match is found.

        // Skip empty lines after removing whitespace.
        if (isLineEmpty(fileOneLine)) {
            continue;
        }

        // Compare with each line of fileTwoContents
        for (int j = 0; j < fileTwoSize; j++) {
            string fileTwoLine = fileTwoContents[j].second;

            // Skip empty lines after removing whitespace.
            if (isLineEmpty(fileTwoLine)) {
                continue;
            }

            // Remove whitespace from both lines for comparison.
            string fileOneLineStripped = removeWhitespace(fileOneLine);
            string fileTwoLineStripped = removeWhitespace(fileTwoLine);

            // If lines match after stripping whitespace.
            if (fileOneLineStripped == fileTwoLineStripped) {
                foundMatch = true;
                break;  // No need to check further lines in fileTwo, since we found a match.
            }
        }

        // If no match is found, print the difference (File 1 line with no corresponding line in File 2).
        if (!foundMatch) {
            cout << fileOneLine << " : " << "File 2 Line " << lineNumber << " - null" << endl;
        }
    }

    // Now compare lines in fileTwoContents with fileOneContents.
    for (int i = 0; i < fileTwoSize; i++) {
        string fileTwoLine = fileTwoContents[i].second;
        int lineNumber = fileTwoContents[i].first;
        bool foundMatch = false;

        // Skip empty lines after removing whitespace.
        if (isLineEmpty(fileTwoLine)) {
            continue;
        }

        // Compare with each line of fileOneContents.
        for (int j = 0; j < fileOneSize; j++) {
            string fileOneLine = fileOneContents[j].second;

            // Skip empty lines after removing whitespace.
            if (isLineEmpty(fileOneLine)) {
                continue;
            }

            // Remove whitespace from both lines for comparison.
            string fileOneLineStripped = removeWhitespace(fileOneLine);
            string fileTwoLineStripped = removeWhitespace(fileTwoLine);

            // If lines match after stripping whitespace.
            if (fileOneLineStripped == fileTwoLineStripped) {
                foundMatch = true;
                break;  // No need to check further lines in fileOne, since we found a match.
            }
        }

        // If no match is found, print the difference (File 2 line with no corresponding line in File 1).
        if (!foundMatch) {
            cout << fileTwoLine << " : " << "File 1 Line " << lineNumber << " - null" << endl;
        }
    }

    cout << endl;
    // Call fancyDiff to display a more detailed diff of the files.
    fancyDiff(6, 25, 25, fileOneContents, fileTwoContents);

} // END OF DIFF FUNCTION

// Function to display a more structured "fancy" diff, with indices and content from both files.
void FileService::fancyDiff(int pIndex, int pFileOneLineAmount, int pFileTwoLineAmount, const vector<pair<int, string>>& fileOneContents, const vector<pair<int, string>>& fileTwoContents) {
    // Print header line for the diff table.
    for (int i = 0; i <= 74; i++) {
        cout << "*";
    }
    cout << "\n|" << setw(pIndex) << "Index" << " | ";
    cout << "File One" << setw(pFileOneLineAmount) << "| ";
    cout << "File Two" << setw(pFileTwoLineAmount) << "| " << endl;
    for (int i = 0; i <= 74; i++) {
        cout << "*";
    }

    // Sidebar Indices, print index for each line in the file.
    int sideBarAmount = max(fileOneContents.size(), fileTwoContents.size());

    cout << endl;
    for (int j = 0; j < sideBarAmount; j++) {
        if (j > 8) {
            cout << "|   " << j + 1 << "  |";  // For indices greater than 9, adjust alignment.
        }
        else {
            cout << "|   " << j + 1 << "   |";  // For single-digit indices, adjust alignment.
        }

        // Print lines from File One.
        if (j < fileOneContents.size()) {
            cout << left << setw(pFileOneLineAmount + 6) << fileOneContents[j].second;
        }
        else {
            cout << setw(pFileOneLineAmount + 6) << "--null--";  // If no line exists, print "--null--".
        }

        cout << " | ";

        // Print lines from File Two.
        if (j < fileTwoContents.size()) {
            cout << left << setw(pFileTwoLineAmount + 6) << fileTwoContents[j].second;
        }
        else {
            cout << setw(pFileTwoLineAmount + 6) << "--null--";  // If no line exists, print "--null--".
        }

        cout << "|" << endl;
    }

    // Print footer line for the diff table.
    for (int i = 0; i <= 74; i++) {
        cout << "*";
    }
}

// Function to read the contents of two files and compare them.
void FileService::diff(string pFileName, string pFileNameTwo) {
    vector<pair<int, string>> fileOneContents;
    vector<pair<int, string>> fileTwoContents;

    // Get filenames from user.
    cout << "Filename: ";
    getline(cin, pFileName);  // Read the first filename from input.
    cout << "Filename: ";
    getline(cin, pFileNameTwo);  // Read the second filename from input.

    ifstream inFile, inFileTwo;  // Declare file stream objects for both files.
    inFile.open(pFileName);  // Open the first file.
    inFileTwo.open(pFileNameTwo);  // Open the second file.

    if (inFile.fail() || inFileTwo.fail()) {  // Check if files failed to open.
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    int lineNumber = 1;
    // Read the contents of the first file and store in fileOneContents with line numbers.
    while (getline(inFile, line)) {
        fileOneContents.push_back(make_pair(lineNumber++, line));
    }
    lineNumber = 1;  // Reset line number for the second file.
    // Read the contents of the second file and store in fileTwoContents with line numbers.
    while (getline(inFileTwo, line)) {
        fileTwoContents.push_back(make_pair(lineNumber++, line));
    }

    // Close the files after reading.
    inFile.close();
    inFileTwo.close();

    // Call the function to compare the contents of both files.
    cout << endl;
    compareFilesTwo(fileOneContents, fileTwoContents);
}
