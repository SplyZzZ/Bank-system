#pragma once
class IObserverLoan
{
 public:
    virtual ~IObserverLoan();
    virtual void onStatusChange();
};
