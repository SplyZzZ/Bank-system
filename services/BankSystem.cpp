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
    auto it = customerList_.find(customerID);
    if(it == customerList_.end()) throw CustomerNotFound {};

    auto newLoan = std::make_unique<Loan>(sum, rate, term, customerID);
    it->second->addLoan(newLoan->getID());

    auto obs = std::make_shared<ObserverCustomer>(it->second);
    loanObserversKeepAlive_.push_back(obs);
    newLoan->attach(obs);

    loansList_.emplace(newLoan->getID(), std::move(newLoan) );


}
 void BankSystem::deleteCustomer(int customerID)
 {
   auto customer =  customerList_.at(customerID);





   const std::vector<std::string> accountList = customer->getAccountsList();
   if(accountList.size() != 0)
   {
    for (const auto& iban : accountList)
    {
     if(accountList_.at(iban)->getBalance() != 0)
     {
        throw PositiveBalanceDelete{};
     }
    }
   }
 }
