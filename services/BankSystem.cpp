#include "BankSystem.h"
#include <memory>
#include <string>
#include "core/Account.h"
#include "core/ContactInformation.h"
#include "core/Loans.h"
#include "core/Transaction.h"
#include "core/errors/AccountError.h"
#include "core/errors/ContractInformationError.h"
#include "core/errors/IdGenerationError.h"
#include "core/AccountType.h"
#include "IbamGeneretion.h"
#include "core/errors/CustomerError.h"
#include "core/ObserverCustomer.h"

void BankSystem::addCustomer(std::string name, ContactInfrormation contact)
{
    validateContactUniqueness(contact);

    auto newCustomer = std::make_shared<Customer>(name, contact);

    auto [it, inserted] = activityCustomerList_.emplace(newCustomer->getID(), newCustomer);
    if(!inserted) { throw DuplicateCustomerId{}; }

    activityCustomerList_.emplace(newCustomer->getID(), newCustomer);
    archiveCustomer_.emplace(newCustomer->getID(),newCustomer );
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
void BankSystem::createAccount(int customerID, AccountType type)
{
      auto customer =  activityCustomerList_.find(customerID);
    if(customer == activityCustomerList_.end()) {throw CustomerNotFound{}; }

    std::string newIbam;
    do
    {
      newIbam = IbamGeneretion();
    }while(accountList_.find(newIbam) != accountList_.end());

    auto newAccount = std::make_shared<Account>(newIbam, type);
    customer->second->addAccount(newIbam);
    accountList_.emplace(newIbam, newAccount);

}
void BankSystem::createTransaction(OperationType type, int64_t sum, const std::string& fromAccount)
{


   auto acc = findAccountUsIban(fromAccount);
   auto newTransaction = std::make_shared<Transaction>(sum, type, acc);

   newTransaction->execute();

   auto [iterator, inserted] = transactionList_.emplace(newTransaction->getId(), newTransaction);
   if(!inserted) throw DuplicateTransactionId{};

}
void BankSystem::createTransaction(int64_t sum, const std::string& fromAccount, const std::string& toAccount)
{
    auto fromAcc = findAccountUsIban(fromAccount);
    auto toAcc = findAccountUsIban(toAccount);

    auto newTransaction = std::make_shared<Transaction>(sum, fromAcc, toAcc);

    newTransaction->execute();

    auto [it, inserted] = transactionList_.emplace(newTransaction->getId(), newTransaction);
    if(!inserted) throw DuplicateTransactionId();

}
 std::shared_ptr<Account> BankSystem::findAccountUsIban(const std::string& iban) const
 {
    auto it = accountList_.find(iban);
    if(it == accountList_.end()) throw AccountNotFound{};

    return it->second;
 }
void BankSystem::createLoan(int64_t sum, double rate, int term, int customerID)
{
    auto it = activityCustomerList_.find(customerID);
    if(it == activityCustomerList_.end()) throw CustomerNotFound {};

    auto newLoan = std::make_unique<Loan>(sum, rate, term, customerID);
    
    // it->second->addLoan(newLoan->getID());

    // auto obs = std::make_shared<ObserverCustomer>(it->second);
    // loanObserversKeepAlive_.push_back(obs);
    // newLoan->attach(obs);

    loansList_.emplace(newLoan->getID(), std::move(newLoan) );


}
 void BankSystem::closeCustomer(int customerID)
 {
   auto customer = activityCustomerList_.find(customerID);
   if(customer == activityCustomerList_.end()) return;

   if(customer->second->getUnsecuredLoan() != 0){throw CustomerLoansNoExtinguished{};}

   for(const auto& sum : customer->second->getAccountsList())
   {
    const auto acc = accountList_.find(sum);

     if(acc == accountList_.end() || !acc->second) throw AccountNotFound{};
     if(acc->second->getBalance() != 0) {throw DeleteNotEmptyAccount{};}
   }

   customer->second->setClosed();

   auto contact = customer->second->getContact();
   if(contact.email) {idByEmail_.erase(*contact.email);}
   if(contact.phone) {idByPhone_.erase(*contact.phone);}

   archiveCustomer_.try_emplace(customerID, customer->second);
   activityCustomerList_.erase(customer);

 }
