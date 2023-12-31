#include <iostream>
#include <fstream>
#include <sstream>
#include "BookCollection.hpp"
#include <vector>
using namespace std;

/*
 * Purpose: Print the options for the user
 * @param none
 * @return none
 */
void displayMenu() {
    cout << endl;
    cout << "======Main Menu======" << endl;
    cout << "1. Show book collection" << endl; // Show complete book collection
    cout << "2. Add a book"<< endl; // Add a book to the collection
    cout << "3. Search a book"<< endl; // Show book by searching for given book name
    cout << "4. Display books by a given author"<< endl; // Show books by a given author
    cout << "5. Display the highest rated books" << endl; // Show the highest rated books in the collection
    cout << "6. Display the height of the book collection tree"<< endl; // Show the height of the book collection (Height of the BST)
    cout << "7. Remove a book"<< endl; // remove a specific book from the tree
    cout << "8. Quit" << endl; //Quit
}


int main() {

    // variable delcaration
    string line;
    string field;
    string tempBookName;
    string tempAuthor;
    double tempRating;
    int counter = 0;
    int input;
    BookCollection* collection = new BookCollection();


    // open the file and check that it has been opened sucessfully
    ifstream inputFile;
    inputFile.open("books.csv");
    if (inputFile.fail()) {
        cout << "File failed to open." << endl;
        return 0;
    }

    while(getline(inputFile, line)) {
        stringstream ss(line);
        counter = 0;
        while(getline(ss, field, ',')) {
            if (counter == 0) {
                tempBookName = field;
            } else if (counter == 1) {
                tempAuthor = field;
            } else if (counter == 2) {
                tempRating = stod(field);
            }
            counter++;
        }
        collection->addBook(tempBookName, tempAuthor, tempRating);
    }

    // show the menu to the user
    while (1) {
        displayMenu();
        cin>>input;

        while (input <= 0 || input > 8) {
            cout << "Input not valid, try again." << endl;
            cin>>input;
        }

        switch (input)
        {
    // == Show book collection ============================================================
        case 1:
            collection->showBookCollection();
            break;
        
    // == Add a book =======================================================================
        case 2:
            // ask user for input
            cout << "Name of book: ";
            cin.ignore();
            getline(cin, tempBookName);
            cout << endl;
            cout << "Author of the book: ";
            getline(cin, tempAuthor);
            cout << endl;
            cout << "Rating of book: ";
            cin>> tempRating;
            
            // add book with function

            collection->addBook(tempBookName, tempAuthor, tempRating);
            cout << endl;
            cout << "Book has been added" << endl;
            break;

    // == Search a book =====================================================================
        case 3:
            cout << "Enter the name of the book: ";
            cin.ignore(); // necessary because if not the getline is skipped
            getline(cin, tempBookName); // get the input
            collection->showBook(tempBookName); // the function to find the book
            break;

    // == Display books by a given author ====================================================
        case 4:
            cout << "Enter the name of the author: ";
            cin.ignore();
            getline(cin, tempAuthor);
            collection->showBooksByAuthor(tempAuthor);
            break;

    // == Display the highest rated books ====================================================
        case 5:
            collection->showHighestRatedBooks();
            break;

    // == Display the height of the book collection tree ======================================
        case 6:
            cout << "The height of the book collection tree is " << collection->getHeightOfBookCollection() << endl;
            break;

    // == Delete the a specific book from the collection ======================================
        case 7:
            cout << "Enter the name of the book to be deleted: ";
            cin.ignore();
            getline(cin, tempBookName);
            collection->removeBook(tempBookName);
            break;

    // == Quit ===============================================================================
        case 8:
            return 1;
            break;

    // == Default ===============================================================================
        default:
            cout << "Error please restart." << endl;
            return 0;
            break;
        } 
    }
    return 1;
}