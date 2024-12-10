#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

const string folderPath = "C:\\Users\\user\\OneDrive\\Documentos\\test";  // Replace with your folder path
const string hiddenFolderSuffix = "123";  // Suffix to append to folder name

// Function to hide the folder by changing its attributes and renaming it
void hideFolder() {
    // Change the folder attributes to Hidden and System
    SetFileAttributes(folderPath.c_str(), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
    
    // Create the new folder path with "123" appended to the original name
    string newFolderPath = folderPath + hiddenFolderSuffix;
    
    // Rename the folder to hide it
    if (MoveFile(folderPath.c_str(), newFolderPath.c_str())) {
        cout << "Folder has been hidden successfully." << endl;
    } else {
        cout << "Failed to hide folder." << endl;
    }
}

// Function to restore the folder from the hidden state
bool restoreFolder() {
    // Read the number from the text file on the desktop
    ifstream file("C:\\Users\\user\\Desktop\\unhide.txt");
    if (!file.is_open()) {
        cout << "Failed to open unhide.txt" << endl;
        return false;
    }
    
    int userNumber;
    file >> userNumber;
    file.close();
    
    // Check if the user's number is correct (password * 2)
    int correctNumber = 123 * 2;  // Example: password is 123
    if (userNumber == correctNumber) {
        // Restore the folder by renaming it back to the original name
        string newFolderPath = folderPath + hiddenFolderSuffix;
        if (MoveFile(newFolderPath.c_str(), folderPath.c_str())) {
            // Remove the hidden and system attributes
            SetFileAttributes(folderPath.c_str(), FILE_ATTRIBUTE_NORMAL);
            cout << "Folder has been restored successfully." << endl;
            return true;
        } else {
            cout << "Failed to restore folder." << endl;
            return false;
        }
    } else {
        cout << "Incorrect number in unhide.txt. Folder cannot be restored." << endl;
        return false;
    }
}

int main() {
    int choice;
    
    cout << "1. Hide Folder" << endl;
    cout << "2. Restore Folder" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    
    if (choice == 1) {
        hideFolder();
    } else if (choice == 2) {
        restoreFolder();
    } else {
        cout << "Invalid choice!" << endl;
    }
    
    return 0;
}
