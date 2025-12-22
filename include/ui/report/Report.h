#pragma once
#include "StructReport.h"
class Report
{
public:

    StructReport genereteReport();

   virtual ~Report();

protected:

    virtual void build();

    StructReport doc_;
};
