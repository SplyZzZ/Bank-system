#include "Customer.h"
#include "errors/AccountError.h"
#include "../services/IdGeneration.h"
#include <algorithm>
Customer::Customer(std::string name, ContactInfrormation contact) : name_(std::move(name)), contact_(std::move(contact))
{
    id_ = IdGeneration::next();
}
void Customer::addAccount(std::string newAccount)
{
  auto it = std::find(accounts_.begin(), accounts_.end(), newAccount);
   if(it != accounts_.end())
   {
    throw DuplicateAccount{};
   }
   accounts_.emplace_back(newAccount);
}
 int Customer::getID() const noexcept
{
    return id_;
}
const ContactInfrormation& Customer::getContact() const noexcept
{
    return contact_;
}

void Customer::removeAccount(std::string iban)
{
   auto it = std::find(accounts_.begin(), accounts_.end(), iban);
   if(it == accounts_.end())
   {
    throw DuplicateAccount{};
   }
   accounts_.erase(it);
}
 void Customer::addLoan(int loanID) noexcept
 {
    loansIdList_.emplace_back(loanID);
    ++unsecuredLoan_;
 }
 const std::vector<std::string>& Customer::getAccountsList() const noexcept
 {
    return accounts_;
 }
 void Customer::unsecuredLoan() noexcept
 {
    --unsecuredLoan_;
 }
