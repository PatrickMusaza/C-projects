#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <algorithm>

using namespace std;

// Enum for Genre
enum Genre
{
    FICTION,
    NON_FICTION,
    PERIODICAL,
    BIOGRAPHY,
    CHILDREN
};

// Function to convert Genre to string
string genreToString(Genre genre)
{
    switch (genre)
    {
    case FICTION: return "Fiction";
    case NON_FICTION: return "Non-Fiction";
    case PERIODICAL: return "Periodical";
    case BIOGRAPHY: return "Biography";
    case CHILDREN: return "Children";
    default: return "Unknown";
    }
}

// Function to get current date as string
string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-" << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-" << setw(2) << ltm->tm_mday;
    return ss.str();
}

// Book Class
class Book
{
private:
    string ISBN;
    string title;
    string author;
    int copyrightDate;
    bool checkedOut;
    Genre genre;

public:
    // Constructors
    Book(string isbn, string t, string a, int date, Genre g)
        : ISBN(isbn), title(t), author(a), copyrightDate(date), checkedOut(false), genre(g) {}
    Book() : ISBN(""), title(""), author(""), copyrightDate(0), checkedOut(false), genre(FICTION) {}

    // Getters
    string getISBN() const { return ISBN; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getCopyrightDate() const { return copyrightDate; }
    Genre getGenre() const { return genre; }
    bool isCheckedOut() const { return checkedOut; }

    // Check Out / Check In
    void checkOut() { checkedOut = true; }
    void checkIn() { checkedOut = false; }

    // Overloaded Operators
    bool operator==(const Book &other) const { return ISBN == other.ISBN; }
    bool operator!=(const Book &other) const { return !(*this == other); }

    friend ostream &operator<<(ostream &os, const Book &book)
    {
        os << "Title: " << book.title << "\n"
           << "Author: " << book.author << "\n"
           << "ISBN: " << book.ISBN << "\n"
           << "Genre: " << genreToString(book.genre) << "\n";
        return os;
    }
};

// Patron Class
class Patron
{
private:
    string userName;
    string cardNumber;
    int owedFees;

public:
    // Constructor
    Patron(string name, string cardNum)
        : userName(name), cardNumber(cardNum), owedFees(0) {}

    // Getters
    string getUserName() const { return userName; }
    string getCardNumber() const { return cardNumber; }
    int getOwedFees() const { return owedFees; }

    // Check Fees
    bool owesFees() const { return owedFees > 0; }

    // Set Fees
    void setFees(int fees) { owedFees = fees; }
};

// Transaction Class
class Transaction
{
private:
    Book book;
    Patron patron;
    string activity; // "Check Out" or "Check In"
    string date;

public:
    // Constructor
    Transaction(Book b, Patron p, string act, string d)
        : book(b), patron(p), activity(act), date(d) {}

    // Display Transaction
    void displayTransaction() const
    {
        cout << "Transaction: " << activity << "\n"
             << "Book: " << book.getTitle() << "\n"
             << "Patron: " << patron.getUserName() << "\n"
             << "Date: " << date << "\n";
    }
};

// Library Class
class Library
{
private:
    vector<Book> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;

public:
    // Add Book
    void addBook(const Book &book)
    {
        books.push_back(book);
        cout << "Book added successfully!\n";
        clearScreen();
    }

    // Add Patron
    void addPatron(const Patron &patron)
    {
        patrons.push_back(patron);
        cout << "Patron added successfully!\n";
        clearScreen();
    }

    // Check Out Book
    void checkOutBook(const string &isbn, const string &cardNumber)
    {
        auto bookIt = find_if(books.begin(), books.end(), [&isbn](const Book &b) { return b.getISBN() == isbn; });
        if (bookIt == books.end())
        {
            cout << "Book not found in library!\n";
            return;
        }

        auto patronIt = find_if(patrons.begin(), patrons.end(), [&cardNumber](const Patron &p) { return p.getCardNumber() == cardNumber; });
        if (patronIt == patrons.end())
        {
            cout << "Patron not found in library!\n";
            return;
        }

        if (patronIt->owesFees())
        {
            cout << "Patron owes fees. Cannot check out book!\n";
            return;
        }

        if (bookIt->isCheckedOut())
        {
            cout << "Book is already checked out!\n";
            return;
        }

        bookIt->checkOut();
        transactions.emplace_back(*bookIt, *patronIt, "Check Out", getCurrentDate());
        cout << "Book checked out successfully!\n";
        clearScreen();
    }

    // List Patrons Who Owe Fees
    vector<string> listPatronsWithFees() const
    {
        vector<string> patronsWithFees;
        for (const auto &patron : patrons)
        {
            if (patron.owesFees())
            {
                patronsWithFees.push_back(patron.getUserName());
            }
        }
        return patronsWithFees;
    }

    // Clear Screen
    void clearScreen()
    {
        cout << string(100, '\n');
    }
};

// Main Function
int main()
{
    Library library;

    // Main program loop
    while (true)
    {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Add Patron\n";
        cout << "3. Check Out Book\n";
        cout << "4. List Patrons with Fees\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        // Clear the screen (cross-platform workaround)
        system("CLS");  // On Windows
        // system("clear");  // On UNIX-based systems

        switch (choice)
        {
        case 1: {
            string isbn, title, author;
            int copyrightDate, genreChoice;

            cout << "Enter ISBN: ";
            cin >> isbn;
            cout << "Enter Title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            cout << "Enter Copyright Date: ";
            cin >> copyrightDate;
            cout << "Enter Genre (0: Fiction, 1: Non-Fiction, 2: Periodical, 3: Biography, 4: Children): ";
            cin >> genreChoice;

            Genre genre = static_cast<Genre>(genreChoice);
            library.addBook(Book(isbn, title, author, copyrightDate, genre));
            break;
        }
        case 2: {
            string name, cardNumber;

            cout << "Enter Patron Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Patron Card Number: ";
            getline(cin, cardNumber);

            library.addPatron(Patron(name, cardNumber));
            break;
        }
        case 3: {
            string isbn, cardNumber;

            cout << "Enter ISBN of Book to Check Out: ";
            cin >> isbn;
            cout << "Enter Patron Card Number: ";
            cin >> cardNumber;

            library.checkOutBook(isbn, cardNumber);
            break;
        }
        case 4: {
            vector<string> patronsWithFees = library.listPatronsWithFees();
            if (patronsWithFees.empty())
            {
                cout << "No patrons owe fees.\n";
            }
            else
            {
                cout << "Patrons owing fees:\n";
                for (const string &name : patronsWithFees)
                {
                    cout << "- " << name << "\n";
                }
            }
            break;
        }
        case 5:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
