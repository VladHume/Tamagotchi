#include "PrintUtility.h"
#include <iomanip>


void PrintUtility::cleanScreen()
{
    system("clear");
}

std::ostream &center(std::ostream &stream)
{
    stream.widght(40);
    return stream;
}