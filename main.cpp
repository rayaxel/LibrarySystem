#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

// Abstract class representing a library entity
class LibraryEntity {
public:
    virtual void addEntity() = 0;
    virtual void removeEntity() = 0;
};

// Base class for person-related information
class Person {
protected:
    string name, memberID, contact;
public:
    // Constructor to initialize person details
    Person(string n, string id, string c) : name(n), memberID(id), contact(c) {}

    // Method to return formatted person details
    virtual string displayDetails() const {
        return name + "," + memberID + "," + contact;
    }

    // Getter for member ID
    string getMemberID() const { return memberID; }
};

// Derived class representing a library member
class Member : public Person {
private:
    vector<string> borrowedBooks; // Stores borrowed books
public:
    // Constructor to initialize member details
    Member(string n, string id, string c) : Person(n, id, c) {}

    // Method to borrow a book
    void borrowBook(const string& bookTitle) { borrowedBooks.push_back(bookTitle); }

    // Method to return a book
    void returnBook(const string& bookTitle) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookTitle);
        if (it != borrowedBooks.end()) borrowedBooks.erase(it);
    }

    // Override method to display member details
    string displayDetails() const override {
        return Person::displayDetails();
    }
};

// Class representing a book
class Book : public LibraryEntity {
private:
    string title, author, isbn;
    int year;
    bool isAvailable; // Availability status
public:
    // Constructor to initialize book details
    Book(string t, string a, string i, int y)
        : title(t), author(a), isbn(i), year(y), isAvailable(true) {}

    // Abstract methods implementation
    void addEntity() override {}
    void removeEntity() override {}

    // Borrowing method
    void borrow() { isAvailable = false; }

    // Returning method
    void returnBook() { isAvailable = true; }

    // Method to display book details
    string displayDetails() const {
        return title + "," + author + "," + isbn + "," + to_string(year);
    }

    // Getters and setters
    string getTitle() const { return title; }
    bool isBookAvailable() const { return isAvailable; }
    void setAvailability(bool status) { isAvailable = status; }
};

// Library class with file handling capabilities
class Library {
private:
    vector<Book> books;
    vector<Member> members;
public:
    // Constructor to load saved data
    Library() { loadBooks(); loadMembers(); }

    // Destructor to save data before exiting
    ~Library() { saveBooks(); saveMembers(); }

    // Method to add a new book
    void addBook(const Book& book) {
        books.push_back(book);
        saveBooks();
    }

    // Method to add a new member
    void addMember(const Member& member) {
        members.push_back(member);
        saveMembers();
    }

    // Display all books
    void displayBooks() const {
        for (const auto& book : books) cout << book.displayDetails() << endl;
    }

    // Display all members
    void displayMembers() const {
        for (const auto& member : members) cout << member.displayDetails() << endl;
    }

    // Borrow a book
    void borrowBook(const string& memberId, const string& title) {
        auto memberIt = find_if(members.begin(), members.end(), [&](const Member& m) { return m.getMemberID() == memberId; });
        auto bookIt = find_if(books.begin(), books.end(), [&](Book& b) { return b.getTitle() == title && b.isBookAvailable(); });
        if (memberIt != members.end() && bookIt != books.end()) {
            bookIt->setAvailability(false);
            memberIt->borrowBook(title);
            saveBooks();
        }
    }

    // Return a book
    void returnBook(const string& memberId, const string& title) {
        auto memberIt = find_if(members.begin(), members.end(), [&](const Member& m) { return m.getMemberID() == memberId; });
        auto bookIt = find_if(books.begin(), books.end(), [&](Book& b) { return b.getTitle() == title; });
        if (memberIt != members.end() && bookIt != books.end()) {
            bookIt->setAvailability(true);
            memberIt->returnBook(title);
            saveBooks();
        }
    }

    // Save book data to file
    void saveBooks() {
        ofstream file("books.csv");
        for (const auto& book : books) file << book.displayDetails() << "\n";
        file.close();
    }

    // Load book data from file
    void loadBooks() {
        ifstream file("books.csv");
        string title, author, isbn, yearStr;
        int year;
        while (getline(file, title, ',') && getline(file, author, ',') && getline(file, isbn, ',') && getline(file, yearStr)) {
            year = stoi(yearStr);
            books.emplace_back(title, author, isbn, year);
        }
        file.close();
    }

    // Save member data to file
    void saveMembers() {
        ofstream file("members.csv");
        for (const auto& member : members) file << member.displayDetails() << "\n";
        file.close();
    }

    // Load member data from file
    void loadMembers() {
        ifstream file("members.csv");
        string name, id, contact;
        while (getline(file, name, ',') && getline(file, id, ',') && getline(file, contact)) {
            members.emplace_back(name, id, contact);
        }
        file.close();
    }
};

// Main menu for user interaction
void showMenu(Library& library) {
    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n2. Add Member\n3. Display Books\n4. Display Members\n5. Borrow Book\n6. Return Book\n7. Exit\nChoose an option: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                string title, author, isbn; int year;
                cout << "Enter title: "; getline(cin, title);
                cout << "Enter author: "; getline(cin, author);
                cout << "Enter ISBN: "; getline(cin, isbn);
                cout << "Enter year: "; cin >> year;
                library.addBook(Book(title, author, isbn, year));
                break;
            }
            case 2: {
                string name, id, contact;
                cout << "Enter name: "; getline(cin, name);
                cout << "Enter ID: "; getline(cin, id);
                cout << "Enter contact: "; getline(cin, contact);
                library.addMember(Member(name, id, contact));
                break;
            }
            case 3: library.displayBooks(); break;
            case 4: library.displayMembers(); break;
            case 5: case 6: case 7: break;
            default: cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 7);
}

int main() {
    Library library;
    showMenu(library);
    return 0;
}
