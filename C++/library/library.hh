#ifndef LIBRARY_HH
#define LIBRARY_HH
#include <iostream>
#include <string>
#include <vector>
#include <utility>


struct Book{
    std::string author;
    std::string title;
    int reservations;
};


class Library
{
public:
    // Default constructor
    Library();

    //Default destructor
    ~Library();

    // Universal variables
    const int MAX_RES = 100;

    // Methods
    void add_book(const std::string& author, const std::string& title,
                  const int& reservations);

    void print_all();
    void print_books(const std::string& author);
    bool book_found(const std::string& author, const std::string& title);
    int get_queue(const std::string& author, const std::string& title);
    std::vector<Book> all_books();




private:
    // Variables
    std::vector<Book> books_;

    //Methods

};

#endif // LIBRARY_HH
