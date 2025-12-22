#pragma once
#include "Report.h"
#include "core/Transaction.h"
class ReportTransaction : public Report
{
public:
    ReportTransaction(const std::vector<std::shared_ptr<Transaction>>& transactionsList);

protected:
    virtual void build() override;

private:
    std::vector<std::shared_ptr<Transaction>> transactionsList_;

};
