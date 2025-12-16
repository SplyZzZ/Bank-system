#include "Loans.h"
#include "services/IdGeneration.h"
#include "core/LoanStatusType.h"
Loan::Loan(int64_t sum, double rate, int term, int customerID) : customerID_(customerID), sum_(sum), interestRate_(rate), term_(term)
{
    id_ = IdGeneration::next();
    type_ = LoanStatusType::issued;
}

double Loan::calculateInterest() const
{
    return sum_*interestRate_*(term_ / 12);
}

void Loan::changeStatus(LoanStatusType newType) noexcept
{
    type_ = newType;

    if(type_ == LoanStatusType::extinguished)
    {
        notify();
    }

}
int Loan::getID() const noexcept
{
    return id_;
}
void Loan::attach(std::shared_ptr<IObserverLoan>obs)
{
    obs_ = obs;
}
void Loan::dettach()
{
    obs_.reset();
}
void Loan::notify()
{
    if(obs_.lock())
    {
        obs_.lock()->onStatusChange();
    }
}
