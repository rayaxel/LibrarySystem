# Library Management System

## Description
This is a C++ based Library Management System that provides a command-line interface for managing books and library members. The system allows for basic library operations such as adding books, registering members, handling book borrowing and returns, and maintains persistent data storage using CSV files.

## Features
- Book management (add, display)
- Member management (register, display)
- Book borrowing and return system
- Persistent data storage using CSV files
- Object-oriented design with inheritance and polymorphism

## Technical Details
### Class Structure
- `LibraryEntity`: Abstract base class for library entities
- `Person`: Base class for person-related information
- `Member`: Derived class for library members
- `Book`: Class representing library books
- `Library`: Main class handling all library operations

### File Storage
The system uses two CSV files for data persistence:
- `books.csv`: Stores book information (title, author, ISBN, year)
- `members.csv`: Stores member information (name, ID, contact)

## How to Use
1. Compile the program using a C++ compiler
2. Run the executable
3. Use the menu-driven interface to:
   - Add new books to the library
   - Register new members
   - View all books in the collection
   - View all registered members
   - Process book borrowings
   - Handle book returns

## Menu Options
1. Add Book: Add a new book to the library
2. Add Member: Register a new library member
3. Display Books: View all books in the library
4. Display Members: View all registered members
5. Borrow Book: Process a book borrowing
6. Return Book: Process a book return


## Data Format
### Books
Books are stored with the following information:
- Title
- Author
- ISBN
- Publication Year
- Availability Status

### Members
Members are stored with the following information:
- Name
- Member ID
- Contact Information
- List of borrowed books

## Limitations
- Command-line interface only
- Single-user operation
- No authentication system
- Basic error handling

