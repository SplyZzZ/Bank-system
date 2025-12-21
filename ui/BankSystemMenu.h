#pragma once

#include "services/BankSystem.h"


class UIBankSystem
{
public:
    explicit UIBankSystem(BankSystem& bank);

    void run();

private:
    BankSystem& bank_;

    void printMenu();

    void addCustomer();
    void openAccount();
    void closeAccount();
    void deposit();
    void withdraw();
    void transfer();
    void loan();
    void report();
};
