#pragma once
#include <string>
#include "../core/AccountType.h"
inline std::string accountTypeToString(const AccountType type)
{
    switch(type)
    {
    case AccountType::Current: { return "Current"; }
    case AccountType::Savings: { return "Savings"; }
    default: { return "Unknown"; }
    }
}
