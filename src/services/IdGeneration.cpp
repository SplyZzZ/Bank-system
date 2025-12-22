#include "services/IdGeneration.h"

int IdGeneration::next()
{
    static int currentID = 1;
    return currentID++;
}