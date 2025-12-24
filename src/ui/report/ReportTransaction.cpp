#include "ui/report/ReportTransaction.h"
#include "ui/formatters/OperationTypeToString.h"
#include <unordered_map>
ReportTransaction::ReportTransaction(const std::unordered_map<int, std::shared_ptr<Transaction>>& transactionList) : transactionList_(transactionList)
{}

void ReportTransaction::build()
{
    doc_.title = "Transaction report";
    doc_.header = {"ID", "Type", "Sum", "Account", "To account", "Time"};

    doc_.informations.clear();
    doc_.informations.reserve(transactionList_.size());
    for(const auto& transact : transactionList_)
    {
        std::string fromIban = "-";
        if (auto from = transact.second->getAccount().lock()) fromIban = from->getIbam();

        std::string toIban = "-";
        if (transact.second->getType() == OperationType::transfer)
        {
            if (auto to = transact.second->getToAccount().lock())
            {
                toIban = to->getIbam();
            }
        }

       doc_.informations.emplace_back
       (
        std::vector<std::string>
        {
         std::to_string(transact.second->getId()),
         operationTypeToString(transact.second->getType()),
         std::to_string(transact.second->getSum()),
         fromIban,
         toIban,
         std::to_string(transact.second->getTime())
        }
       );
    }
}
