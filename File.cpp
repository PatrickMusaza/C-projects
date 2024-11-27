#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstdio> // For std::rename

using namespace std;

const string PASSWORD = "1234"; // Change this to your desired password
const string META_FILE = "file_meta.dat"; // To store file metadata

// Function to hide a file
void hideFile(const string& filePath) {
    // Check if the file exists
    ifstream checkFile(filePath);
    if (!checkFile) {
        cerr << "File does not exist.\n";
        return;
    }
    checkFile.close();

    // Generate a random name for the file
    srand(static_cast<unsigned int>(time(nullptr)));
    string randomName = to_string(rand()) + ".hidden";

    // Rename the file
    if (rename(filePath.c_str(), randomName.c_str()) != 0) {
        cerr << "Failed to hide file.\n";
        return;
    }

    // Save metadata
    ofstream metaFile(META_FILE, ios::app);
    if (metaFile.is_open()) {
        metaFile << filePath << "|" << randomName << "\n";
        cout << "File hidden successfully.\n";
    } else {
        cerr << "Failed to save metadata.\n";
    }
    metaFile.close();
}

// Function to unhide a file
void unhideFile(const string& filePath) {
    // Require password
    string inputPassword;
    cout << "Enter password to unhide: ";
    cin >> inputPassword;

    if (inputPassword != PASSWORD) {
        cerr << "Incorrect password.\n";
        return;
    }

    // Read metadata to find the original and hidden paths
    ifstream metaFile(META_FILE);
    if (!metaFile.is_open()) {
        cerr << "Failed to read metadata file.\n";
        return;
    }

    string line, originalPath, hiddenPath;
    bool fileFound = false;

    ofstream tempFile("temp_meta.dat");

    while (getline(metaFile, line)) {
        size_t delimiterPos = line.find('|');
        originalPath = line.substr(0, delimiterPos);
        hiddenPath = line.substr(delimiterPos + 1);

        if (hiddenPath == filePath) {
            // Rename the file back to its original name
            if (rename(hiddenPath.c_str(), originalPath.c_str()) != 0) {
                cerr << "Failed to unhide file.\n";
                return;
            }
            cout << "File unhidden successfully: " << originalPath << "\n";
            fileFound = true;
        } else {
            // Preserve metadata for other files
            tempFile << line << "\n";
        }
    }
    metaFile.close();
    tempFile.close();

    // Replace the old metadata file
    remove(META_FILE.c_str()); // Remove the old metadata file
    rename("temp_meta.dat", META_FILE.c_str()); // Rename temp to original

    if (!fileFound) {
        cerr << "File not found in metadata.\n";
    }
}

// Main function
int main() {
    int choice;
    string filePath;

    cout << "1. Hide a File\n";
    cout << "2. Unhide a File\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); // Clear newline from input buffer

    if (choice == 1) {
        cout << "Enter the file path to hide: ";
        getline(cin, filePath);
        hideFile(filePath);
    } else if (choice == 2) {
        cout << "Enter the hidden file path to unhide: ";
        getline(cin, filePath);
        unhideFile(filePath);
    } else {
        cerr << "Invalid choice.\n";
    }

    return 0;
}
