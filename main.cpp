#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    bool isAvailable;
public:
    Book(string t, string a, string i) : title(t), author(a), isbn(i), isAvailable(true) {}
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getIsbn() const { return isbn; }
    bool getAvailability() const { return isAvailable; }
    void setAvailability(bool status) { isAvailable = status; }
    void displayBook() const {
        cout << "Title: " << title << "\nAuthor: " << author << "\nISBN: " << isbn;
        cout << (isAvailable ? "\nAvailable\n" : "\nNot Available\n") << endl;
    }
};

class User {
protected:
    string name;

public:
    int userID;
    int id;
    User(string n, int id) : name(n), userID(id) {}
    virtual void borrowBook(Book &book) {
        if (book.getAvailability()) {
            book.setAvailability(false);
            cout << name << " borrowed the book: " << book.getTitle() << endl;
        } else {
            cout << "Sorry, the book is not available.\n";
        }
    }
    virtual void returnBook(Book &book) {
        book.setAvailability(true);
        cout << name << " returned the book: " << book.getTitle() << endl;

    }
    virtual void displayUserInfo() const {
        cout << "User: " << name << "\nID: " << userID << endl;
    }
};

class Student : public User {
public:
    Student(string n, int id) : User(n, id) {}
    void displayUserInfo() const override {
        cout << "Student Name: " << name << "\nID: " << userID << endl;
    }
};

class Teacher : public User {
public:
    Teacher(string n, int id) : User(n, id) {}
    void displayUserInfo() const override {
        cout << "Teacher Name: " << name << "\nID: " << userID << endl;
    }
};

class Library {
private:
    vector<Book> books;
    vector<User *> users;

public:
    void addBook(const Book &book) {
        books.push_back(book);
    }
    void addUser(User *user) {
        users.push_back(user);
    }
    void displayAllBooks() const {
        for (const auto &book : books) {
            book.displayBook();
        }
    }
    User* getUserById(int userId) {
        for (auto user : users) {
            if (user->id == userId) {
                return user;
            }
        }
        return nullptr;
    }

    Book* searchBookByTitle(const string &title) {
        for (auto &book : books) {
            if (book.getTitle() == title) {
                return &book;
            }
        }
        return nullptr;
    }
    void displayAllUsers() const {
        for (const auto &user : users) {
            user->displayUserInfo();
        }
    }
};

void displayMenu() {
    cout << "\n=== Library Management System ===\n";
    cout << "1. Add a Book\n";
    cout << "2. Display All Books\n";
    cout << "3. Search for a Book by Title\n";
    cout << "4. Borrow a Book\n";
    cout << "5. Return a Book\n";
    cout << "6. Add a User\n";
    cout << "7. Display All Users\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    // adding sample data
    Library library;
    Book book1("C++ Programming", "Bjarne Stroustrup", "123456");
    Book book2("Clean Code", "Robert C. Martin", "654321");
    library.addBook(book1);
    library.addBook(book2);
    Student student1("Alice", 101);
    Teacher teacher1("Mr. Smith", 201);

    library.addUser(&student1);
    library.addUser(&teacher1);

    int choice;
    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string author, title, isbn;
                cout << "Enter the book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter the book author: ";
                getline(cin, author);
                cout << "Enter ISBN: ";
                cin >> isbn;
                Book newBook(title, author, isbn);
                library.addBook(newBook);
                cout << "Book added successfully!\n";
                break;
            }
            case 2:
                library.displayAllBooks();
                break;
            case 3: {
                string searchTitle;
                cout << "Enter the book title to search: ";
                cin.ignore();
                getline(cin, searchTitle);
                Book* book = library.searchBookByTitle(searchTitle);
                if (book != nullptr) {
                    book->displayBook();
                } else {
                    cout << "Book not found.\n";
                }
                break;
            }
            case 4: {
                string title;
                int userId;
                cout << "Enter your User ID: ";
                cin >> userId;
                cout << "Enter the book title you want to borrow: ";
                cin.ignore();
                getline(cin, title);

                User* user = library.getUserById(userId);
                if (user != nullptr) {
                    Book* book = library.searchBookByTitle(title);
                    if (book != nullptr) {
                        user->borrowBook(*book);
                    } else {
                        cout << "Book not found.\n";
                    }
                } else {
                    cout << "User not found.\n";
                }
                break;
            }
            case 5: {
                string title;
                int userId;
                cout << "Enter your User ID: ";
                cin >> userId;
                cout << "Enter the book title you want to return: ";
                cin.ignore();
                getline(cin, title);

                User* user = library.getUserById(userId);
                if (user != nullptr) {
                    Book* book = library.searchBookByTitle(title);
                    if (book != nullptr) {
                        user->returnBook(*book);
                    } else {
                        cout << "Book not found.\n";
                    }
                } else {
                    cout << "User not found.\n";
                }
                break;
            }
            case 6: {
                string userName;
                int userID, userType;
                cout << "Enter user name: ";
                cin.ignore();
                getline(cin, userName);
                cout << "Enter user ID: ";
                cin >> userID;
                cout << "Enter user type (1 for Student, 2 for Teacher): ";
                cin >> userType;

                if (userType == 1) {
                    library.addUser(new Student(userName, userID));
                    cout << "Student added successfully!\n";
                } else if (userType == 2) {
                    library.addUser(new Teacher(userName, userID));
                    cout << "Teacher added successfully!\n";
                } else {
                    cout << "Invalid user type.\n";
                }
                break;
            }
            case 7:
                library.displayAllUsers();
                break;
            case 8:
                cout << "Thank you for using the Library Management System. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
