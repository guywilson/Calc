#include "system.h"

static int _precision = FLOAT_PRECISION;

void System::setPrecision(int p)
{
    _precision = p;
}

int System::getPrecision()
{
    return _precision;
}
