#pragma once
#include <cstdint>

class CreditSnapshot
{
public:
 std::size_t activeLoans_ = 0;
 std::size_t overdueLoans_ = 0;
 std::size_t closedLoansTotal_ = 0;
 std::size_t loansEverOverdueTotal_ = 0;
 std::size_t repaidOnTimeTotal_ = 0;

};
