
#include "services/BankSystem.h"
#include "ui/BankSystemMenu.h"


int main()
{
    BankSystem bank;
    UserSession user;
    UIBankSystem UIBank(bank, user);
    UIBank.run();

}
