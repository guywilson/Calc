#include <string>

#include "calc.h"
#include "calclib.h"

using namespace std;

string * calculate(const string & expression)
{
	string * r;

    Calculator * calc = new Calculator();
    
	r = calc->evaluate(expression);

    delete calc;
    
	return r;
}
