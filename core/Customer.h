#pragma once
#include "ContactInformation.h"
#include "Loans.h"
#include <memory>
#include <vector>

class Customer
{
public:
    Customer(std::string name, ContactInfrormation contact);
    void addAccount(std::string newAccount);
    void removeAccount(std::string iban);
    const ContactInfrormation& getContact() const noexcept;
    int getID() const noexcept;
private:
    int id_;
    std::string name_;
    ContactInfrormation contact_;
    std::vector<std::string> accounts_;
    std::vector<std::unique_ptr<Loan>> loansList_;
};
