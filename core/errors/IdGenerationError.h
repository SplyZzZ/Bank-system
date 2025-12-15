#include "BankError.h"
class DuplicateCustomerId : public BankError
{
public:
    DuplicateCustomerId() : BankError("Id duplicate") {}
};
class DuplicateTransactionId : public BankError
{
public:
    DuplicateTransactionId() : BankError("Id duplicate") {}
};
