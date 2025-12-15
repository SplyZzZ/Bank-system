#include "Report.h"
#include "core/Transaction.h"
class ReportTransaction : public Report
{
public:
    ReportTransaction(const std::vector<shared_ptr<Transaction>>& transactionsList);

protected:
    virtual Report build() override;

private:
    std::vector<std::shared_ptr<Transaction>> transactionsList_;

};