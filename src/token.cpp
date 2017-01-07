#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "secure_func.h"
#include "token.h"
#include "exception.h"
#include "debug.h"

using namespace std;

static double _memory[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};


Token::Token(char * pszToken)
{
	strcpy_s(this->_szToken, TOKEN_LENGTH, pszToken);
}

Token::Token(char * pszToken, const char * pszClassName) : Token(pszToken)
{
	DebugHelper * dbg = DebugHelper::getInstance();
	
	if (dbg->getDebugState()) {
		cout << "Creating Token of type " << pszClassName << " with token '" << pszToken << "'" << endl;
	}
	
	setClass(pszClassName);
}

void Token::setClass(const char * pszClassName)
{
	strcpy_s(this->_szClassName, CLASSNAME_LENGTH, pszClassName);
}

char * Token::getToken()
{
	return this->_szToken;
}

char * Token::getClass()
{
	return this->_szClassName;
}

bool Token::isOperand(char * pszToken) {
	int		i;
	bool	ret = true;
	size_t	tokenLength = strlen(pszToken);
	
	if (pszToken[0] == '-' && tokenLength == 1) {
		// Must be the '-' operator...
		ret = false;
	}
	else {
		for (i = 0;i < (int)tokenLength;i++) {
			if (!isdigit(pszToken[i]) && pszToken[i] != '.' && pszToken[i] != '-') {
				ret = false;
				break;
			}
		}
	}
	
	return ret;
}
bool Token::isOperatorPlus(char * pszToken) {
	return pszToken[0] == '+';
}
bool Token::isOperatorMinus(char * pszToken) {
	bool	ret = true;
	size_t	tokenLength = strlen(pszToken);
	
	if (pszToken[0] == '-') {
		if (tokenLength > 1 && isdigit(pszToken[1])) {
			ret = false;
		}
	}
	else {
		ret = false;
	}
	
	return ret;
}
bool Token::isOperatorMultiply(char * pszToken) {
	return pszToken[0] == '*';
}
bool Token::isOperatorDivide(char * pszToken) {
	return pszToken[0] == '/';
}
bool Token::isOperatorPower(char * pszToken) {
	return pszToken[0] == '^';
}
bool Token::isOperator(char * pszToken) {
	return (
		isOperatorPlus(pszToken) ||
		isOperatorMinus(pszToken) || 
		isOperatorMultiply(pszToken) || 
		isOperatorDivide(pszToken) || 
		isOperatorPower(pszToken));
}
bool Token::isBraceLeft(char * pszToken) {
	return (pszToken[0] == '(' || pszToken[0] == '[' || pszToken[0] == '{');
}
bool Token::isBraceRight(char * pszToken) {
	return (pszToken[0] == ')' || pszToken[0] == ']' || pszToken[0] == '}');
}
bool Token::isBrace(char * pszToken) {
	return (isBraceLeft(pszToken) || isBraceRight(pszToken));
}
bool Token::isConstantPi(char * pszToken) {
	return !strncmp(pszToken, "pi", 2);
}
bool Token::isConstantC(char * pszToken) {
	return !strncmp(pszToken, "c", 1);
}
bool Token::isConstant(char * pszToken)
{
	return (isConstantPi(pszToken) || isConstantC(pszToken));
}
bool Token::isFunctionSine(char * pszToken) {
	return !strncmp(pszToken, "sin", 3);
}
bool Token::isFunctionCosine(char * pszToken) {
	return !strncmp(pszToken, "cos", 3);
}
bool Token::isFunctionTangent(char * pszToken) {
	return !strncmp(pszToken, "tan", 3);
}
bool Token::isFunctionArcSine(char * pszToken) {
	return !strncmp(pszToken, "asin", 4);
}
bool Token::isFunctionArcCosine(char * pszToken) {
	return !strncmp(pszToken, "acos", 4);
}
bool Token::isFunctionArcTangent(char * pszToken) {
	return !strncmp(pszToken, "atan", 4);
}
bool Token::isFunctionSquareRoot(char * pszToken) {
	return !strncmp(pszToken, "sqrt", 4);
}
bool Token::isFunctionLogarithm(char * pszToken) {
	return !strncmp(pszToken, "log", 3);
}
bool Token::isFunctionLogarithm10(char * pszToken) {
	return !strncmp(pszToken, "log10", 5);
}
bool Token::isFunctionFactorial(char * pszToken) {
	return !strncmp(pszToken, "fact", 4);
}
bool Token::isFunctionMemory(char * pszToken) {
	return !strncmp(pszToken, "mem", 3);
}
bool Token::isFunction(char * pszToken) {
	return (
		isFunctionSine(pszToken) || 
		isFunctionCosine(pszToken) || 
		isFunctionTangent(pszToken) || 
		isFunctionArcSine(pszToken) || 
		isFunctionArcCosine(pszToken) || 
		isFunctionArcTangent(pszToken) || 
		isFunctionSquareRoot(pszToken) || 
		isFunctionLogarithm(pszToken) ||
		isFunctionLogarithm10(pszToken) ||
		isFunctionFactorial(pszToken) ||
		isFunctionMemory(pszToken));
}


