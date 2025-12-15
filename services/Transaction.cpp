#include "core/Transaction.h"
#include "core/errors/AccountError.h"
#include "core/errors/TransactionError.h"
#include "core/Transaction.h"
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
        auto to = toAccount_.lock();

        if(!to){throw AccountNotFound{};}

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
Transaction::Transaction(int64_t sum, OperationType type, std::shared_ptr<Account> account) : account_(account), sum_(sum), type_(type)
{
    id_ = IdGeneration::next();
    time_ = std::chrono::system_clock::now();
}

int Transaction::getId() const noexcept
{
    return id_;
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

auto  Transaction::getTime() const noexcept
{
    return time_;
}

Transaction::Transaction(int64_t sum, std::shared_ptr<Account> account, std::shared_ptr<Account> toAccount) : account_(account), toAccount_(toAccount), sum_(sum)
{
    id_ = IdGeneration::next();
    type_ = OperationType::transfer;
    time_ = std::chrono::system_clock::now();
}
