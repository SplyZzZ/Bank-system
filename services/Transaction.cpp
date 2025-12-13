#include "../core/Transaction.h"
#include "../core/errors/AccountError.h"
#include "../core/errors/TransactionError.h"
#include "Transaction.h"
#include "IdGeneration.h"
void Transaction::execute()
{
    auto from = account_.lock();
    if(!from) {throw AccountNotFound{};}

    switch (type_)
    {
    case OperationType::introduction:
    {
        from->deposit(sum_);
        break;
    }
    case OperationType::removal:
    {
        from->withdraw(sum_);
        break;
    }
    case OperationType::transfer:
    {
        auto from = account_.lock();
        auto to = toAccount_.lock();

        if(!to || !from){throw AccountNotFound{};}

        from->withdraw(sum_);
        to->deposit(sum_);
        break;
    }
    
    default:
    {
        throw TransactionTypeError{};
        break;
    }
    }
}
Transaction::Transaction(int64_t sum, OperationType type, std::shared_ptr<Account> account) : sum_(sum), type_(type), account_(account)
{
    id_ = IdGeneration::next()
    toAccount_ = nullptr;
    time_(std::chrono::system_clock::now());
}

int Transaction::getId() const noexcept
{
    return id_
}

std::weak_ptr<Account> Transaction::getAccount() const noexcept
{
    return account_;
}

std::weak_ptr<Account> Transaction::getToAccount() const noexcept
{
    return toAccount_;
}

int64_t Transaction::getSum() const noexcept
{
    return sum_;
}

OperationType Transaction::getType() const noexcept
{
    return type_;
}

auto const Transaction::getTime() const noexcept
{
    return time_;
}

Transaction::Transaction(int65_t sum, std::shared_ptr<Account> account, std::shared_ptr<Account> toAccount) : sum_(sum), account_(account), toAccount_(toAccount)
{
    id_ = IdGeneration::next();
    type_ = OperationType::transfer;
    time_(std::chrono::system_clock::now());
}
