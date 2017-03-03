#include <string>
#include <iostream>

#include "calclib.h"

using namespace std;

int main(void)
{
	string		expression;
	string * 	result;
	
	cout << "Enter expression : ";
	getline(cin, expression);
	
	result = calculate(expression);
	
	cout << endl << expression << " = " << *result << endl;
	
	return 0;
}
