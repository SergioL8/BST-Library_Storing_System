#include "BookCollection.hpp"
#include <iostream>
using namespace std;

/*
 * Purpose: Set the root of the tree to NULL
 * @param none
 * @return none
 */
BookCollection::BookCollection() {
    root = nullptr;
}

/*
 * Purpose: Delete the entire tree
 * @param none
 * @return none
 */
BookCollection::~BookCollection() {
    destroyCollection(root);
}

/*
 * Purpose: Traverse through the entire binary from a given book deleting all nodes
 * @param currentBook
 * @return none
 */
void BookCollection::destroyCollection(Book* currentBook)
{
    if (currentBook != nullptr) // if we are not at the end of the tree
    {
        destroyCollection(currentBook->left); // traverse trough left
        destroyCollection(currentBook->right); // traverse thorugh right

        delete currentBook; // delete the current book
        currentBook = nullptr;
    }
}



/*
 * Purpose: Add a new book to the tree, here is where the real work is being done
 * @param (Book*) currentBook, (Book*) newBook
 * @return Book*
 */
Book* BookCollection::addBookHelper(Book* currentBook, Book* newBook) {
    // if we have reached the end of the tree, then return newBook, which will assign newBook to either the previous current book right or left
    // or if the tree is empty (as currentBook is initially root)
    if (currentBook == nullptr) {
        return newBook;
    }

    // the compare function returns > 0 if the first string is greater than the second string
    int strComp = currentBook->bookName.compare(newBook->bookName);

    // if strComp is greater than 0, then currentBook is greater than newBook book and we should traverse to the left
    if (strComp > 0) {
        currentBook->left = addBookHelper(currentBook->left, newBook);
    } else if (strComp < 0) { // if strComp is smaller than 0, then newBook is greater than currentBook and should move to the right
        currentBook->right = addBookHelper(currentBook->right, newBook);
    }
    // this return is necessary because (unless assigning the new node, it is what it's  being assigned to the previous currentBook left or right)
    return currentBook; 
}

/*
 * Purpose: Add a new book to the tree
 * @param (s)bookName, (s)author, (d)rating
 * @return none
 */
void BookCollection::addBook(string bookName, string author, double rating) {

    Book* newBook = new Book(bookName, author, rating); // create the new book that will be added
    root = addBookHelper(root, newBook); // set the root to the new tree
}



/*
 * Purpose: Traverse through the entire tree printing the contents
 * @param currentBook
 * @return none
 */
void BookCollection::showBookCollectionHelper(Book* currentBook) {
    
    // check that the tree is not empty
    if (root == nullptr) {
        cout << "Collection is empty." << endl;
        return;
    } else if (currentBook != nullptr) { // check that we haven't reached the end of the tree
        showBookCollectionHelper(currentBook->left); // traverse all the way to the left until end has been reacheds
        cout << "BOOK: " << currentBook->bookName << " BY: " << currentBook->author << " RATING: " << currentBook->rating << endl; // print the book
        showBookCollectionHelper(currentBook->right); // traverse to the right node of the right node
        // the order of left and right makes the books to be printed in alphabetical order
    }
}   

/*
 * Purpose: Traverse through the entire tree printing the contents (calls showBookCollectionHelper)
 * @param none
 * @return none
 */
void BookCollection::showBookCollection() {
    showBookCollectionHelper(root);
}



/*
 * Purpose: Fidn a book from a bookName and print it's information
 * @param (Book)currentBook, (s)bookName
 * @return Book
 */
Book* BookCollection::showBookHelper(Book* currentBook, string bookName)
{
    // the book doesn't exist in the tree or the tree is empty
    if (currentBook == nullptr) {
        return nullptr;
    }
    // compare the strings
    int strComp = currentBook->bookName.compare(bookName); // strComp will be > 0 if currentBook->bookName is greater than bookName

    // if you have found the book
    if (strComp == 0) {
        return currentBook;
    }
    // if it has to go to the right
    if (strComp < 0) {
        return showBookHelper(currentBook->right, bookName);
    }
    // if it has to go to the left
    if (strComp > 0) {
        return showBookHelper(currentBook->left, bookName);
    } 
    return nullptr;      
}

