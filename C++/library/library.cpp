#include "library.hh"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

// Constructor
Library::Library():
    books_({}){
}


// Destructor
Library::~Library(){
}


// Does what you might think it does
void Library::add_book(const string& author,const string& title,
              const int& reservations){

    Book temp = {author, title, reservations};
    vector<Book>::iterator iter = books_.begin();

    // Adding books in alphabetical order
    if (books_.size() == 0){
        books_.push_back(temp);

    } else {

        while (iter != books_.end()){

            if(iter->author > temp.author){
                books_.insert(iter, temp);
                break;

            } else if (iter->author == temp.author){

                if (iter->title > temp.title){
                    books_.insert(iter,temp);
                    break;
                }
            }

            iter++;
        }

        if (iter == books_.end()){
            books_.push_back(temp);
        }
    }
}


// Prints titles and authors of all books without showing reservation status
void Library::print_all(){

    for (auto part : books_){
        cout << part.author << ": " << part.title << endl;
    }
}


// Method prints books and their amount of reservation
void Library::print_books(const string& author){

    vector<Book>::iterator iter = books_.begin();
    int running_nmbr = 0;

    while (iter != books_.end()){

        if (iter->author == author){
            cout << iter->title << " " << "---";

                if (iter->reservations == 0){
                    cout << " on the shelf" << endl;
                } else {
                    cout << " " << iter->reservations
                         << " reservations" << endl;
                }
            running_nmbr++;
        }
        iter++;
    }

    if (running_nmbr == 0){
        cout << "Error: unknown author" << endl;
    }

}


// If book is found in library, return true
bool Library::book_found(const string& author, const string& title){

    for ( auto part : books_){
        if (part.title == title and part.author == author){
            return true;
        }
    }
    return false;
}


// Method returns the amount of reservations of a book. Returns -1
// if book not found.
int Library::get_queue(const string& author, const string& title){

    for (auto part : books_){

        if ((part.author == author) and (part.title == title)){
            return part.reservations;
        }
    }

    // Book not found
    return -1;
}


// Return every book of the library stored in a vector
vector<Book> Library::all_books(){
    vector<Book> all = {};

    for (auto part : books_){
        all.push_back(part);
    }

    return all;
}
