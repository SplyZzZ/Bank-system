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
private:
    int id_;
    std::weak_ptr<Account> account_;
    std::weak_ptr<Account> toAccount_;
    int64_t sum_;
    OperationType type_;
    std::string time_;
};