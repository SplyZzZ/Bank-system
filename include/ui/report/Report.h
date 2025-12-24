#pragma once
#include "StructReport.h"
class Report
{
public:

    StructReport genereteReport();

   virtual ~Report();
   void print(const StructReport& doc);

protected:

    virtual void build();

    StructReport doc_;
};
