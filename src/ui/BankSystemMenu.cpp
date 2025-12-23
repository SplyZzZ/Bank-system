#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <string>

#include <unistd.h>
#include "ui/BankSystemMenu.h"
#include "core/ContactInformation.h"
#include "core/OperationType.h"
#include "ui/formatters/AccountTypeToString.h"
#include "services/BankSystem.h"
#include "utils/ConsoleHelper.h"
#include "ui/formatters/OperationTypeToString.h"
UIBankSystem::UIBankSystem(BankSystem& bank, UserSession& user) : bank_(bank), user_(user) {}
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
    authorization();

    int choice = -1;

    while (choice != 0)
    {
        printMenu();
        choice = readNumber<int>();

        try {
            switch (choice)
            {
                case 1: addCustomer(); break;
                case 2: openAccount(); break;
                case 3: closeAccount(); break;
                case 4: newTransaction(); break;
                // case 5: withdraw(); break;
                // case 6: transfer(); break;
                // case 7: loan(); break;
                // case 8: report(); break;
                // case 0: std::cout << "Exit\n"; break;
                default: std::cout << "Invalid option\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
}
void UIBankSystem::newTransaction()
{
    std::cout << "Виберіть тип транзакції: ";
    std::cout << "0 - " << operationTypeToString(OperationType::introduction) << "\n";
    std::cout << "1 - " << operationTypeToString(OperationType::removal) << "\n";
    std::cout << "2 - " << operationTypeToString(OperationType::transfer) << "\n";
    int selection = readNumber<int>();
    switch (selection) 
    {
        case 0:
        {
            deposit();
            return;
        }
    }
    
}
void UIBankSystem::deposit()
{
   auto ibanList = user_.user_->getAccountsList();
   printIbanList(ibanList);
   
   while(true)
   {
        std::cout << "Введіть рахунок для поповненя: ";
        std::string iban = readLine();
        std::cout << "Введіть суму для поповнення: ";
        uint64_t sum = readNumber<uint64_t>();
        try 
        {
            bank_.createTransaction(OperationType::introduction, sum, iban);
        } catch (const std::exception& e)
        {
        std::cout << "Error: " << e.what() << '\n';
        std::cout << "Для відміни нажміть 1: ";
                    int tmp = readNumber<int>();
                    if(tmp == 1)
                    {
                        return;
                    }
        }
   }
}
void UIBankSystem::printIbanList(const std::vector<std::string>& ibanList)
{
    std::cout << "iban list: ";
    for(const auto& iban : ibanList)
    {
        std::cout << iban << "\n";
    }
}
void UIBankSystem::addCustomer()
{
   
    while(true)
    {
    auto input = readCustomerInput();
        try
        {
            bank_.addCustomer(input.name, input.pass, input.contact);
            std::cout << "Користувача успішно додано!\n";
            break;
        }
        catch(std::exception& e)
        {
             std::cout << "Error: " << e.what() << "\n";
             std::cout << "Please try again.\n";
        }
    }
}
void UIBankSystem::openAccount()
{
    while(true)
    {
        std::cout << "Виберіть тип рахунку: ";

        std::cout << "0 - " << accountTypeToString(AccountType::Current) << "\n";
        std::cout << "1 - "  << accountTypeToString(AccountType::Savings) << "\n";
        int selection = readNumber<int>();
        try
        {
            switch (selection)
            {
            case 0:
            {
                bank_.createAccount(user_.user_->getID(), AccountType::Current);
                return;
            }
            case 1:
            {
                bank_.createAccount(user_.user_->getID(), AccountType::Savings);
                return;
            }
            default:
            {
                std::cout << "No";
                throw std::runtime_error("Incorrect account type");
            }

            }
        }catch(const std::exception& e)
        {
            std::cout << "Error: " << e.what() << "\n";
            std::cout << "Для виходу нажміть 1: ";
            int tmp = readNumber<int>();
            if(tmp == 1)
            {
                return;
            }

        }
    }
        
}
UIBankSystem::MenuResult UIBankSystem::loginMenu()
{
    
    while (true)
    {

        try
        {
            std::cout << "Введіть номер телефону користувача: ";
            std::string phoneNumber = readLine();
            std::cout << "Введіть пароль користувача: ";
            std::string pass = readLine();
            user_.user_ = bank_.login(phoneNumber, pass);
            return MenuResult::Success;
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << "\n";
            std::cout << "Якщо бажаєте зареєструватися натисніть 1: ";

            int tmp = readNumber<int>();
            if (tmp == 1)
            {
                return MenuResult::GoToRegister;
            }

            std::cout << "Please try again.\n";
        }
    }
}
UIBankSystem::MenuResult UIBankSystem::registerMenu()
{

    while(true)
    {
        auto input = readCustomerInput();
        try
        {
            user_.user_ = bank_.addCustomer(input.name, input.pass, input.contact);
            return MenuResult::Success;
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << "\n";
            return MenuResult::Retry;
        }
    }
}
UIBankSystem::CustomerInput UIBankSystem::readCustomerInput()
{
    CustomerInput input;

    std::cout << "Введіть ім'я клієнта: ";
    input.name = readLine();

    std::cout << "Введіть пароль клієнта: ";
    input.pass = readLine();

    std::cout << "Бажаєте ввести адресу?\n1 - Так\nІнше - Ні\n";
    if (readNumber<int>() == 1)
    {
        std::cout << "Введіть адресу клієнта: ";
        input.contact.address = readLine();
    }

    std::cout << "Бажаєте ввести email?\n1 - Так\nІнше - Ні\n";
    if (readNumber<int>() == 1)
    {
        std::cout << "Введіть email клієнта: ";
        input.contact.email = readLine();
    }

    std::cout << "Введіть номер телефону клієнта: ";
    input.contact.phone = readLine();

    return input;
}
void UIBankSystem::authorization()
{
    while (true)
    {
     
        switch (loginMenu())
        {
            case MenuResult::Success:
                return;

            case MenuResult::GoToRegister:
                if(registerMenu() == MenuResult::Success) return;
             
                break;

            case MenuResult::Retry:
                break;
        }
    }
}

