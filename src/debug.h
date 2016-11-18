#ifndef _INCL_DEBUG
#define _INCL_DEBUG

#define DEBUG_LEVEL_ENTRY_EXIT			0x10
#define DEBUG_LEVEL_INFO				0x08
#define DEBUG_LEVEL_DEBUG				0x04
#define DEBUG_LEVEL_WARNING				0x02
#define DEBUG_LEVEL_ERROR				0x01
#define DEBUG_LEVEL_ALL					DEBUG_LEVEL_ENTRY_EXIT | DEBUG_LEVEL_INFO | DEBUG_LEVEL_DEBUG | DEBUG_LEVEL_WARNING | DEBUG_LEVEL_ERROR

void initDebug(bool debugSwitch, unsigned short usLevel);
bool isDebugOn(unsigned short usLevel);

#endif
