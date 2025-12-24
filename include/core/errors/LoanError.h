#pragma once
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
class LoanIsNotActivity : public BankError
{
public: 
    LoanIsNotActivity() : BankError("Loan is not activity") {}
};
class LoanHasNotBeenRepaid : public BankError
{
public:
    LoanHasNotBeenRepaid() : BankError("The loan has not been repaid") {}
};