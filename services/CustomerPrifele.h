#pragma once
#include <cstdint>
#include <optional>
#include <string>
class CustomerProfile
{
    protected:
    std::string dateOfBirth;
    std::optional<int64_t> monthlyIncome_;
};
