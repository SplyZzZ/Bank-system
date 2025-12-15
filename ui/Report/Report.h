#include "StructReport.h"
class Report
{
public:

    void genereteReport();
    
    ~Report();

protected:

    virtual Report build() const = 0;

    StructReport doc_;
};