#pragma once
#include <unordered_map>
#include <memory>
class Customer;
class CreditSnepshotServices
{
public:
    void addActivityLoans(int customerID) noexcept;
    void addCurrentlyOverdue(int customerID) noexcept;
    void addClosedLoans(int customerID) noexcept;
    void addLoansEverOverdueTotal(int customerID) noexcept;
    void addRepaidOnTimeTotal(int customerID) noexcept;
private:
std::unordered_map<int, std::shared_ptr<Customer>>  customers_;
};
