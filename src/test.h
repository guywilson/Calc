#ifndef _INCL_TEST
#define _INCL_TEST

typedef struct
{
	const char *testCalc;
	double expected;
}
TESTITEM;

bool runTestSuite(void);

#endif