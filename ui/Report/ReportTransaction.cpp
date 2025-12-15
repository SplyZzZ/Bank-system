#include "ReportTransaction.h"
#include "../formatters/OperationTypeToString.h"
ReportTransaction::ReportTransaction(const std::vector<shared_ptr<Transaction>>& transactionsList) : transactionsList_(transactionsList)
{}

Report ReportTransaction::build()
{
    doc_.title = "Transaction report";
    doc_.header = {"ID", "Type", "Sum", "Account", "To account", "Time"};

    doc_.informations.clear();
    doc_.informations.reserve(transactionsList_.size());
    for(const auto& transact : transactionsList_)
    {
        std::string fromIban = "-";
        if (auto from = transact->getAccount().lock()) fromIban = from->getIbam();

        std::string toIban = "-";
        if (transact->getType() == OperationType::transfer)
        {
            if (auto to = transact->getToAccount().lock())
            {
                toIban = to->getIbam();
            }
        }

        doc_.informations.emplace_back
        (
            {
                std::to_string(transact->getId()),
                operationTypeToString(transact->getType()),
                std::to_string(transact->getSum()),
                fromIban,
                toIban,
                std::to_string(transact->getTime())
            }
        );
    }
    return doc_;
}
