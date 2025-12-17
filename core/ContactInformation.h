#pragma once
#include <optional>
#include <string>
struct ContactInfrormation
{
    std::optional<std::string> email;
    std::optional<std::string> phone;
    std::optional<std::string> address;
};
