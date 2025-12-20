#pragma once
#include <unordered_map>
#include "core/AccountType.h"
#include "core/ContactInformation.h"
#include "core/Customer.h"
#include <memory>
#include <string>
#include "core/Account.h"
#include "core/Transaction.h"
#include "core/OperationType.h"
#include "core/Loans.h"
#include "core/IObserverLoan.h"
#include "core/RejectedLoanInfo.h"
class BankSystem
{
public:
    void addCustomer(std::string name, ContactInfrormation contact);
    void createAccount(int customerID, AccountType type);
    void createTransaction(OperationType type, int64_t sum, const std::string& fromAccount);
    void createTransaction(int64_t sum, const std::string& fromAccount, const std::string& toAccount);
    void createLoan(int64_t sum, double rate, int term, int customerID);
    void closeCustomer(int customerID);

    private:
    std::unordered_map<int, std::shared_ptr<Customer>> activityCustomerList_;
    std::unordered_map<int, std::shared_ptr<Customer>> archiveCustomer_;
    std::unordered_map<std::string, int> idByEmail_;
    std::unordered_map<std::string, int> idByPhone_;


    std::unordered_map<int, std::shared_ptr<Loan>> loansList_;
    std::unordered_map<int, std::shared_ptr<Loan>> activeLoans_;
    std::unordered_map<int, RejectedLoanInfo> rejectedLoans_;
    std::unordered_map<int, std::shared_ptr<Loan>> closedLoans_;
    std::unordered_map<int, std::shared_ptr<Loan>> pendingLoans_;


    std::unordered_map<std::string, std::shared_ptr<Account>> accountList_;
    std::unordered_map<int, std::shared_ptr<Transaction>> transactionList_;

    std::vector<std::shared_ptr<IObserverLoan>> loanObserversKeepAlive_;
    void validateContactUniqueness(const ContactInfrormation& contact) const;
    std::shared_ptr<Account> findAccountUsIban(const std::string& iban) const;
    void alghoritmToGiveLoan(std::shared_ptr<Loan> loan);
};
