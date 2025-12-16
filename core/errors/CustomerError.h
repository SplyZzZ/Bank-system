#include "BankError.h"

class CustomerNotFound : public BankError
{
public:
    CustomerNotFound() : BankError("Customer not found") {}
};
