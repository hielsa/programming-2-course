#include "book.hh"

#include <iostream>

Book::Book(const std::string& author, const std::string& title) :
    author_(author),
    title_(title),
    is_loaned_(false),
    loan_date_(Date(1, 1, 1)),
    return_date_(Date(1, 1, 1))

{

}

void Book::print()
{
    std::cout << author_ << " : " << title_ << std::endl;
    if (is_loaned_)
    {
        std::cout << "- loaned: ";
        loan_date_.print();
        std::cout << "- to be returned: ";
        return_date_.print();
    }
    else
    {
        std::cout << "- available" << std::endl;
    }
}

void Book::loan(const Date &loan_date)
{
    if (is_loaned_)
    {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
        return;
    }
    is_loaned_ = true;
    loan_date_ = loan_date;
    return_date_ = loan_date;
    return_date_.advance(28);
}

void Book::renew()
{
    if (!is_loaned_) {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
        return;
    }
        return_date_.advance(28);
}

void Book::give_back()
{
    is_loaned_ = false;
}



