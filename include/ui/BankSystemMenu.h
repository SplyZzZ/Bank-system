#pragma once

#include "core/UserSesion.h"
#include "services/BankSystem.h"
class UIBankSystem
{
public:
    UIBankSystem(BankSystem& bank, UserSession& user);

    void run();

private:
    enum class MenuResult
    {
        Retry,
        GoToRegister,
        Success
    };
    struct CustomerInput
    {
        std::string name;
        std::string pass;
        ContactInfrormation contact;
    };

    BankSystem& bank_;
    UserSession& user_;
    void printMenu();
    MenuResult loginMenu();
    MenuResult registerMenu();
    void authorization();
    CustomerInput readCustomerInput();
    void addCustomer();
    void openAccount();
    // void closeAccount();
    // void deposit();
    // void withdraw();
    // void transfer();
    // void loan();
    // void report();
    
};
