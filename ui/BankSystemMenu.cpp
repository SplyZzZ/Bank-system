#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>
#include "BankSystemMenu.h"
#include "core/ContactInformation.h"
#include "services/BankSystem.h"
#include "utils/ConsoleHelper.h"
UIBankSystem::UIBankSystem(BankSystem& bank) : bank_(bank) {}
void UIBankSystem::printMenu()
{
    std::cout << "\n=== BANK SYSTEM ===\n";
    std::cout << "1. Add customer\n";
    std::cout << "2. Open account\n";
    std::cout << "3. Close account\n";
    std::cout << "4. Deposit money\n";
    std::cout << "5. Withdraw money\n";
    std::cout << "6. Transfer money\n";
    std::cout << "7. Issue loan\n";
    std::cout << "8. Show reports\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose option: ";
}
void UIBankSystem::run()
{

    int choice = -1;

    while (choice != 0)
    {
        printMenu();
        std::cin >> choice;

        try {
            switch (choice)
            {
                case 1: addCustomer(); break;
                // case 2: openAccount(); break;
                // case 3: closeAccount(); break;
                // case 4: deposit(); break;
                // case 5: withdraw(); break;
                // case 6: transfer(); break;
                // case 7: loan(); break;
                // case 8: report(); break;
                case 0: std::cout << "Exit\n"; break;
                default: std::cout << "Invalid option\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
}
void UIBankSystem::addCustomer()
{
    std::cout << "Введіть ім'я клієнта: ";
    std::string name = readLine();
    ContactInfrormation customerContact;

    std::cout << "Бажаєте ввести адресу?\n1 - Так\nБудь яка інша клавіша - Ні\n";
    int selection = readNumber<int>();
    if(selection == 1)
    {
         std::cout << "Введіть адресу клієнта: ";
        customerContact.address = readLine();
    }
    std::cout << "Бажаєте ввести емеїл?\n1 - Так\nБудь яка інша клавіша - Ні\n";
    selection = readNumber<int>();
    if(selection == 1)
    {
    std::cout << "Введіть емеїл клієнта: ";
    customerContact.email = readLine();
    }
    std::cout << "Введіть номер телефону клієнта: ";
    customerContact.phone = readLine();
    while(true)
    {
        try
        {
            bank_.addCustomer(name, customerContact);
            break;
        }
        catch(std::exception& e)
        {
             std::cout << "Error: " << e.what() << "\n";
             std::cout << "Please try again.\n";
        }
    }


}


