#pragma once
#include <string>
#include "AccountType.h"

class Account
{
public:
    Account(std::string& iban, AccountType type);
    int64_t getBalance() const noexcept;
    void setBalance(int64_t newBalance);
    void deposit(int64_t amount);
    void withdraw(int64_t amount);
    std::string getIbam() const noexcept;
    AccountType getType() const noexcept;
private:
    std::string iban_;
    AccountType type_;
    int64_t balance_;
};
