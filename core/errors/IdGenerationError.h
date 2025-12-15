#include "BankError.h"
class DuplicateCustomerId : public BankError
{
public:
    DuplicateCustomerId() : BankError("Id duplicate") {}
};
