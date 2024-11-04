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
    string getISBN() const { return ISBN; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    Genre getGenre() const { return genre; }
    bool isCheckedOut() const { return checkedOut; }

    // Check out and check in functions
    void checkOut() { checkedOut = true; }
    void checkIn() { checkedOut = false; }

    // Operator overloads
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

// Class for Patron
class Patron
{
private:
    string userName;
    string cardNumber;
    int owedFees;

public:
    // Constructors
    Patron(string name, string cardNum)
        : userName(name), cardNumber(cardNum), owedFees(0) {}

    // Getter functions
    string getUserName() const { return userName; }
    string getCardNumber() const { return cardNumber; }
    int getOwedFees() const { return owedFees; }

    // Function to check if user owes fees
    bool owesFees() const { return owedFees > 0; }

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
    string date;     // Date can be formatted as a string (e.g., "YYYY-MM-DD")

public:
    // Constructor
    Transaction(Book b, Patron p, string act, string d)
        : book(b), patron(p), activity(act), date(d) {}

    // Function to display transaction details
    void displayTransaction() const
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
    void addBook(Book book) { books.push_back(book); }

    // Function to add a patron to the library
    void addPatron(Patron patron) { patrons.push_back(patron); }

    // Function to check out a book
    void checkOutBook(string isbn, string cardNum)
    {
        // Find the book
        Book *bookPtr = nullptr;
        for (auto &book : books)
        {
            if (book.getISBN() == isbn)
            {
                bookPtr = &book;
                break;
            }
        }

        // Find the patron
        Patron *patronPtr = nullptr;
        for (auto &patron : patrons)
        {
            if (patron.getCardNumber() == cardNum)
            {
                patronPtr = &patron;
                break;
            }
        }

        // Check for errors
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

        // Proceed with checkout
        bookPtr->checkOut();
        transactions.emplace_back(*bookPtr, *patronPtr, "check out", "YYYY-MM-DD");
        cout << "Book checked out successfully.\n";
    }

    // Function to check in a book
    void checkInBook(string isbn)
    {
        // Find the book
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

        // Proceed with check-in
        bookPtr->checkIn();
        transactions.emplace_back(*bookPtr, Patron("", ""), "check in", "YYYY-MM-DD");
        cout << "Book checked in successfully.\n";
    }

    // Function to display patrons who owe fees
    void displayPatronsOwingFees() const
    {
        cout << "Patrons owing fees:\n";
        for (const auto &patron : patrons)
        {
            if (patron.owesFees())
            {
                cout << patron.getUserName() << " owes " << patron.getOwedFees() << " fees.\n";
            }
        }
    }
};

// Dashboard function
void dashboard(Library &library)
{
    int choice;
    while (true)
    {
        cout << "\nLibrary Dashboard\n";
        cout << "1. Add a Book\n";
        cout << "2. Add a Patron\n";
        cout << "3. Check Out a Book\n";
        cout << "4. Check In a Book\n";
        cout << "5. Display Patrons Who Owe Fees\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 6)
            break;

        string isbn, title, author, cardNum;
        int date, genre;
        switch (choice)
        {
        case 1:
            cout << "Enter ISBN: ";
            cin >> isbn;
            cout << "Enter Title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            cout << "Enter Copyright Date: ";
            cin >> date;
            cout << "Enter Genre (0: Fiction, 1: Non-Fiction, 2: Periodical, 3: Biography, 4: Children): ";
            cin >> genre;
            library.addBook(Book(isbn, title, author, date, static_cast<Genre>(genre)));
            cout << "Book added successfully.\n";
            break;

        case 2:
            cout << "Enter User Name: ";
            cin.ignore();
            getline(cin, cardNum);
            cout << "Enter Card Number: ";
            cin >> cardNum;
            library.addPatron(Patron(cardNum, cardNum));
            cout << "Patron added successfully.\n";
            break;

        case 3:
            cout << "Enter ISBN of the book to check out: ";
            cin >> isbn;
            cout << "Enter Patron's Card Number: ";
            cin >> cardNum;
            library.checkOutBook(isbn, cardNum);
            break;

        case 4:
            cout << "Enter ISBN of the book to check in: ";
            cin >> isbn;
            library.checkInBook(isbn);
            break;

        case 5:
            library.displayPatronsOwingFees();
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}

// Main function
int main()
{
    Library library;
    dashboard(library);
    return 0;
}
