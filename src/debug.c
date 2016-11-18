#include <stdio.h>

#include "types.h"


static bool				bDebugOn;
static unsigned short	usDebugLevel;

void initDebug(bool debugSwitch, unsigned short usLevel)
{
	bDebugOn = debugSwitch;
	usDebugLevel = usLevel;
}

bool isDebugOn(unsigned short usLevel)
{
	return (bDebugOn && (usDebugLevel & usLevel));
}
