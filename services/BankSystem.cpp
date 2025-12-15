#include "BankSystem.h"
#include <memory>
#include <string>
#include "core/Account.h"
#include "core/ContactInformation.h"
#include "core/errors/ContractInformationError.h"
#include "core/errors/IdGenerationError.h"
#include "core/errors/AccountError.h"
#include "core/AccountType.h"
#include "IbamGeneretion.h"
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
std::string BankSystem::createAccount(AccountType type)
{
    std::string newIbam;
    do
    {
      newIbam = IbamGeneretion();
    }while(accountList_.find(newIbam) != accountList_.end());

    auto newAccount = std::make_shared<Account>(newIbam, type);
    accountList_.emplace(newIbam, newAccount);
    return newIbam;

}
