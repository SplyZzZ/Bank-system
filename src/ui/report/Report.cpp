#include "ui/report/Report.h"
#include "ui/report/StructReport.h"
#include <iostream>
#include <iomanip>
StructReport Report::genereteReport()
{
    build();
    return doc_;
}
void Report::build()
{
   
}
Report::~Report() = default;
void Report::print(const StructReport& doc)
{
    if (doc.header.empty()) return;

    const size_t cols = doc.header.size();
    std::vector<size_t> colWidths(cols, 0);

    for (size_t i = 0; i < cols; ++i)
    {
        colWidths[i] = doc.header[i].size();
    }

    for (const auto& row : doc.informations)
    {
        for (size_t i = 0; i < std::min(cols, row.size()); ++i)
        {
            colWidths[i] = std::max(colWidths[i], row[i].size());
        }
    }

    for (auto& w : colWidths) w += 2;

    auto printSeparator = [&]()
    {
        for (size_t i = 0; i < cols; ++i)
        {
            std::cout << '+' << std::string(colWidths[i], '-');
        }
        std::cout << "+\n";
    };

    std::cout << "\n" << doc.title << "\n";

    printSeparator();

  
    for (size_t i = 0; i < cols; ++i)
    {
        std::cout << "|" << std::left << std::setw(colWidths[i]) << doc.header[i];
    }
    std::cout << "|\n";

    printSeparator();

    for (const auto& row : doc.informations)
    {
        for (size_t i = 0; i < cols; ++i)
        {
            std::string cell = (i < row.size()) ? row[i] : "";
            std::cout << "|" << std::left << std::setw(colWidths[i]) << cell;
        }
        std::cout << "|\n";
    }

    printSeparator();
}