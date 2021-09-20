#include "account.hh"
#include <iostream>
#include <string>

Account::Account(const std::string owner, bool has_credit):
    owner_(owner), has_credit_(has_credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::print() const {
    std::cout << owner_ << " : " << iban_ << " : " << balance_ << " euros" << std::endl;
}

void Account::set_credit_limit(int limit) {
    if (has_credit_) {
        credit_limit_ = limit;
    } else {
        credit_limit_ = 0;
    }
}

void Account::save_money(int savings) {
    balance_ += savings;
    }

void Account::take_money(int spendings) {

    if (has_credit_) {
        if ((balance_ - spendings) < -(credit_limit_)) {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
        } else {
            balance_ -= spendings;
            std::cout << spendings << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
        }
    }
    else {
        if (balance_ - spendings < 0) {
            std::cout << "Cannot take money: balance underflow" << std::endl;
        } else {
            balance_ -= spendings;
            std::cout << spendings << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
        }
    }
}

void Account::transfer_to(Account &A2, int transfer) {
    if (has_credit_) {
        if ((balance_ + credit_limit_) >= transfer) {
            balance_ -= transfer;
            A2.save_money(transfer);
            std::cout << transfer << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
        } else {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        }
    }
    else {
        if (balance_ <= transfer) {
            std::cout << "Cannot take money: balance underflow" << std::endl;
            std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        } else {
            balance_ -= transfer;
            A2.save_money(transfer);
            std::cout << transfer << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
        }
    }
}
