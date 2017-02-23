#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <cln/cln.h>

#include "secure_func.h"
#include "types.h"
#include "test.h"
#include "calc.h"
#include "exception.h"

using namespace std;
using namespace cln;

int assertEqualTo(double actualResult, double expectedResult)
{
	double		diff = 0.0;

	diff = actualResult - expectedResult;

	if (diff < 0.0) {
		diff = diff * -1;
	}

	if (diff < 0.05) {
		cout << "\nSUCCESS!!" << endl;
		return 1;
	}
	else {
		cout << "\nFAIL!!" << endl;
		return 0;
	}
}

bool testCalculation(string & calculation, double expectedResult)
{
	cl_F		result = 0.0;
	bool		isSuccess = true;
	string		resultBuffer;


	cout << "\nTesting calculation:" << endl;
	cout << "\t" << calculation << endl;;

	result = Calculator::evaluate(calculation, &resultBuffer);

	cout << "\tActual ["  << std::setprecision(4) << double_approx(result) << "] Expected [" << expectedResult << "]" << endl;
	isSuccess = (assertEqualTo(double_approx(result), expectedResult) != 0);

	return isSuccess;
}

bool testValidation(string & calculation)
{
	string		resultBuffer;
	bool		isSuccess = false;

	cout << "\nTesting calculation:" << endl;
	cout << "\t" << calculation << endl;

	try {
		Calculator::evaluate(calculation, &resultBuffer);
	}
	catch (Exception * e) {
		cout << "Exception caught: " << e->getExceptionString() << endl << endl;
		cout << "SUCCESS - VALIDATION FAILURE!!" << endl;
		isSuccess = true;
	}

	return isSuccess;
}

bool runTestSuite(void)
{
	int				passCount = 0;
	int				failCount = 0;
	int				testCount = 0;
	int				i;
	string 			calculation;
	const TESTITEM	testCalculations[] = {
						{"2 + (3 * 4) ^ 2 - 13", 133.00},
						{"12 - ((2 * 3) - (8 / 2) / 0.5) / 12.653", 12.16},
						{"2 ^ 16 - 1", 65535.0},
						{"(((((((1 + 2 * 3)-2)*4)/2)-12)+261)/12) - 5.25", 16.33},
						{"pi + sin(45 + 45)", 4.14},
						{"pi * (2 ^ 2)", 12.57},
						{"3 + 4/(2 * 3 * 4) - 4/(4 * 5 * 6) + 4/(6 * 7 * 8) - 4/(8 * 9 * 10) + 4/(10 * 11 * 12)", 3.14},
						{"84 * -15 + sin(47)", -1259.27},
						{"16 / (3 - 5 + 8) * (3 + 5 - 4)", 10.66}
					};
	const char *	testValidations[] = {
						"((((4(((1 + 2 * 3)-2)*4)/2)-12)+261)/12) - 5.25",
						"(((((((1 + 2 * 3)-2)*4)/2)-12)+261)/12 - 5.25",
						"((((((1 + 2 * 3)-2)*4)/2)-12)+261)/12) - 5.25",
						"84 * -15 + sin47"
					};

	/**************************************************************************
	**
	** ADD TESTS HERE
	**
	**************************************************************************/

	for (i = 0;i < 9;i++) {
		testCount++;
		calculation = testCalculations[i].testCalc;
		if (testCalculation(calculation, testCalculations[i].expected)) {
			passCount++;
		}
		else {
			failCount++;
		}
	}

	for (i = 0;i < 4;i++) {
		testCount++;
		calculation = testValidations[i];
		if (testValidation(calculation)) {
			passCount++;
		}
		else {
			failCount++;
		}
	}

	/**************************************************************************
	**
	** END TESTS
	**
	**************************************************************************/

	/*
	** Print test results...
	*/
	cout << endl << endl << "Total tests run: " << testCount << ", passed: " << passCount << ", failed: " << failCount << endl << endl;

	if (passCount < testCount || testCount == 0) {
		return false;
	}
	else {
		return true;
	}
}
