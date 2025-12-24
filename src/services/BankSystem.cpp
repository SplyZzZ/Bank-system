#include "services/BankSystem.h"
#include <memory>
#include <string>
#include "core/Account.h"
#include "core/ContactInformation.h"
#include "core/Customer.h"
#include "core/LoanStatusType.h"
#include "core/Loans.h"
#include "core/Transaction.h"
#include "core/errors/AccountError.h"
#include "core/errors/ContractInformationError.h"
#include "core/errors/IdGenerationError.h"
#include "core/AccountType.h"
#include "services/IbamGeneretion.h"
#include "core/errors/CustomerError.h"
#include <cmath>
#include "core/errors/LoanError.h"
#include "core/RejectedLoanInfo.h"
#include "services/CreditSnepshotServices.h"
BankSystem::BankSystem()
        : creditServices_(archiveCustomer_)
    {
    }
std::shared_ptr<Customer> BankSystem::addCustomer(std::string name, std::string pass, ContactInfrormation contact)
{
    validateContactUniqueness(contact);

    creditServices_.setMap(activityCustomerList_);
    auto newCustomer = std::make_shared<Customer>(name, pass, contact);

    auto [it, inserted] = activityCustomerList_.emplace(newCustomer->getID(), newCustomer);
    if(!inserted) { throw DuplicateCustomerId{}; }

    archiveCustomer_.emplace(newCustomer->getID(),newCustomer );
    if(contact.email) {idByEmail_.emplace(*contact.email ,newCustomer->getID());}
    if(contact.phone) {idByPhone_.emplace(*contact.phone, newCustomer->getID());}
    return newCustomer;
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

    auto newAccount = std::make_shared<Account>(newIbam, type, customerID);
    customer->second->addAccount(newIbam);
    accountList_.emplace(newIbam, newAccount);
    activityAccountList_.emplace(newIbam, newAccount);

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

    auto newLoan = std::make_shared<Loan>(sum, rate, term, customerID);
    pendingLoans_.emplace(newLoan->getID(), newLoan);
    alghoritmToGiveLoan(newLoan);
}
void BankSystem::alghoritmToGiveLoan(std::shared_ptr<Loan> loan)
{
    auto it = activityCustomerList_.find(loan->getCustomerID());
    if(it == activityCustomerList_.end()){throw CustomerNotFound{};}
    auto snapshot = it->second->getCreditSnapshot();
    auto profile = it->second->getCustomerProfile();
    double i = loan->getInterestRate();
    double P = loan->getSum() * i * pow(1 + i, loan->getTermin()) / (pow(1+i,loan->getTermin()) - 1 );
    size_t k_max = static_cast<size_t>(profile.monthlyIncome_.value() * 0.4 / P);
    if(k_max >= snapshot.activeLoans_)
    {
        RejectedLoanInfo whyRegejecredLoan;
        whyRegejecredLoan.loan = loan;
        whyRegejecredLoan.reason = "limits loan";
        whyRegejecredLoan.rejectedBy = "System";
        rejectedLoans_.emplace(loan->getID(), whyRegejecredLoan);
        loansList_.emplace(loan->getID(),loan);
        pendingLoans_.erase(loan->getID());
        throw ExceededLoanslimit{};
    }
    if(snapshot.repaidOnTimeTotal_ < snapshot.loansEverOverdueTotal_ && loan->getSum() > 50000)
    {
        RejectedLoanInfo whyRegejecredLoan;
        whyRegejecredLoan.loan = loan;
        whyRegejecredLoan.reason = "Too large an amount, with a delay of more than closed on time";
        whyRegejecredLoan.rejectedBy = "System";
        rejectedLoans_.emplace(loan->getID(), whyRegejecredLoan);
        loansList_.emplace(loan->getID(),loan);
        pendingLoans_.erase(loan->getID());
        throw TooMoreSum{};
    }
    if(profile.monthlyIncome_ < loan->getSum() / 2)
    {
         RejectedLoanInfo whyRegejecredLoan;
        whyRegejecredLoan.loan = loan;
        whyRegejecredLoan.reason = "The loan amount is too high compared to income";
        whyRegejecredLoan.rejectedBy = "System";
        rejectedLoans_.emplace(loan->getID(), whyRegejecredLoan);
        loansList_.emplace(loan->getID(),loan);
        pendingLoans_.erase(loan->getID());
        throw TooMoreSum{};
    }
    if(snapshot.repaidOnTimeTotal_ < 10 && loan->getSum() > 1000000 )
    {
         RejectedLoanInfo whyRegejecredLoan;
        whyRegejecredLoan.loan = loan;
        whyRegejecredLoan.reason = "Too much money";
        whyRegejecredLoan.rejectedBy = "System";
        rejectedLoans_.emplace(loan->getID(), whyRegejecredLoan);
        loansList_.emplace(loan->getID(),loan);
        pendingLoans_.erase(loan->getID());
        throw TooMoreSum{};
    }

    it->second->addLoan(loan->getID());
    creditServices_.addActivityLoans(it->second->getID());
    activeLoans_.emplace (loan->getID(), loan);
    loansList_.emplace(loan->getID(), loan);
    pendingLoans_.erase(loan->getID());
}
void BankSystem::closeCustomer(int customerID)
{
   auto customer = activityCustomerList_.find(customerID);
   if(customer == activityCustomerList_.end()) return;

   if(customer->second->getCreditSnapshot().activeLoans_ != 0){throw CustomerLoansNoExtinguished{};}

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
 std::shared_ptr<Customer> BankSystem::login(std::string phoneNumber, std::string pass) const
 {
   auto it =  idByPhone_.find(phoneNumber);
   if(it == idByPhone_.end()){ throw CustomerNotFound{};}
   auto user = activityCustomerList_.find(it->second);
   if(user == activityCustomerList_.end()) { throw CustomerNotFound{}; }
   if(user->second->getPass() != pass) { throw InvalidePassword{};}
   return user->second;
 }
 
void BankSystem::closeLoan(std::shared_ptr<Loan> loan)
{
    auto it = activeLoans_.find(loan->getID());
    if(it == activeLoans_.end()) { throw LoanIsNotActivity{}; }
    if(it->second->getSum() != it->second->getGlobalSum()) {LoanHasNotBeenRepaid{};}
    loan->changeStatus(LoanStatusType::extinguished);
   
    closedLoans_.try_emplace(it->second->getID(),it->second);
    activeLoans_.erase(it);
   creditServices_.addClosedLoans(loan->getCustomerID());
}
void BankSystem::closeAccount(std::string iban)
{
    auto it = activityAccountList_.find(iban);
    if(it== activityAccountList_.end()) { throw AccountNotActivity{};}
    if(it->second->getBalance() != 0) { throw DeleteNotEmptyAccount{}; }
    auto customerIt = archiveCustomer_.find(it->second->getCustomerId());
    if(customerIt == archiveCustomer_.end()) { throw CustomerNotFound {}; }   
    it->second->changeType(AccountType::Closed);
    customerIt->second->removeAccount(it->second->getIbam());
    closedAccountList_.try_emplace(it->second->getIbam(), it->second);
    activityAccountList_.erase(it);
}
