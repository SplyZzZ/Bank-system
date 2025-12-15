#pragma once
#include "LoanStatusType.h"
#include <chrono>

class Loan
{
public:

 Loan(int64_t sum, double rate, int term);

 int64_t calculateInterest() const;

 void changeStatus(LoanStatusType& newType) noexcept;

private:
    int id_;
    int64_t sum_;
    double interestRate_;
    int term_;
    LoanStatusType type_;
};