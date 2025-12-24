#pragma once
#include <string>
#include "AccountType.h"

class Account
{
public:
    Account(std::string& iban, AccountType type, int customerID);
    int64_t getBalance() const noexcept;
    void setBalance(int64_t newBalance);
    void deposit(int64_t amount);
    void withdraw(int64_t amount);
    int getCustomerId() const noexcept;
    std::string getIbam() const noexcept;
    AccountType getType() const noexcept;
    void changeType(AccountType newType) noexcept;
private:
    std::string iban_;
    AccountType type_;
    int64_t balance_;
    int customerID_;
};
