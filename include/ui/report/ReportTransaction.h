#pragma once
#include "Report.h"
#include "core/Transaction.h"
#include <unordered_map>
class ReportTransaction : public Report
{
public:
    ReportTransaction(const std::unordered_map<int, std::shared_ptr<Transaction>>& transactionList );

protected:
    virtual void build() override;

private:
   std::unordered_map<int, std::shared_ptr<Transaction>> transactionList_;

};
