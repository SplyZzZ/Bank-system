#pragma once
#include "IObserverLoan.h"
#include "core/Customer.h"
#include "memory"
class ObserverCustomer : public IObserverLoan
{
public:
 ObserverCustomer(std::shared_ptr<Customer> customer);
 virtual void onStatusChange() override;
private:
std::weak_ptr<Customer> customer_;
};
