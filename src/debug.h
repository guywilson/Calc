
#ifndef _INCL_DEBUG
#define _INCL_DEBUG

class DebugHelper
{
	private:
		bool					isDebugOn;
		
	public:
		DebugHelper();
		
		static DebugHelper *	getInstance();
		
		void					setDebugOn();
		void					setDebugOff();
		void					setDebug(bool toggle);
		
		bool					getDebugState();
};

#endif
