#pragma once
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
class InvalidePassword : public BankError
{
    public:
    InvalidePassword() : BankError("Invalide password") {}
};
