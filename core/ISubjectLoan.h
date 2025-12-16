#pragma once
#include "IObserverLoan.h"
#include <memory>
class ISubjectLoan
{
public:
    virtual ~ISubjectLoan();
    virtual void attach(std::shared_ptr<IObserverLoan>obs) = 0;
    virtual void dettach() = 0;
protected:
    virtual void notify() = 0;
};
