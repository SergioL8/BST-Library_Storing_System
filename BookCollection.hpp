#ifndef BookCollection_H__
#define BookCollection_H__
#include <iostream>
using namespace std;

struct Book {
    string bookName;
    string author;
    double rating;
    Book* left = NULL;
    Book* right = NULL;

    // constructor
    Book(string bn, string a, double r) {
        bookName = bn;
        author = a;
        rating = r;
    }
};


class BookCollection {
    private:
        Book* root;

    public:
        BookCollection(); // default constructor
        ~BookCollection(); // destructor

        void showBookCollection();
        void addBook(string bookName, string author, double rating);
        void showBook(string bookName);
        void showBooksByAuthor(string author);
        void showHighestRatedBooks();
        int getHeightOfBookCollection();
        void removeBook(string bookName);

        void showBookCollectionHelper(Book* currentBook);
        Book* addBookHelper(Book* currentBook, Book* newBook);
        Book* showBookHelper(Book* currentBook, string bookName);
        void showBooksByAuthorHelper(Book* currentBook, string author);
        double findHighestRatedBooksHelper(Book* currentBook, double highest_rate);
        void showHighestRatedBooksHelper(Book* currentBook, double rate);
        int getHeightOfBookCollectionHelper(Book* currentBook);
        void destroyCollection(Book* currentBook);
        void removeBookhelper(Book* &bookName, string foundBook);
        Book* searchMinHelper(Book* currentBook);

};


#endif