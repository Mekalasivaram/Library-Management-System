#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;

    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        isIssued = false;
    }

    void display() {
        cout << "ID: " << id << ", Title: " << title
             << ", Author: " << author
             << ", Status: " << (isIssued ? "Issued" : "Available") << endl;
    }
};

// Base class
class Person {
public:
    string name;
    int rollOrId;

    virtual void getDetails() {
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter ID/Roll number: ";
        cin >> rollOrId;
    }
};

// Derived classes
class Student : public Person {
public:
    void getDetails() {
        cout << "Enter Student Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Roll Number: ";
        cin >> rollOrId;
    }
};

class Teacher : public Person {
public:
    void getDetails() {
        cout << "Enter Teacher Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Teacher ID: ";
        cin >> rollOrId;
    }
};

class Library {
    vector<Book> books;

public:
    void addBook() {
        int id;
        string title, author;
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
        books.push_back(Book(id, title, author));
        cout << "Book added successfully!\n";
    }

    void displayBooks() {
        for (auto &book : books) {
            book.display();
        }
    }

    void issueBook() {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;
        for (auto &book : books) {
            if (book.id == id) {
                if (!book.isIssued) {
                    cout << "Issue to: 1.Student 2.Teacher : ";
                    int choice;
                    cin >> choice;
                    Person *p;
                    if (choice == 1)
                        p = new Student();
                    else
                        p = new Teacher();
                    p->getDetails();

                    book.isIssued = true;
                    cout << "Book issued successfully!\n";

                    // Save record in file
                    ofstream fout("issued_books.txt", ios::app);
                    fout << "BookID: " << id << ", Title: " << book.title
                         << ", Issued to: " << p->name << ", ID: " << p->rollOrId << endl;
                    fout.close();

                    delete p;
                } else {
                    cout << "Book already issued.\n";
                }
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;
        for (auto &book : books) {
            if (book.id == id) {
                if (book.isIssued) {
                    book.isIssued = false;
                    cout << "Book returned successfully!\n";
                } else {
                    cout << "Book was not issued.\n";
                }
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void viewIssuedRecords() {
        ifstream fin("issued_books.txt");
        string line;
        cout << "\n--- Issued Books Records ---\n";
        while (getline(fin, line)) {
            cout << line << endl;
        }
        fin.close();
    }
};

int main() {
    Library lib;
    int choice;

    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. View Issued Records\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.displayBooks(); break;
            case 3: lib.issueBook(); break;
            case 4: lib.returnBook(); break;
            case 5: lib.viewIssuedRecords(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}