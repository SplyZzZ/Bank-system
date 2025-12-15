#include "BankError.h"
class DuplicateEmail : public BankError
{
    public:
    DuplicateEmail() : BankError("Duplicate email")
    {}
};
class DuplicatePhone : public BankError
{
    public:
    DuplicatePhone() : BankError("Duplicate phone")
    {}
};
