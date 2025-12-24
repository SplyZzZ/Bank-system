#include "BankError.h"
class NoReportType : public BankError
{
public:
    NoReportType() : BankError("Invalide report type") {}
};