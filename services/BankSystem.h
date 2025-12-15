#pragma once
#include <unordered_map>
#include "core/AccountType.h"
#include "core/ContactInformation.h"
#include "core/Customer.h"
#include <memory>
#include <string>
#include "core/Account.h"

class BankSystem
{
public:
    void addCustomer(std::string name, ContactInfrormation contact);
    std::string createAccount(AccountType type);
private:
    std::unordered_map<int, std::shared_ptr<Customer>> customerList_;
    std::unordered_map<std::string, int> idByEmail_;
    std::unordered_map<std::string, int> idByPhone_;
    std::unordered_map<std::string, std::shared_ptr<Account>> accountList_;
    void validateContactUniqueness(const ContactInfrormation& contact) const;
};
