#include "core/Account.h"
#include "core/AccountType.h"
#include "core/errors/AccountError.h"
Account::Account(std::string &iban, AccountType type, int customerID) :  iban_(iban), type_(type), balance_(0), customerID_(customerID)
{}

int64_t Account::getBalance() const noexcept
{
    return balance_;
}

void Account::setBalance(int64_t newBalance)
{
    balance_ = newBalance;
}

void Account::deposit(int64_t amount)
{
    if(amount <= 0){ throw InvalidAmount{}; }
    balance_ += amount;

}

void Account::withdraw(int64_t amount)
{
    if(amount <= 0) {throw InvalidAmount{};}
    if(balance_ < amount) {throw InsufficientFunds{};}
    balance_ -= amount;
}
int Account::getCustomerId() const noexcept
{
    return customerID_;
}
AccountType Account::getType() const noexcept
{
    return type_;
}

std::string Account::getIbam() const noexcept
{
    return iban_;
}
void Account::changeType(AccountType newType) noexcept
{
    type_ = newType;
}
