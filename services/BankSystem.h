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
class BankSystem
{
public:
    void addCustomer(std::string name, ContactInfrormation contact);
    std::string createAccount(AccountType type);
    void createTransaction(OperationType type, int64_t sum, const std::string& fromAccount);
    void createTransaction(int64_t sum, std::string& fromAccount, const std::string& toAccount);
private:
    std::unordered_map<int, std::shared_ptr<Customer>> customerList_;
    std::unordered_map<std::string, int> idByEmail_;
    std::unordered_map<std::string, int> idByPhone_;
    std::unordered_map<std::string, std::shared_ptr<Account>> accountList_;
    std::unordered_map<int, std::shared_ptr<Transaction>> transactionList_;
    void validateContactUniqueness(const ContactInfrormation& contact) const;
};
