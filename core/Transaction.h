#pragma once
#include <string>
#include <memory>
#include "Account.h"
#include "OperationType.h"
#include <chrono>
class Transaction
{
public:
    void execute();
    Transaction(int64_t sum, OperationType type, std::shared_ptr<Account> account);
    Transaction(int64_t sum, std::shared_ptr<Account> account, std::shared_ptr<Account> toAccount);
private:
    int id_;
    std::weak_ptr<Account> account_;
    std::weak_ptr<Account> toAccount_;
    int64_t sum_;
    OperationType type_;
    std::chrono::system_clock::time_point time_;
};