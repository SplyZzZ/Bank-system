#include "Loans.h"
#include "../services/IdGeneration.h"
Loan::Loan(int64_t sum, double rate, int term) : sum_(sum), interestRate_(rate), term_(term)
{
    id_ = IdGeneration::next();
    type_ = LoanStatusType::issued;
}

int64_t Loan::calculateInterest() const
{
    return sum_*interestRate_*(term_ / 12);
}

void Loan::changeStatus(LoanStatusType &newType) noexcept
{
    type_ = newType;
}
