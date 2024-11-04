#include <iostream>
#include <vector>
#include <string>

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

// Function to convert genre to string
string genreToString(Genre genre)
{
    switch (genre)
    {
    case FICTION:
        return "Fiction";
    case NON_FICTION:
        return "Non-Fiction";
    case PERIODICAL:
        return "Periodical";
    case BIOGRAPHY:
        return "Biography";
    case CHILDREN:
        return "Children";
    default:
        return "Unknown";
    }
}

// Class for Book
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

    // Getter functions
    string getISBN() { return ISBN; }
    string getTitle() { return title; }
    string getAuthor() { return author; }
    Genre getGenre() { return genre; }
    bool isCheckedOut() { return checkedOut; }

    // Check out and check in functions
    void checkOut() { checkedOut = true; }
    void checkIn() { checkedOut = false; }

    // Operator overloads
    bool operator==(const Book &other) const { return ISBN == other.ISBN; }
    bool operator!=(const Book &other) const { return !(*this == other); }

    friend ostream &operator<<(ostream &os, const Book &b)
    {
        os << "Title: " << b.title << "\n"
           << "Author: " << b.author << "\n"
           << "ISBN: " << b.ISBN << "\n"
           << "Genre: " << genreToString(b.genre) << "\n";
        return os;
    }
};

// Class for Patron
class Patron
{
private:
    string userName;
    string cardNumber;
    int owedFees;

public:
    // Constructors
    Patron(string name, string cardNum, int fees = 0)
        : userName(name), cardNumber(cardNum), owedFees(fees) {}

    // Getter functions
    string getUserName() { return userName; }
    string getCardNumber() { return cardNumber; }
    int getOwedFees() { return owedFees; }

    // Function to check if user owes fees
    bool owesFees() { return owedFees > 0; }

    // Setter for fees
    void setFees(int fees) { owedFees = fees; }
};

// Class for Transaction
class Transaction
{
private:
    Book book;
    Patron patron;
    string activity; // "check out" or "check in"
    string date;

public:
    // Constructor
    Transaction(Book b, Patron p, string act, string d)
        : book(b), patron(p), activity(act), date(d) {}

    // Function to display transaction details
    void displayTransaction()
    {
        cout << "Transaction: " << activity << "\n"
             << "Book: " << book.getTitle() << "\n"
             << "Patron: " << patron.getUserName() << "\n"
             << "Date: " << date << "\n";
    }
};

// Class for Library
class Library
{
private:
    vector<Book> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;

public:
    // Function to add a book to the library
    void addBook(Book book)
    {
        books.push_back(book);
    }

    // Function to add a patron to the library
    void addPatron(Patron patron)
    {
        patrons.push_back(patron);
    }

    // Function to check out a book
    void checkOutBook(string isbn, string cardNum)
    {
        Book *bookPtr = nullptr;
        for (auto &book : books)
        {
            if (book.getISBN() == isbn)
            {
                bookPtr = &book;
                break;
            }
        }

        Patron *patronPtr = nullptr;
        for (auto &patron : patrons)
        {
            if (patron.getCardNumber() == cardNum)
            {
                patronPtr = &patron;
                break;
            }
        }

        if (!bookPtr)
        {
            cout << "Error: Book with ISBN " << isbn << " not found.\n";
            return;
        }
        if (!patronPtr)
        {
            cout << "Error: Patron with card number " << cardNum << " not found.\n";
            return;
        }
        if (patronPtr->owesFees())
        {
            cout << "Error: Patron " << patronPtr->getUserName() << " owes fees.\n";
            return;
        }
        if (bookPtr->isCheckedOut())
        {
            cout << "Error: Book is already checked out.\n";
            return;
        }

        bookPtr->checkOut();
        string date = "YYYY-MM-DD"; // Placeholder for the actual date
        transactions.emplace_back(*bookPtr, *patronPtr, "check out", date);
        cout << "Book checked out successfully.\n";
    }

    // Function to check in a book
    void checkInBook(string isbn)
    {
        Book *bookPtr = nullptr;
        for (auto &book : books)
        {
            if (book.getISBN() == isbn)
            {
                bookPtr = &book;
                break;
            }
        }

        if (!bookPtr)
        {
            cout << "Error: Book with ISBN " << isbn << " not found.\n";
            return;
        }
        if (!bookPtr->isCheckedOut())
        {
            cout << "Error: Book is not checked out.\n";
            return;
        }

        bookPtr->checkIn();
        string date = "YYYY-MM-DD"; // Placeholder for the actual date
        transactions.emplace_back(*bookPtr, Patron("", ""), "check in", date);
        cout << "Book checked in successfully.\n";
    }

    // Function to display patrons who owe fees
    void displayPatronsOwingFees()
    {
        cout << "Patrons owing fees:\n";
        for (auto &patron : patrons)
        {
            if (patron.owesFees())
            {
                cout << patron.getUserName() << " owes " << patron.getOwedFees() << " fees.\n";
            }
        }
    }
};

// Main function
int main()
{
    Library library;

    // Adding sample books
    library.addBook(Book("12345", "The Great Gatsby", "F. Scott Fitzgerald", 1925, FICTION));
    library.addBook(Book("67890", "A Brief History of Time", "Stephen Hawking", 1988, NON_FICTION));
    library.addBook(Book("54321", "The Diary of a Young Girl", "Anne Frank", 1947, BIOGRAPHY));

    // Adding sample patrons
    library.addPatron(Patron("Alice Smith", "P001"));
    library.addPatron(Patron("Bob Johnson", "P002"));
    library.addPatron(Patron("Charlie Brown", "P003"));

    // Sample transactions
    library.checkOutBook("12345", "P001");
    library.checkInBook("12345");
    library.checkOutBook("67890", "P002");
    library.checkOutBook("54321", "P003");

    // Display patrons owing fees
    library.displayPatronsOwingFees();

    return 0;
}
