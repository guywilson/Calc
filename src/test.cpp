#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>

#include "secure_func.h"
#include "types.h"
#include "test.h"
#include "calc.h"
#include "exception.h"

using namespace std;

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

bool testCalculation(char *pszCalculation, int calcLen, double expectedResult)
{
	double		result = 0.0;
	bool		isSuccess = true;
	
	cout << "\nTesting calculation:" << endl;
	cout << "\t" << pszCalculation << endl;;
	
	result = Calculator::evaluate(pszCalculation, calcLen);

	cout << "\tActual ["  << std::setprecision(4) << result << "] Expected [" << expectedResult << "]" << endl;
	isSuccess = (assertEqualTo(result, expectedResult) != 0);
	
	return isSuccess;
}

bool testValidation(char *pszCalculation, int calcLen)
{
	bool		isSuccess = false;
	
	cout << "\nTesting calculation:" << endl;
	cout << "\t" << pszCalculation << endl;
	
	try {
		Calculator::evaluate(pszCalculation, calcLen);
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
	char 			szCalculation[1024];
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
		strcpy_s(szCalculation, 1024, testCalculations[i].testCalc);
		if (testCalculation(szCalculation, 1024, testCalculations[i].expected)) {
			passCount++;
		}
		else {
			failCount++;
		}
	}

	for (i = 0;i < 4;i++) {
		testCount++;
		strcpy_s(szCalculation, 1024, testValidations[i]);
		if (testValidation(szCalculation, 1024)) {
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