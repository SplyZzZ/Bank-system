#include "ui/report/ReportAccountStatus.h"

#include "ui/formatters/AccountTypeToString.h"
ReportAccountStatus::ReportAccountStatus(const std::vector<std::shared_ptr<Account>>& accountList) : accountList_(accountList){};
void ReportAccountStatus::build()
{
    doc_.title = "Account report";
    doc_.header = {"Iban","Balance","Type"};

    doc_.informations.clear();
    doc_.informations.reserve(accountList_.size());

    for(const auto& acc : accountList_)
    {
       doc_.informations.emplace_back(
        std::vector<std::string>{
        acc->getIbam(),
        std::to_string(acc->getBalance()),
        accountTypeToString(acc->getType())
    }
        );
    }
}
