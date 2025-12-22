#pragma once
#include "ContactInformation.h"
#include <vector>
#include "CustomerType.h"
#include "services/CustomerPrifele.h"
#include "services/CreditSnapshot.h"
#include "services/CreditSnepshotServices.h"
class Customer
{
public:
    Customer(std::string name,std::string pass, ContactInfrormation contact);
    void addAccount(std::string newAccount);
    void removeAccount(std::string iban);
    const ContactInfrormation& getContact() const noexcept;
    int getID() const noexcept;
    void addLoan(int loanID) noexcept;
    const std::vector<std::string>& getAccountsList() const noexcept;
    void setClosed()  noexcept;
    std::string getPass() const noexcept;
    const CustomerProfile& getCustomerProfile() const noexcept;
    const CreditSnapshot& getCreditSnapshot() const noexcept;
private:
    int id_;
    std::string name_;
    std::string password_;
    CustomerType type_;
    ContactInfrormation contact_;
    std::vector<std::string> accounts_;
    std::vector<int> loansIdList_;
    CustomerProfile profile_;
    CreditSnapshot snapshot_;
    friend class CreditSnepshotServices;

};
