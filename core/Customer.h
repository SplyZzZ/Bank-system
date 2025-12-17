#pragma once
#include "ContactInformation.h"
#include <vector>
#include "CustomerType.h"
class Customer
{
public:
    Customer(std::string name, ContactInfrormation contact);
    void addAccount(std::string newAccount);
    void removeAccount(std::string iban);
    const ContactInfrormation& getContact() const noexcept;
    int getID() const noexcept;
    void addLoan(int loanID) noexcept;
    const std::vector<std::string>& getAccountsList() const noexcept;
    void unsecuredLoan() noexcept;
    unsigned int getUnsecuredLoan() const noexcept;
    void setClosed()  noexcept;
private:
    int id_;
    std::string name_;
    CustomerType type_;
    ContactInfrormation contact_;
    std::vector<std::string> accounts_;
    std::vector<int> loansIdList_;
    unsigned int unsecuredLoan_;
    int64_t totalSumAllAccount_;
};
