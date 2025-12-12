#pragma once
#include "ContactInformation.h"
#include <unordered_map>
#include <memory>
#include "Account.h"
class Customer
{
public:
    Customer(std::string name, ContactInfrormation& contact);
    void addAccount(std::shared_ptr<Account> newAccount);
    void removeAccount(std::string& iban);
    const ContactInfrormation& getContact() const noexcept;
    
private:
    int id_;
    std::string name_;
    ContactInfrormation contact_;
    std::unordered_map<std::string, std::shared_ptr<Account>> accounts_;
    
};