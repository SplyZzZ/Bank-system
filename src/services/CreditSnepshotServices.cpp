#include "services/CreditSnepshotServices.h"
#include "core/Customer.h"
 CreditSnepshotServices::CreditSnepshotServices(std::unordered_map<int, std::shared_ptr<Customer>>& customers): customers_(customers) {}
 void CreditSnepshotServices::setMap(std::unordered_map<int, std::shared_ptr<Customer>>& customer)
 {
   customers_ = customer;
 }
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
