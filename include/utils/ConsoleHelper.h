#pragma once
#include <string>
#include <iostream>
#include <limits>
std::string readLine();
template <typename T>
T readNumber()
{
    T value;

    while (true)
    {
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again: ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}
