#include <iostream>
#include <limits>
#include <iomanip>
#include <stdio.h>
#include <string.h>

#include "secure_func.h"
#include "types.h"
#include "token.h"
#include "calc.h"
#include "test.h"
#include "exception.h"
#include "debug.h"

#define CALC_BUFFER_LEN				1024

using namespace std;

void removeNewLine(char *pszCalculation, size_t bufferLength);
void printHelp(void);

int main(int argc, char *argv[])
{
	char			szCalculation[CALC_BUFFER_LEN];
	double			result;
	int				i;
	bool			loop;
	bool			hasParams = false;
	DebugHelper *	dbg;
	
	szCalculation[0] = 0;
	
	if (argc > 1) {
		for (i = 1;i < argc;i++) {
			strcat_s(szCalculation, CALC_BUFFER_LEN, argv[i]);
		}
	
		hasParams = true;
	}

	dbg = DebugHelper::getInstance();
	
	loop = true;
		
	while (loop) {
		if (!(hasParams && strlen(szCalculation) > 0)) {
			cout << "calc> ";
			cin.getline(szCalculation, CALC_BUFFER_LEN);
			removeNewLine(szCalculation, CALC_BUFFER_LEN);
		}

		if (strlen(szCalculation) == 0) {
			continue;
		}
		
		if (strncmp(szCalculation, "exit", 4) == 0) {
			loop = false;
		}
		else if (strncmp(szCalculation, "test", 4) == 0) {
			runTestSuite();
		}
		else if (strncmp(szCalculation, "dbgon", 5) == 0) {
			dbg->setDebugOn();
		}
		else if (strncmp(szCalculation, "dbgoff", 6) == 0) {
			dbg->setDebugOff();
		}
		else if (strncmp(szCalculation, "help", 4) == 0 || strncmp(szCalculation, "?", 1) == 0) {
			printHelp();
		}
		else {
			try {
				result = Calculator::evaluate(szCalculation, CALC_BUFFER_LEN);
				cout << szCalculation << " = " << std::setprecision(12) << result << endl;
			}
			catch (Exception * e) {
				cout << "Caught exception: " << e->getExceptionString() << endl;
			}
		}
		
		/*
		** Just exit if we supplied the calculation
		** as a program argument...
		*/
		if (hasParams) {
			loop = false;
		}
	}
	
	return 0;
}

void removeNewLine(char *pszCalculation, size_t bufferLength)
{
	int		i;
	int		len = (int)strlen(pszCalculation);
	char	ch;
	
	for (i = 0;i < len && i < (int)bufferLength;i++) {
		ch = pszCalculation[i];
		
		if (ch == '\n' || ch == '\r') {
			pszCalculation[i] = 0;
		}
	}
}

void printHelp(void)
{
	cout << "\nOperators supported:" << endl;
	cout << "\t+, -, *, /" << endl;
	cout << "\t^ (power, e.g. x to the power of y)" << endl << endl;
	cout << "\tNesting is achieved with braces ()" << endl << endl;
	cout << "Functions supported:" << endl;
	cout << "\tsin(x)\treturn the sine of the angle x degrees" << endl;
	cout << "\tcos(x)\treturn the cosine of the angle x degrees" << endl;
	cout << "\ttan(x)\treturn the tangent of the angle x degrees" << endl;
	cout << "\tasin(x)\treturn the angle in degrees of arcsine(x)" << endl;
	cout << "\tacos(x)\treturn the angle in degrees of arccosine(x)" << endl;
	cout << "\tatan(x)\treturn the angle in degrees of arctangent(x)" << endl;
	cout << "\tsqrt(x)\treturn the square root of x" << endl;
	cout << "\tlog(x)\treturn the log of x" << endl;
	cout << "\tlog10(x)\treturn the log of x" << endl;
	cout << "\tfact(x)\treturn the factorial of x" << endl << endl;
	cout << "Constants supported:" << endl;
	cout << "\tpi\tthe ratio pi" << endl;
	cout << "\tc\tthe speed of light in a vacuum" << endl << endl;
	cout << "Commands supported:" << endl;
	cout << "\ttest\tSelf test of the calculator" << endl;
	cout << "\thelp\tThis help text" << endl;
	cout << "\tdbgon\tTurn on debugging output" << endl;
	cout << "\tdbgoff\tTurn off debugging output" << endl;
	cout << "\texit\tExit the calculator" << endl << endl;
}