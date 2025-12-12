#include "../core/Transaction.h"
#include "../core/errors/AccountError.h"
void Transaction::execute()
{
    switch (type_)
    {
    case OperationType::introduction:
    {
        account_.lock()->deposit(sum_);
        break;
    }
    case OperationType::removal:
    {
        account_.lock()->withdraw(sum_);
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
        break;
    }
}