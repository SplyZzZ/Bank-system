#include "Customer.h"
#include "errors/AccountError.h"
#include "../services/IdGeneration.h"
Customer::Customer(std::string name, ContactInfrormation &contact) : name_(std::move(name)), contact_(contact)
{
    id_ = IdGeneration::next();
}
void Customer::addAccount(std::shared_ptr<Account> newAccount)
{
   auto [it, inserted] = accounts_.try_emplace(newAccount->getIbam(), newAccount );
   if(!inserted)
   {
    throw DuplicateAccount{};
   }
}

const ContactInfrormation& Customer::getContact() const noexcept
{
    return contact_;
}

void Customer::removeAccount(std::string& iban)
{
    if(accounts_.erase(iban) == 0)
    {
        throw AccountNotFound{};
    }
}
