#ifndef BOOK_HH
#define BOOK_HH

#include "date.hh"

#include <string>


class Book
{
public:
    Book(const std::string& author, const std::string& title);
    void print();
    void loan(const Date& loan_date);
    void renew();
    void give_back();
private:

    const std::string author_;
    const std::string title_;
    bool is_loaned_;

    Date loan_date_;
    Date return_date_;
};

#endif // BOOK_HH
