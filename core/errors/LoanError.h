#include "BankError.h"
class ExceededLoanslimit : public BankError
{
    public:
    ExceededLoanslimit() : BankError("Exceeded loans limit") {}
};
class TooMoreSum : public BankError
{
    public:
    TooMoreSum() : BankError("Too more sum") {}
};
