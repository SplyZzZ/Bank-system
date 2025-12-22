#pragma once
#include "../../core/OperationType.h"
#include <string>
inline std::string operationTypeToString(OperationType type)
{
    switch (type)
    {
    case OperationType::introduction: { return "Introduction"; }
    case OperationType::transfer: { return "Transfer"; }
    case OperationType::removal: { return "Removal"; }
    default:{ return "Unknown"; }
    }
}