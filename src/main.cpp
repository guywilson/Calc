#include <iostream>
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
	double			result = 0.0;
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

	if (!hasParams) {
		cout << "Welcome to Calc. A command line scientific calculator." << endl;
		cout << "Type a calculation or command at the prompt, type 'help' for info." << endl << endl;
	}

	loop = true;
	
	while (loop) {
		if (!hasParams) {
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
		else if (strncmp(szCalculation, "memst", 5) == 0) {
			int memoryNum = 0;
			
			if (strlen(szCalculation) > 5) {
				memoryNum = atoi(&szCalculation[5]);
			}
			
			Calculator::store(memoryNum, result);
		}
		else if (strncmp(szCalculation, "help", 4) == 0 || strncmp(szCalculation, "?", 1) == 0) {
			printHelp();
		}
		else {
			try {
				result = Calculator::evaluate(szCalculation, CALC_BUFFER_LEN);
				printf("%s = %.12f\n", szCalculation, result);
			}
			catch (Exception * e) {
				cout << "Caught exception: " << e->getExceptionString() << endl;
			}
		}
		
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
	cout << "\tfact(x)\treturn the factorial of x" << endl;
	cout << "\tmem(n)\tthe value in memory location n, where n is 0 - 9" << endl << endl;
	cout << "Constants supported:" << endl;
	cout << "\tpi\tthe ratio pi" << endl;
	cout << "\tc\tthe speed of light in a vacuum" << endl << endl;
	cout << "Commands supported:" << endl;
	cout << "\tmemstn\tStore the last result in memory location n (0 - 9)" << endl;
	cout << "\ttest\tSelf test of the calculator" << endl;
	cout << "\thelp\tThis help text" << endl;
	cout << "\tdbgon\tTurn on debugging output" << endl;
	cout << "\tdbgoff\tTurn off debugging output" << endl;
	cout << "\texit\tExit the calculator" << endl << endl;
}