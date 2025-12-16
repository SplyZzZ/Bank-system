#include "ObserverCustomer.h"

ObserverCustomer::ObserverCustomer(std::shared_ptr<Customer> customer) : customer_(customer)
{}
 void ObserverCustomer::onStatusChange()
 {
    if(customer_.lock())
    {
        customer_.lock()->unsecuredLoan();
    }
 }