/*
 * Purpose: Fidn a book from a bookName and print it's information
 * @param (s)bookName
 * @return none
 */
void BookCollection::showBook(string bookName) {

    // use the helper to find if the book with bookName exists
    Book* printBook = showBookHelper(root, bookName);

    // the book doesn't exist in the tree
    if (printBook == nullptr) {
        cout << endl;
        cout << "Book not found." << endl;
        return;
    }
    else
    {
        cout << endl;
        cout << "Book:" << endl;
        cout << "==================" << endl;
        cout << "Name :" << printBook->bookName << endl;
        cout << "Author :" << printBook->author << endl;
        cout << "Rating :" << printBook->rating << endl;
    }
}



/*
 * Purpose: Find all the books given an author
 * @param (s)author
 * @return none
 */
void BookCollection::showBooksByAuthorHelper(Book* currentBook, string author)
{
    // check that the tree is not empty
    if (root == nullptr) {
        cout << "No books given the author because the collection is empty." << endl;
        return;
    }

    // if we are not at the end of the tree
    if (currentBook != nullptr) {
        // traverse all the way to the right (no need to compare anything before traversing because we have to go over all nodes)
        showBooksByAuthorHelper(currentBook->right, author);
        if (currentBook->author.compare(author) == 0) { // check if the book we are currently in is written by the given author
            cout << currentBook->bookName << " RATING: " << currentBook->rating << endl;
        }
        // traverse throught to the left node of the current node
        showBooksByAuthorHelper(currentBook->left, author);
    }
    return;
}

/*
 * Purpose: Find all the books given an author
 * @param (s)author
 * @return none
 */
void BookCollection::showBooksByAuthor(string author) {
    cout << endl;
    cout << "========== Books By: " << author << " =========="<< endl << endl;
    showBooksByAuthorHelper(root, author);
}



/*
 * Purpose: find out what is the higest rating of the entire collection
 * @param (Book) currentBook, (d) higest_rate
 * @return (d)rating
 */
double BookCollection::findHighestRatedBooksHelper(Book* currentBook, double highest_rate) {

    if (currentBook != nullptr) { // if we haven't gotten to the end of the tree
        highest_rate = findHighestRatedBooksHelper(currentBook->right, highest_rate); // traverse through all the right nodes
        if (currentBook->rating > highest_rate) { // check if there is a new highest rating
            highest_rate = currentBook->rating;
        }
        highest_rate = findHighestRatedBooksHelper(currentBook->left, highest_rate); // traverse through the left node of the current book
    }
    return highest_rate;

}

/*
 * Purpose: Given a rate, find which books have that same rating
 * @param (Book) currentBook, (d)rate
 * @return none
 */
void BookCollection::showHighestRatedBooksHelper(Book* currentBook, double rate) {
    
    // if we haven't gotten to the end of the tree
    if (currentBook != nullptr) {
        showHighestRatedBooksHelper(currentBook->right, rate); // traverse all the way to the right 
        if (currentBook->rating == rate) { // check if the current book has the highest grade
            cout << currentBook->bookName << " BY: " << currentBook->author << endl;
        }
        showHighestRatedBooksHelper(currentBook->left, rate); // traverse to the left of the current book
    }
    return;
}

/*
 * Purpose: Find all books that have the highest rating of the collection by first finding out the highest rating
 * and then by getting all the books that have that same rating
 * @param node
 * @return none
 */
void BookCollection::showHighestRatedBooks() {

    // check that the collection is not empty
    if (root == nullptr) {
        cout << "Collection is empty." << endl;
        return;
    }

    // find out which is the highest rating of the collection
    double rate = findHighestRatedBooksHelper(root, root->rating); // pass the root and an initial rating (the root rating)
    cout << "Highest Rating: " << rate << endl;
    showHighestRatedBooksHelper(root, rate); // find out which are the books that have that highest rating
}



