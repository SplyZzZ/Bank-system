#pragma once
#include "BankError.h"

class InvalidAmount : public BankError
{
public:
   InvalidAmount() : BankError("Invalid amount") {}
};

class InsufficientFunds : public BankError
{
public:
    InsufficientFunds() : BankError("Insufficient funds") {}
};

class DuplicateAccount : public BankError
{
public:
    DuplicateAccount() : BankError("Duplicate account") {}
};

class AccountNotFound : public BankError
{
public:
    AccountNotFound() : BankError("Account not found") {}
};
class PositiveBalanceDelete : public BankError
{
public:
    PositiveBalanceDelete() : BankError("Positive balance") {}
};

class DeleteNotEmptyAccount : public BankError
{
public:
 DeleteNotEmptyAccount() : BankError("Not empty account") {}
};
