#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);
    // More methods
    void print() const;
    void set_credit_limit(int limit);
    void save_money(int savings);
    void take_money(int spendings);
    void transfer_to(Account &A2, int transfer);

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();
    // Used for generating IBAN.
    static int running_number_;

    // More attributes/methods
    const std::string owner_;
    bool has_credit_;
    int balance_ = 0;
    std::string iban_;
    int credit_limit_;
};

#endif // ACCOUNT_HH