Operator::Operator(char * pszToken) : Token(pszToken, "Operator")
{
	if (Token::isOperatorPlus(pszToken)) {
		op = Plus;
		precedence = 2;
		assoc = Left;
	}
	else if (Token::isOperatorMinus(pszToken)) {
		op = Minus;
		precedence = 2;
		assoc = Left;
	}
	else if (Token::isOperatorMultiply(pszToken)) {
		op = Multiply;
		precedence = 3;
		assoc = Left;
	}
	else if (Token::isOperatorDivide(pszToken)) {
		op = Divide;
		precedence = 3;
		assoc = Left;
	}
	else if (Token::isOperatorPower(pszToken)) {
		op = Power;
		precedence = 4;
		assoc = Right;
	}
}

Operator::Operator(char *pszToken, const char *pszClassName) : Token(pszToken, pszClassName)
{
}

void Operator::setPrecedence(int precedence)
{
	this->precedence = precedence;
}

int Operator::getPrecedence()
{
	return this->precedence;
}

Associativity Operator::getAssociativity()
{
	return this->assoc;
}

Op Operator::getOp()
{
	return this->op;
}

Operand * Operator::evaluate(Operand * o1, Operand * o2)
{
	Operand * result;
	
	switch (getOp()) {

		case Plus:
			result = new Operand(o1->getValue() + o2->getValue());
			break;

		case Minus:
			result = new Operand(o1->getValue() - o2->getValue());
			break;

		case Multiply:
			result = new Operand(o1->getValue() * o2->getValue());
			break;

		case Divide:
			result = new Operand(o1->getValue() / o2->getValue());
			break;

		case Power:
			result = new Operand(pow(o1->getValue(), o2->getValue()));
			break;
	}
	
	return result;
}


Brace::Brace(char * pszToken) : Token(pszToken, "Brace")
{
	if (Token::isBraceLeft(pszToken)) {
		type = Open;
	}
	else if (Token::isBraceRight(pszToken)) {
		type = Close;
	}
}

BraceType Brace::getType()
{
	return this->type;
}


Operand::Operand(char * pszToken) : Token(pszToken, "Operand")
{
	this->value = atof(pszToken);
}

Operand::Operand(double x)
{
	this->value = x;
}

Operand::Operand(char * pszToken, const char * pszClassName) : Token(pszToken, pszClassName)
{
}

double Operand::getValue()
{
	return this->value;
}


Constant::Constant(char * pszToken) : Operand(pszToken, "Constant")
{
	if (Token::isConstantPi(pszToken)) {
		constant = Pi;
		value = _pi();
	}
	else if (Token::isConstantC(pszToken)) {
		constant = C;
		value = 299792458.0; // in m/s
	}
}

