#pragma once
#include <cstdint>
#include <optional>
#include <string>
class CustomerProfile
{
    public:
    std::string dateOfBirth;
    std::optional<int64_t> monthlyIncome_;
};