/*
 * Purpose: Find out the height of the tree
 * @param (Book)currentBook
 * @return (i)heightOfCollection
 */
int BookCollection::getHeightOfBookCollectionHelper(Book* currentBook)
{
    int left_height = 0;
    int right_height = 0;
    if (currentBook == nullptr) { // as we first traverse to the left, once we have ended that recurssion, return that height
        return left_height;
    }
    else { // if we are not at the end of the tree yet
        left_height = getHeightOfBookCollectionHelper(currentBook->left); // traverse all the way to the left
        right_height = getHeightOfBookCollectionHelper(currentBook->right); // traverse to the right of the currentBook
        if (left_height >= right_height) { // compare the different heights
            return left_height + 1; // we need to add 1 because we are counting as 0 the root
        }
        else {
            return right_height + 1;
        }
    }
}

/*
 * Purpose: Find out the height of the tree
 * @param none
 * @return (i) heightOfTree
 */
int BookCollection::getHeightOfBookCollection() {
    return getHeightOfBookCollectionHelper(root);
}



/*
 * Purpose: Find the in-order successor. It starts at the right child of the node to be
 * deleted and goes as far left as possible until finds a child with no node in the left
 * @param currentBook
 * @return (Book) in-order successor
 */
Book* BookCollection::searchMinHelper(Book* currentBook)
{
    // check that current book is not null
    if (currentBook == nullptr) {
        return nullptr;
    } else if (currentBook->left == nullptr) { // if we are at the most left child
        return currentBook;
    } else {
        return searchMinHelper(currentBook->left); // traverse left
    }
}

/*
 * Purpose: Remove a specific book from the collection
 * @param (Book*) &currentBook, (s) foundBook
 * @return none
 */
void BookCollection::removeBookhelper(Book* &currentBook, string foundBook) {

    // check if the input exists in the tree
    if (showBookHelper(root, foundBook) == nullptr) {
        cout << "Book not found!" << endl;
        return;
    }
    
    // traverse through the tree until we get to the book that we want to delete
    int strComp = currentBook->bookName.compare(foundBook);

    if (strComp > 0) { // if greater than 0, then currentBook->bookName is greater than foundBook therefore we should traverse left
        removeBookhelper(currentBook->left, foundBook);
    } else if (strComp < 0) { // if smaller than 0, then current->bookname is smaller then foundBook therefore we shuold traverse right
        removeBookhelper(currentBook->right, foundBook);
    } else { // if 0, strings are equal

        // if the book is a leaf (no children)
        if (currentBook->left == nullptr && currentBook->right == nullptr) {
            delete currentBook;
            currentBook = nullptr;
        } 
        // if it only has a right child and not left child
        else if (currentBook->left == nullptr && currentBook->right != nullptr) {
            Book* childBook = currentBook->right; // store the right child into a pointer
            delete currentBook; // delete the node that we want to delete
            currentBook = childBook; // "connect" the child and it's children to the tree again by assinging the stored pointer to current book, which is conencted to the parent of the node that we just deleted
        }
        // if it only has a left child and not right child
        else if (currentBook->left != nullptr && currentBook->right == nullptr) {
            Book* childBook = currentBook->left;// store the left child into a pointer
            delete currentBook; // delete the node that we want to delete
            currentBook = childBook; // "connect" the child and it's children to the tree again by assinging the stored pointer to current book, which is conencted to the parent of the node that we just deleted
        }
        // if the node to be deleted has two children
        else {
            Book* temp = searchMinHelper(currentBook->right); // find the in-order sucessor
            // copy the in-order sucessor to the current book
            currentBook->author = temp->author;
            currentBook->bookName = temp->bookName;
            currentBook->rating = temp->rating;
            removeBookhelper(currentBook->right, currentBook->bookName); // delete the in-order successor which has already being copied to the node that we want to delete
        }
    }
}

/*
 * Purpose: Remove a book given a bookName
 * @param (s)bookName
 * @return none
 */
void BookCollection::removeBook(string bookName) {
    removeBookhelper(root, bookName);
}





