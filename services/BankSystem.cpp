#include "BankSystem.h"
#include <string>
#include "core/ContactInformation.h"
#include "core/errors/ContractInformationError.h"
#include "core/errors/IdGenerationError.h"
 void BankSystem::addCustomer(std::string name, ContactInfrormation contact)
 {
    validateContactUniqueness(contact);

    auto newCustomer = std::make_shared<Customer>(name, contact);

    auto [it, inserted] = customerList_.emplace(newCustomer->getID(), newCustomer);
    if(!inserted) { throw DuplicateCustomerId{}; }

    customerList_.emplace(newCustomer->getID(), newCustomer);

    if(contact.email) {idByEmail_.emplace(*contact.email ,newCustomer->getID());}
    if(contact.phone) {idByPhone_.emplace(*contact.phone, newCustomer->getID());}
 }
 void BankSystem::validateContactUniqueness(const ContactInfrormation& contact) const
 {
    if (contact.email && idByEmail_.find(*contact.email) != idByEmail_.end())
    {
        throw DuplicateEmail{};
    }

    if (contact.phone && idByPhone_.find(*contact.phone) != idByPhone_.end())
    {
        throw DuplicatePhone{};
    }
 }
