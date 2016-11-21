
#include "debug.h"

static DebugHelper * instance = nullptr;

DebugHelper::DebugHelper()
{
	isDebugOn = false;
}

DebugHelper * DebugHelper::getInstance()
{
	if (instance == nullptr) {
		instance = new DebugHelper();
	}
	
	return instance;
}

void DebugHelper::setDebugOn()
{
	isDebugOn = true;
}

void DebugHelper::setDebugOff()
{
	isDebugOn = false;
}

void DebugHelper::setDebug(bool toggle)
{
	isDebugOn = toggle;
}

bool DebugHelper::getDebugState()
{
	return isDebugOn;
}