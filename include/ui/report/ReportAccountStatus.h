#pragma once
#include "Report.h"
#include "core/Account.h"
#include <unordered_map>
#include <memory>
class ReportAccountStatus : public Report
{
 public:
    ReportAccountStatus(const std::unordered_map<std::string, std::shared_ptr<Account>>& accountList);

 private:
    const std::unordered_map<std::string, std::shared_ptr<Account>> accountList_;

 protected:
    virtual void build() override;

};
