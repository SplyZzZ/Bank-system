cmake_minimum_required(VERSION 3.16)

project(Bank VERSION 1.0.0)

add_library(bank_lib STATIC
    src/core/Account.cpp
    src/core/Customer.cpp
    src/core/Loans.cpp
    src/services/BankSystem.cpp
    src/services/CreditSnepshotServices.cpp
    src/services/IdGeneration.cpp
    src/services/Transaction.cpp
    src/ui/report/Report.cpp
    src/ui/report/ReportAccountStatus.cpp
    src/ui/report/ReportTransaction.cpp
    src/ui/BankSystemMenu.cpp
    src/utils/ConsoleHelper.cpp
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_include_directories(bank_lib PUBLIC
 ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(bank_lib PUBLIC cxx_std_20)
add_executable(Bank_app
src/main.cpp
)
target_link_libraries(Bank_app PRIVATE bank_lib)
target_compile_features(Bank_app PRIVATE cxx_std_20)
