#pragma once
#include "LoanStatusType.h"
#include "ISubjectLoan.h"
class Loan : public ISubjectLoan
{
public:

 Loan(int64_t sum, double rate, int term, int customerID);
 double calculateInterest() const;
 void changeStatus(LoanStatusType newType) noexcept;
 int getID() const noexcept;
 int getCustomerID() const noexcept;
 int64_t getSum() const noexcept;
 int getTermin() const noexcept;
 double getInterestRate() const noexcept;


private:
    int id_;
    int customerID_;
    int64_t sum_;
    double interestRate_;
    int term_;
    LoanStatusType type_;

};
