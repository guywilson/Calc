#include <string>
#include <cln/cln.h>

#include "stack.h"
#include "types.h"

using namespace std;
using namespace cln;

#ifndef _INCL_CALC
#define _INCL_CALC

class Calculator
{
	private:
        Base            _base;
        
		void            _convertToRPN(const string & expression, Queue * outputQueue);

	public:
                        Calculator();
                      
        Base            getMode();
        void            setMode(Base b);
        
        string          getModeStr();
                      
		cl_N            evaluate(const string & expression, string * resultBuffer);
		string *        evaluate(const string & expression);

		void            store(int memoryNum, cl_N result);
        cl_N            recall(int memoryNum);
};

#endif
