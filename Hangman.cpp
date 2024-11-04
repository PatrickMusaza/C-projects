#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cctype>

using namespace std;

// Predefined list of words
vector<string> wordList = {"teacher", "programming", "hangman", "computer", "science", "game", "project", "algorithm"};

// Function to randomly select a word from the list
string getRandomWord()
{
    srand(static_cast<unsigned int>(time(0))); // Seed for randomness
    int randomIndex = rand() % wordList.size();
    return wordList[randomIndex];
}

// Display the current state of the guessed word
void displayWord(string word, vector<bool> guessedLetters)
{
    for (size_t i = 0; i < word.length(); ++i)
    {
        if (guessedLetters[i])
        {
            cout << word[i] << " ";
        }
        else
        {
            cout << "_ ";
        }
    }
    cout << "\n";
}

// Check if the word is fully guessed
bool isWordGuessed(vector<bool> guessedLetters)
{
    for (bool guessed : guessedLetters)
    {
        if (!guessed)
            return false;
    }
    return true;
}

// Main game function
void playHangman()
{
    string word = getRandomWord();                     // Randomly select a word
    vector<bool> guessedLetters(word.length(), false); // Track guessed letters
    vector<char> incorrectGuesses;                     // Track incorrect guesses
    int attemptsLeft = 6;                              // Maximum incorrect guesses

    cout << "Welcome to Hangman!\n";

    // Game loop
    while (attemptsLeft > 0 && !isWordGuessed(guessedLetters))
    {
        cout << "\nWord: ";
        displayWord(word, guessedLetters);

        cout << "Incorrect Guesses: ";
        for (char ch : incorrectGuesses)
            cout << ch << " ";
        cout << "\nGuesses Left: " << attemptsLeft << "\n";

        // Get player's guess
        char guess;
        cout << "Guess a letter: ";
        cin >> guess;
        guess = tolower(guess); // Convert to lowercase for uniformity

        // Validate input
        if (!isalpha(guess) || guess < 'a' || guess > 'z')
        {
            cout << "Please enter a valid letter.\n";
            continue;
        }

        // Check if the letter has been guessed before
        bool alreadyGuessed = false;
        for (size_t i = 0; i < guessedLetters.size(); ++i)
        {
            if (guessedLetters[i] && word[i] == guess)
            {
                alreadyGuessed = true;
                break;
            }
        }
        for (char incorrect : incorrectGuesses)
        {
            if (incorrect == guess)
            {
                alreadyGuessed = true;
                break;
            }
        }

        if (alreadyGuessed)
        {
            cout << "You already guessed that letter. Try again.\n";
            continue;
        }

        // Check if the guessed letter is in the word
        bool correctGuess = false;
        for (size_t i = 0; i < word.length(); ++i)
        {
            if (word[i] == guess)
            {
                guessedLetters[i] = true;
                correctGuess = true;
            }
        }

        if (correctGuess)
        {
            cout << "Good guess!\n";
        }
        else
        {
            cout << "Incorrect guess.\n";
            incorrectGuesses.push_back(guess);
            --attemptsLeft;
        }
    }

    // End of game messages
    if (isWordGuessed(guessedLetters))
    {
        cout << "\nCongratulations! You guessed the word \"" << word << "\" correctly!\n";
    }
    else
    {
        cout << "\nOut of guesses! The word was \"" << word << "\". Better luck next time!\n";
    }
}

int main()
{
    char playAgain;
    do
    {
        playHangman();
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing Hangman!\n";
    return 0;
}
