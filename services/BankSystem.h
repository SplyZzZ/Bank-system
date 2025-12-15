#pragma once
#include <unordered_map>
#include "core/ContactInformation.h"
#include "core/Customer.h"
#include <memory>
#include <string>

class BankSystem
{
public:
    void addCustomer(std::string name, ContactInfrormation contact);

private:
    std::unordered_map<int, std::shared_ptr<Customer>> customerList_;
    std::unordered_map<std::string, int> idByEmail_;
    std::unordered_map<std::string, int> idByPhone_;
    void validateContactUniqueness(const ContactInfrormation& contact) const;
};
