
#include "services/BankSystem.h"
#include "ui/BankSystemMenu.h"
int main()
{
    BankSystem bank;
    UIBankSystem UIBank(bank);
    UIBank.run();
}
