#include "ui/report/Report.h"

StructReport Report::genereteReport()
{
    build();
    return doc_;
}
