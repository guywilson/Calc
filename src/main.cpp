#include <iostream>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <cln/cln.h>

#include "secure_func.h"
#include "types.h"
#include "token.h"
#include "calc.h"
#include "test.h"
#include "exception.h"
#include "debug.h"

using namespace std;
using namespace cln;

void printHelp(void);

int main(int argc, char *argv[])
{
	string						calculation;
    string                      resultBuffer;
	int							i;
	bool						loop;
	bool						hasParams = false;
	cl_N						result = 0.0;
	DebugHelper *				dbg;
	istreambuf_iterator<char>	eos;

	if (argc > 1) {
		for (i = 1;i < argc;i++) {
			calculation += argv[i];
		}

		hasParams = true;
	}

	dbg = DebugHelper::getInstance();

    Calculator * calc = new Calculator();
    
	if (!hasParams) {
		cout << "Welcome to Calc. A command line scientific calculator." << endl;
		cout << "Type a calculation or command at the prompt, type 'help' for info." << endl << endl;
	}

	loop = true;

	while (loop) {
		if (!hasParams) {
			cout << "calc [" << calc->getModeStr() << "]> ";
			getline(cin, calculation);

			if (dbg->getDebugState()) {
				cout << "Calculation entered = [" << calculation << "]" << endl << endl;
			}
		}

		if (calculation.length() == 0) {
			continue;
		}

		if (calculation.compare(0, 4, "exit") == 0 || calculation.compare(0, 4, "quit") == 0 || calculation[0] == 'q') {
			loop = false;
		}
		else if (calculation.compare(0, 4, "test") == 0) {
			runTestSuite();
		}
		else if (calculation.compare(0, 5, "dbgon") == 0) {
			dbg->setDebugOn();
		}
		else if (calculation.compare(0, 6, "dbgoff") == 0) {
			dbg->setDebugOff();
		}
		else if (calculation.compare(0, 5, "memst") == 0) {
			int memoryNum = 0;

			if (calculation.length() > 5) {
				memoryNum = atoi(calculation.substr(5).c_str());
			}

			calc->store(memoryNum, result);
		}
		else if (calculation.compare(0, 5, "memr") == 0) {
            for (i = 0;i < 10;i++) {
                string s;
                cl_N mem = calc->recall(i);
                Operand::toString(mem, calc->getMode(), &s);
                cout << "[" << i << "] = " << s << "; ";
            }
            
            cout << endl;
		}
		else if (calculation.compare(0, 3, "dec") == 0) {
            calc->setMode(Dec);

            string s;
            Operand::toString(result, Dec, &s);
            
            cout << "Result = " << s << endl;
		}
		else if (calculation.compare(0, 3, "hex") == 0) {
            calc->setMode(Hex);
            
            string s;
            Operand::toString(result, Hex, &s);
            
            cout << "Result = " << s << endl;
		}
		else if (calculation.compare(0, 3, "bin") == 0) {
            calc->setMode(Bin);
            
            string s;
            Operand::toString(result, Bin, &s);
            
            cout << "Result = " << s << endl;
		}
		else if (calculation.compare(0, 4, "help") == 0 || calculation[0] == '?') {
			printHelp();
		}
		else {
			try {
				result = calc->evaluate(calculation, &resultBuffer);

				cout << calculation << " = " << resultBuffer << endl;
                
                resultBuffer.clear();
			}
			catch (Exception * e) {
				cout << "Caught exception: " << e->getExceptionString() << endl;
			}
		}

		if (hasParams) {
			loop = false;
		}
	}

    delete calc;
    
	return 0;
}

void printHelp(void)
{
	cout << "\nOperators supported:" << endl;
	cout << "\t+, -, *, /, % (Modulo)" << endl;
	cout << "\t& (AND), | (OR), ~ (XOR)" << endl;
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
	cout << "\tln(x)\treturn the natural log of x" << endl;
	cout << "\tfact(x)\treturn the factorial of x" << endl;
	cout << "\tmem(n)\tthe value in memory location n, where n is 0 - 9" << endl << endl;
	cout << "Constants supported:" << endl;
	cout << "\tpi\tthe ratio pi" << endl;
	cout << "\tc\tthe speed of light in a vacuum" << endl << endl;
	cout << "Commands supported:" << endl;
	cout << "\tmemstn\tStore the last result in memory location n (0 - 9)" << endl;
    cout << "\tdec\tSwitch to decimal mode" << endl;
    cout << "\thex\tSwitch to hexadecimal mode" << endl;
    cout << "\tbin\tSwitch to binary mode" << endl;
	cout << "\ttest\tSelf test of the calculator" << endl;
	cout << "\thelp\tThis help text" << endl;
	cout << "\tdbgon\tTurn on debugging output" << endl;
	cout << "\tdbgoff\tTurn off debugging output" << endl;
	cout << "\texit\tExit the calculator" << endl << endl;
}
