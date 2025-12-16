#pragma once
#include "LoanStatusType.h"

#include <memory>
#include "ISubjectLoan.h"
class Loan : public ISubjectLoan
{
public:

 Loan(int64_t sum, double rate, int term, int customerID);
 double calculateInterest() const;
 void changeStatus(LoanStatusType newType) noexcept;
 int getID() const noexcept;

 virtual void attach(std::shared_ptr<IObserverLoan>obs) override;
 virtual void dettach() override;
 virtual void notify() override;

private:
    int id_;
    int customerID_;
    int64_t sum_;
    double interestRate_;
    int term_;
    LoanStatusType type_;
    std::weak_ptr<IObserverLoan> obs_;
};
