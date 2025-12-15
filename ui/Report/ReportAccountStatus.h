#include "Report.h"
#include "Account.h"
#include <vector>
#include <memory>
class ReportAccountStatus : public Report
{
 public:
    ReportAccountStatus(const std::vector<std::shared_ptr<Account>>& accountList);
    
 private:
    std::vector<std::shared_ptr<Account>> accountList_;

 protected:
    virtual Report build() override;
 
}