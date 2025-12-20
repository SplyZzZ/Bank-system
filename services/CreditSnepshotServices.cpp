#include "CreditSnepshotServices.h"
#include "core/Customer.h"
 void CreditSnepshotServices::addActivityLoans(int customerID) noexcept
 {
    auto customer = customers_.at(customerID);
    ++(customer->snapshot_.activeLoans_);
 }
 void CreditSnepshotServices::addCurrentlyOverdue(int customerID) noexcept
 {
     auto customer = customers_.at(customerID);
     ++(customer->snapshot_.overdueLoans_);
 }
 void CreditSnepshotServices::addClosedLoans(int customerID) noexcept
 {
    auto customer = customers_.at(customerID);
    ++(customer->snapshot_.closedLoansTotal_);
    --(customer->snapshot_.activeLoans_);
 }
void CreditSnepshotServices::addLoansEverOverdueTotal(int customerID) noexcept
{
  auto customer = customers_.at(customerID);
  ++(customer->snapshot_.loansEverOverdueTotal_);
}
 void  CreditSnepshotServices::addRepaidOnTimeTotal(int customerID) noexcept
 {
   auto customer = customers_.at(customerID);
    ++(customer->snapshot_.repaidOnTimeTotal_);
 }
