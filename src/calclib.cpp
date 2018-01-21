#include <string>

#include "calc.h"
#include "calclib.h"

using namespace std;

string result;

string & calculate(const string & expression)
{
    Calculator * calc = new Calculator();
    
	result = calc->evaluate(expression);

    delete calc;
    
	return result;
}