/******************************************************************************
*
* Calculate Pi using Nilakantha's infinite series:
*
* Pi = 3 + 4/(2 * 3 * 4) - 4/(4 * 5 * 6) + 4/(6 * 7 * 8) - 4/(8 * 9 * 10)...
*
******************************************************************************/
double Constant::_pi()
{
	double			pi;
	double			numerator;
	bigint			d1;
	bigint			d2;
	bigint			d3;
	bigint			d4;
	bigint			d5;
	bigint			i;
	
	pi = 3.0;
	numerator = 4.0;
	d1 = 2L;
	d2 = 3L;
	d3 = 4L;
	d4 = 5L;
	d5 = 6L;
	i = 0;
	
	/*
	** Calculate pi using 4 million terms of the series...
	*/
	for (i = 0;i < 1000000;i++) {
		pi = pi + (numerator / ((double)(d1 * d2 * d3))) - (numerator / ((double)(d3 * d4 * d5)));

		d1 += 4L;
		d2 += 4L;
		d3 += 4L;
		d4 += 4L;
		d5 += 4L;
	}
	
	return pi;
}

Const Constant::getConstant()
{
	return this->constant;
}


Function::Function(char * pszToken) : Operator(pszToken, "Function")
{
	if (Token::isFunctionSine(pszToken)) {
		function = Sine;
		numArguments = 1;
	}
	else if (Token::isFunctionCosine(pszToken)) {
		function = Cosine;
		numArguments = 1;
	}
	else if (Token::isFunctionTangent(pszToken)) {
		function = Tangent;
		numArguments = 1;
	}
	else if (Token::isFunctionArcSine(pszToken)) {
		function = ArcSine;
		numArguments = 1;
	}
	else if (Token::isFunctionArcCosine(pszToken)) {
		function = ArcCosine;
		numArguments = 1;
	}
	else if (Token::isFunctionArcTangent(pszToken)) {
		function = ArcTangent;
		numArguments = 1;
	}
	else if (Token::isFunctionSquareRoot(pszToken)) {
		function = SquareRoot;
		numArguments = 1;
	}
	else if (Token::isFunctionLogarithm(pszToken)) {
		function = Logarithm;
		numArguments = 1;
	}
	else if (Token::isFunctionLogarithm10(pszToken)) {
		function = Logarithm10;
		numArguments = 1;
	}
	else if (Token::isFunctionFactorial(pszToken)) {
		function = Factorial;
		numArguments = 1;
	}
	else if (Token::isFunctionMemory(pszToken)) {
		function = Memory;
		numArguments = 1;
	}
	
	setPrecedence(5);
}

Operand * Function::evaluate(Operand * arg1)
{
	Operand *		result;
	double			degreesToRadians = (3.14159265358979323846 / 180.0);
	double			radiansToDegrees = (180.0 / 3.14159265358979323846);

	switch (this->function) {
		
		case Sine:
			result = new Operand(sin(arg1->getValue() * degreesToRadians));
			break;
		
		case Cosine:
			result = new Operand(cos(arg1->getValue() * degreesToRadians));
			break;
		
		case Tangent:
			result = new Operand(tan(arg1->getValue() * degreesToRadians));
			break;
		
		case ArcSine:
			result = new Operand(asin(arg1->getValue()) * radiansToDegrees);
			break;
		
		case ArcCosine:
			result = new Operand(acos(arg1->getValue()) * radiansToDegrees);
			break;
		
		case ArcTangent:
			result = new Operand(atan(arg1->getValue()) * radiansToDegrees);
			break;
		
		case SquareRoot:
			result = new Operand(sqrt(arg1->getValue()));
			break;
		
		case Logarithm:
			result = new Operand(log(arg1->getValue()));
			break;
		
		case Logarithm10:
			result = new Operand(log10(arg1->getValue()));
			break;
		
		case Factorial:
			result = new Operand((double)_factorial((long)arg1->getValue()));
			break;
		
		case Memory:
			result = new Operand(_memory[(int)arg1->getValue()]);
			break;
		
		default:
			break;
	}
	
	return result;
}

bigint Function::_factorial(unsigned long arg)
{
	unsigned long	index;
	bigint			result;
	
	result = arg;
	
	if (arg > 1) {
		for (index = arg - 1;index > 0;index--) {
			result *= index;
		}
	}
	
	return result;
}

void Function::memoryStore(int memoryNum, double value)
{
	_memory[memoryNum] = value;
}


