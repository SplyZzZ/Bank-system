#pragma once

#include <memory>
#include "Account.h"
#include "OperationType.h"

class Transaction
{
public:
    void execute();
    Transaction(int64_t sum, OperationType type, std::shared_ptr<Account> account);
    Transaction(int64_t sum, std::shared_ptr<Account> account, std::shared_ptr<Account> toAccount);
    int getId() const noexcept;
    std::weak_ptr<Account> getAccount() const noexcept;
    std::weak_ptr<Account> getToAccount() const noexcept;
    int64_t getSum() const noexcept;
    OperationType getType() const noexcept;
    int  getTime() const noexcept;
private:
    int id_;
    std::weak_ptr<Account> account_;
    std::weak_ptr<Account> toAccount_;
    int64_t sum_;
    OperationType type_;
    int time_;
};
