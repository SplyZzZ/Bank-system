#pragma once
#include "Loans.h"
#include <chrono>
#include <memory>
struct RejectedLoanInfo
{
    std::shared_ptr<Loan> loan;
    std::string reason;
    std::string rejectedBy;
    std::chrono::system_clock::time_point rejectedAt;
};