Token * TokenFactory::createToken(char * pszToken)
{
	Token * t;
	
	if (Token::isOperand(pszToken)) {
		t = new Operand(pszToken);
	}
	else if (Token::isOperator(pszToken)) {
		t = new Operator(pszToken);
	}
	else if (Token::isBrace(pszToken)) {
		t = new Brace(pszToken);
	}
	else if (Token::isConstant(pszToken)) {
		t = new Constant(pszToken);
	}
	else if (Token::isFunction(pszToken)) {
		t = new Function(pszToken);
	}
	else {
		throw new Exception(
					ERR_INVALID_TOKEN,
					"Invalid token found",
					__FILE__,
					"TokenFactory",
					"createToken()",
					__LINE__);
	}
	
	return t;
}


CalcTokenizer::CalcTokenizer(char * pszExpression, size_t bufferLength)
{
	this->pszExpression = pszExpression;
	startIndex = 0;
	endIndex = 0;
	expressionLen = strlen(pszExpression);
	maxLen = bufferLength;
	
	if (expressionLen > maxLen) {
		throw new Exception(
					ERR_ARRAY_OVERFLOW,
					"String length exceeds maximum buffer length",
					__FILE__,
					"CalcTokenizer",
					"CalcTokenizer()",
					__LINE__);
	}
}

bool CalcTokenizer::_isToken(char ch)
{
	return (strchr(szTokens, ch) != NULL);
}

bool CalcTokenizer::_isWhiteSpace(char ch)
{
	return (strchr(szWhiteSpace, ch) != NULL);
}

int CalcTokenizer::_findNextTokenPos()
{
	int		i;
	char	ch;
	bool	lookingForWhiteSpace = true;
	int		tokenLen = 0;
	
	for (i = startIndex;i < (int)expressionLen && i < (int)maxLen;i++) {
		ch = pszExpression[i];
		
		if (lookingForWhiteSpace) {
			if (_isWhiteSpace(ch)) {
				startIndex++;
				continue;
			}
			else {
				lookingForWhiteSpace = false;
			}
		}
		
		if (_isWhiteSpace(ch)) {
			return i;
		}
		if (_isToken(ch)) {
			/*
			** Do we have a token on it's own, or is it a delimiter...
			*/
			if (tokenLen > 0) {
				// The token is the delimiter to another token...
				return i;
			}
			else {
				/*
				** If this is the '-' character and if the next char is a digit (0-9)
				** and the previous char is not a ')' or a digit then this must be a -ve number, 
				** not the '-' operator...
				*/
				if (ch == '-' && isdigit(pszExpression[i + 1])) {
					bool isNegativeOperand = false;
					
					if (i > 1) {
						bool isPreviousCharBrace = Token::isBraceRight(&pszExpression[i - 1]);
						bool isPreviousCharDigit = isdigit(pszExpression[i - 1]) != 0 ? true : false;
						
						if (!isPreviousCharBrace && !isPreviousCharDigit) {
							isNegativeOperand = true;
						}
						else {
							isNegativeOperand = false;
						}
					}
					else if (i == 0) {
						// We're at the begininng of the expression, must be
						// a -ve operand
						isNegativeOperand = true;
					}

					if (isNegativeOperand) {
						// Found a -ve number...
						continue;
					}
					else {
						return i + 1;
					}
				} 
				else {
					// The token is the token we want to return...
					return i + 1;
				}
			}
		}
		
		tokenLen++;
		
		/*
		** If we haven't returned yet and we're at the end of
		** the expression, we must have an operand at the end 
		** of the expression...
		*/
		if (i == (int)(expressionLen - 1)) {
			return i + 1;
		}
	}
	
	return -1;
}

bool CalcTokenizer::hasMoreTokens()
{
	int pos = _findNextTokenPos();
	
	if (pos > 0) {
		endIndex = pos;
		return true;
	}
	
	return false;
}

Token * CalcTokenizer::nextToken()
{
	char		szToken[TOKEN_LENGTH];
	int			tokenLen;
	
	tokenLen = endIndex - startIndex;

#ifdef _WIN32	
	strncpy_s(szToken, TOKEN_LENGTH, &pszExpression[startIndex], tokenLen);
#else
	strncpy(szToken, &pszExpression[startIndex], tokenLen);
#endif
	szToken[tokenLen] = 0;
	
	startIndex = endIndex;
	
	return TokenFactory::createToken(szToken);
}
