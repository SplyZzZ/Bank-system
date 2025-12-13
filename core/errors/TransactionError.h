#include "BankError.h"
class TransactionTypeError : public BankError
{
    public:
    TransactionTypeError() : BankError("Invalid transaction type");
}