#pragma once
#include "LoanStatusType.h"


class Loan
{
public:

 Loan(int64_t sum, double rate, int term, int customerID);

 int64_t calculateInterest() const;

 void changeStatus(LoanStatusType& newType) noexcept;
 int getID() const noexcept;
private:
    int id_;
    int customerID_;
    int64_t sum_;
    double interestRate_;
    int term_;
    LoanStatusType type_;
};
