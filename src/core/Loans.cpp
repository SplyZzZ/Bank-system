#include "core/Loans.h"
#include "services/IdGeneration.h"
#include "core/LoanStatusType.h"
Loan::Loan(int64_t sum, double rate, int term, int customerID) : customerID_(customerID), sum_(sum), interestRate_(rate/ 12), term_(term)
{
    id_ = IdGeneration::next();
    type_ = LoanStatusType::issued;
    globalSum_ = sum_;
}
int64_t Loan::getGlobalSum() const noexcept
{
 return globalSum_;
}
double Loan::calculateInterest() const
{
    return globalSum_*interestRate_*(static_cast<double>(term_) / 12);
}
int Loan::getCustomerID() const noexcept
{
    return customerID_;
}
double Loan::getInterestRate() const noexcept
{
    return interestRate_;
}
void Loan::changeStatus(LoanStatusType newType) noexcept
{
    type_ = newType;
}
int Loan::getID() const noexcept
{
    return id_;
}
int64_t Loan::getSum() const noexcept
{
    return sum_;
}
int Loan::getTermin() const noexcept
{
    return term_;
}
