#include "BankError.h"


class CustomerNotFound : public BankError
{
public:
    CustomerNotFound() : BankError("Customer not found") {}
};
class CustomerLoansNoExtinguished : public BankError
{
public:
    CustomerLoansNoExtinguished() : BankError("Not all loans are closed") {}

};
