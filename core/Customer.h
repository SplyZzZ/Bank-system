#pragma once
#include "ContactInformation.h"
#include "Loans.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include "Account.h"
class Customer
{
public:
    Customer(std::string name, ContactInfrormation contact);
    void addAccount(std::shared_ptr<Account> newAccount);
    void removeAccount(std::string& iban);
    const ContactInfrormation& getContact() const noexcept;
     int getID() const noexcept;
private:
    int id_;
    std::string name_;
    ContactInfrormation contact_;
    std::unordered_map<std::string, std::shared_ptr<Account>> accounts_;
    std::vector<std::unique_ptr<Loan>> loansList;
};
