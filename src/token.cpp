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
using namespace cln;

static cl_N _memory[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};


Token::Token(const string & token)
{
	this->_token = token;
    this->_base = Dec;
}

Token::Token(const string & token, const string & className) : Token(token)
{
	DebugHelper * dbg = DebugHelper::getInstance();

	if (dbg->getDebugState()) {
		cout << "Creating Token of type " << className << " with token '" << token << "'" << endl;
	}

	setClass(className);
}

void Token::setClass(const string & className)
{
	this->_className = className;
}

string & Token::getToken()
{
	return this->_token;
}

string & Token::getClass()
{
	return this->_className;
}

void Token::setMode(Base b)
{
    this->_base = b;
}

Base Token::getMode()
{
    return this->_base;
}

bool Token::isDecDigit(const char digit)
{
    if (!isdigit(digit) && digit != '.' && digit != '-') {
        return false;
    }
    else {
        return true;
    }
}

bool Token::isHexDigit(const char digit)
{
    if (isdigit(digit) || (toupper(digit) >= 'A' && toupper(digit) <= 'F')) {
        return true;
    }
    else {
        return false;
    }
}

bool Token::isBinDigit(const char digit)
{
    if (digit == '0' || digit == '1') {
        return true;
    }
    else {
        return false;
    }
}

bool Token::isOperand(const string & token) {
	int		i;
	bool	ret = true;
	size_t	tokenLength = token.length();

	if (token[0] == '-' && tokenLength == 1) {
		// Must be the '-' operator...
		ret = false;
	}
	else {
		for (i = 0;i < (int)tokenLength;i++) {
			if (!isDecDigit(token[i]) && !isHexDigit(token[i]) && !isBinDigit(token[i])) {
				ret = false;
				break;
			}
		}
	}

	return ret;
}
bool Token::isOperatorPlus(const string & token) {
	return token[0] == '+';
}
bool Token::isOperatorMinus(const string & token) {
	bool	ret = true;
	size_t	tokenLength = token.length();

	if (token[0] == '-') {
		if (tokenLength > 1 && isdigit(token[1])) {
			ret = false;
		}
	}
	else {
		ret = false;
	}

	return ret;
}
bool Token::isOperatorMultiply(const string & token) {
	return token[0] == '*';
}
bool Token::isOperatorDivide(const string & token) {
	return token[0] == '/';
}
bool Token::isOperatorPower(const string & token) {
	return token[0] == '^';
}
bool Token::isOperatorMod(const string & token) {
	return token[0] == '%';
}
bool Token::isOperatorAND(const string & token) {
	return token[0] == '&';
}
bool Token::isOperatorOR(const string & token) {
	return token[0] == '|';
}
bool Token::isOperatorXOR(const string & token) {
	return token[0] == '~';
}
bool Token::isOperator(const string & token) {
	return (
		isOperatorPlus(token) ||
		isOperatorMinus(token) ||
		isOperatorMultiply(token) ||
		isOperatorDivide(token) ||
		isOperatorPower(token)) ||
		isOperatorMod(token) ||
		isOperatorAND(token) ||
		isOperatorOR(token) ||
		isOperatorXOR(token);
}
bool Token::isBraceLeft(const string & token) {
	return (token[0] == '(' || token[0] == '[' || token[0] == '{');
}
bool Token::isBraceRight(const string & token) {
	return (token[0] == ')' || token[0] == ']' || token[0] == '}');
}
bool Token::isBrace(const string & token) {
	return (isBraceLeft(token) || isBraceRight(token));
}
bool Token::isBraceLeft(char chToken) {
	return (chToken == '(' || chToken == '[' || chToken == '{');
}
bool Token::isBraceRight(char chToken) {
	return (chToken == ')' || chToken == ']' || chToken == '}');
}
bool Token::isBrace(char chToken) {
	return (isBraceLeft(chToken) || isBraceRight(chToken));
}
bool Token::isConstantPi(const string & token) {
	return !token.compare(0, 2, "pi");
}
bool Token::isConstantC(const string & token) {
	return token[0] == 'c';
}
bool Token::isConstant(const string & token) {
	return (isConstantPi(token) || isConstantC(token));
}
bool Token::isFunctionSine(const string & token) {
	return !token.compare(0, 3, "sin");
}
bool Token::isFunctionCosine(const string & token) {
	return !token.compare(0, 3, "cos");
}
bool Token::isFunctionTangent(const string & token) {
	return !token.compare(0, 3, "tan");
}
bool Token::isFunctionArcSine(const string & token) {
	return !token.compare(0, 4, "asin");
}
bool Token::isFunctionArcCosine(const string & token) {
	return !token.compare(0, 4, "acos");
}
bool Token::isFunctionArcTangent(const string & token) {
	return !token.compare(0, 4, "atan");
}
bool Token::isFunctionSquareRoot(const string & token) {
	return !token.compare(0, 4, "sqrt");
}
bool Token::isFunctionLogarithm(const string & token) {
	return !token.compare(0, 3, "log");
}
bool Token::isFunctionNaturalLog(const string & token) {
	return !token.compare(0, 2, "ln");
}
bool Token::isFunctionFactorial(const string & token) {
	return !token.compare(0, 4, "fact");
}
bool Token::isFunctionMemory(const string & token) {
	return !token.compare(0, 3, "mem");
}
bool Token::isFunction(const string & token) {
	return (
		isFunctionSine(token) ||
		isFunctionCosine(token) ||
		isFunctionTangent(token) ||
		isFunctionArcSine(token) ||
		isFunctionArcCosine(token) ||
		isFunctionArcTangent(token) ||
		isFunctionSquareRoot(token) ||
		isFunctionLogarithm(token) ||
		isFunctionNaturalLog(token) ||
		isFunctionFactorial(token) ||
		isFunctionMemory(token));
}


Operator::Operator(const string & token, Base b) : Token(token, "Operator")
{
    setMode(b);
    
	if (Token::isOperatorPlus(token)) {
		op = Plus;
		precedence = 2;
		assoc = Left;
	}
	else if (Token::isOperatorMinus(token)) {
		op = Minus;
		precedence = 2;
		assoc = Left;
	}
	else if (Token::isOperatorMultiply(token)) {
        if (getMode() != Dec) {
            throw new Exception(
                        ERR_INVALID_TOKEN,
                        "Invalid token found for mode",
                        __FILE__,
                        "Operator",
                        "init()",
                        __LINE__);
        }
        
		op = Multiply;
		precedence = 3;
		assoc = Left;
	}
	else if (Token::isOperatorDivide(token)) {
        if (getMode() != Dec) {
            throw new Exception(
                        ERR_INVALID_TOKEN,
                        "Invalid token found for mode",
                        __FILE__,
                        "Operator",
                        "init()",
                        __LINE__);
        }
        
		op = Divide;
		precedence = 3;
		assoc = Left;
	}
	else if (Token::isOperatorPower(token)) {
        if (getMode() != Dec) {
            throw new Exception(
                        ERR_INVALID_TOKEN,
                        "Invalid token found for mode",
                        __FILE__,
                        "Operator",
                        "init()",
                        __LINE__);
        }
        
		op = Power;
		precedence = 4;
		assoc = Right;
	}
	else if (Token::isOperatorMod(token)) {
        if (getMode() != Dec) {
            throw new Exception(
                        ERR_INVALID_TOKEN,
                        "Invalid token found for mode",
                        __FILE__,
                        "Operator",
                        "init()",
                        __LINE__);
        }
        
		op = Mod;
		precedence = 3;
		assoc = Left;
	}
	else if (Token::isOperatorAND(token)) {
		op = And;
		precedence = 4;
		assoc = Left;
	}
	else if (Token::isOperatorOR(token)) {
		op = Or;
		precedence = 4;
		assoc = Left;
	}
	else if (Token::isOperatorXOR(token)) {
		op = Xor;
		precedence = 4;
		assoc = Left;
	}
}

Operator::Operator(const string & token, const string & className) : Token(token, className)
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

Operand * Operator::evaluate(Operand & o1, Operand & o2)
{
	Operand * result;

	switch (getOp()) {

		case Plus:
			result = new Operand(o1 + o2);
			break;

		case Minus:
			result = new Operand(o1 - o2);
			break;

		case Multiply:
			result = new Operand(o1 * o2);
			break;

		case Divide:
			result = new Operand(o1 / o2);
			break;

		case Power:
			result = new Operand(cl_float(pow(double_approx(o1.getDoubleValue()), double_approx(o2.getDoubleValue()))));
			break;

		case Mod:
			result = new Operand(o1 % o2);
			break;

		case And:
			result = new Operand(o1 & o2);
			break;

		case Or:
			result = new Operand(o1 | o2);
			break;

		case Xor:
			result = new Operand(o1 ^ o2);
			break;
	}

	return result;
}


Brace::Brace(const string & token, Base b) : Token(token, "Brace")
{
    setMode(b);
    
	if (Token::isBraceLeft(token)) {
		type = Open;
	}
	else if (Token::isBraceRight(token)) {
		type = Close;
	}
}

BraceType Brace::getType()
{
	return this->type;
}


Operand::Operand(Operand & src)
{
	_value = src.getDoubleValue();
}

Operand::Operand(const string & token, Base b) : Token(token, "Operand")
{
	int		tokenLen;
	int		i = 0;
	bool	isFloat = false;
	char	szPrecision[8];
	string 	operand;

	tokenLen = token.length();

	operand = token;

    setMode(b);
    
    if (b == Dec) {
        while (i < tokenLen) {
            if (token[i] == '.') {
                isFloat = true;
                break;
            }

            i++;
        }

        if (!isFloat) {
            operand += ".0";
        }

        sprintf(szPrecision, "_%d", FLOAT_PRECISION);
        operand += szPrecision;

        _value = operand.c_str();
    }
    else if (b == Hex) {
        _value = strtoll(operand.c_str(), NULL, 16);
    }
    else if (b == Bin) {
        _value = strtoll(operand.c_str(), NULL, 2);
    }
}

Operand::Operand(cl_F x)
{
	_value = x;
}

Operand::Operand(cl_N n)
{
	_value = n;
}

Operand::Operand(cl_I i)
{
	_value = i;
}

Operand::Operand(double d)
{
	_value = d;
}

Operand::Operand(int i)
{
	_value = i;
}

Operand::Operand(unsigned int i)
{
	_value = i;
}

Operand::Operand(long l)
{
	_value = l;
}

Operand::Operand(unsigned long l)
{
	_value = l;
}

Operand::Operand(const string & token, const string & className) : Token(token, className)
{
}

Operand & Operand::operator+(Operand & rhs)
{
	setValue(getValue() + rhs.getValue());
	return *this;
}
Operand	& Operand::operator-(Operand & rhs)
{
	setValue(getValue() - rhs.getValue());
	return *this;
}
Operand	& Operand::operator*(Operand & rhs)
{
	setValue(getValue() * rhs.getValue());
	return *this;
}
Operand	& Operand::operator/(Operand & rhs)
{
	setValue(getValue() / rhs.getValue());
	return *this;
}
Operand	& Operand::operator%(Operand & rhs)
{
	setValue(mod(getIntValue(), rhs.getIntValue()));
	return *this;
}
Operand	& Operand::operator&(Operand & rhs)
{
	setValue(getIntValue() & rhs.getIntValue());
	return *this;
}
Operand	& Operand::operator|(Operand & rhs)
{
	setValue(getIntValue() | rhs.getIntValue());
	return *this;
}
Operand	& Operand::operator^(Operand & rhs)
{
	setValue(getIntValue() ^ rhs.getIntValue());
	return *this;
}

cl_N Operand::getValue()
{
	return this->_value;
}

cl_F Operand::getDoubleValue()
{
	return cl_float(realpart(this->_value), float_format(16));
}

cl_I Operand::getIntValue()
{
	cl_I		intValue;

	intValue = floor1(realpart(this->_value));

	return intValue;
}

void Operand::setValue(cl_F x)
{
	this->_value = x;
}

void Operand::setValue(cl_N n)
{
	this->_value = n;
}

void Operand::setValue(cl_I i)
{
	_value = cl_float(i, float_format(FLOAT_PRECISION));
}


Constant::Constant(const string & token, Base b) : Operand(token, "Constant")
{
    setMode(b);
    
    if (getMode() != Dec) {
        throw new Exception(
                    ERR_INVALID_TOKEN,
                    "Invalid token found for mode",
                    __FILE__,
                    "Function",
                    "init()",
                    __LINE__);
    }
        
	if (Token::isConstantPi(token)) {
		constant = Pi;
		setValue(pi(float_format(FLOAT_PRECISION)));
	}
	else if (Token::isConstantC(token)) {
		constant = C;
		setValue(cl_float(299792458.0, float_format(FLOAT_PRECISION))); // in m/s
	}
}

Const Constant::getConstant()
{
	return this->constant;
}


Function::Function(const string & token, Base b) : Operator(token, "Function")
{
    setMode(b);
    
    if (getMode() != Dec) {
        throw new Exception(
                    ERR_INVALID_TOKEN,
                    "Invalid token found for mode",
                    __FILE__,
                    "Function",
                    "init()",
                    __LINE__);
    }
        
	if (Token::isFunctionSine(token)) {
		function = Sine;
		numArguments = 1;
	}
	else if (Token::isFunctionCosine(token)) {
		function = Cosine;
		numArguments = 1;
	}
	else if (Token::isFunctionTangent(token)) {
		function = Tangent;
		numArguments = 1;
	}
	else if (Token::isFunctionArcSine(token)) {
		function = ArcSine;
		numArguments = 1;
	}
	else if (Token::isFunctionArcCosine(token)) {
		function = ArcCosine;
		numArguments = 1;
	}
	else if (Token::isFunctionArcTangent(token)) {
		function = ArcTangent;
		numArguments = 1;
	}
	else if (Token::isFunctionSquareRoot(token)) {
		function = SquareRoot;
		numArguments = 1;
	}
	else if (Token::isFunctionLogarithm(token)) {
		function = Logarithm;
		numArguments = 1;
	}
	else if (Token::isFunctionNaturalLog(token)) {
		function = NaturalLog;
		numArguments = 1;
	}
	else if (Token::isFunctionFactorial(token)) {
		function = Factorial;
		numArguments = 1;
	}
	else if (Token::isFunctionMemory(token)) {
		function = Memory;
		numArguments = 1;
	}

	setPrecedence(5);
}

Operand * Function::evaluate(Operand & arg1)
{
	Operand *		result;
	cl_F			degreesToRadians = (pi(float_format(FLOAT_PRECISION)) / cl_float(180, float_format(FLOAT_PRECISION)));
	cl_F			radiansToDegrees = (cl_float(180, float_format(FLOAT_PRECISION)) / pi(float_format(FLOAT_PRECISION)));

	switch (this->function) {

		case Sine:
			result = new Operand(sin(arg1.getDoubleValue() * degreesToRadians));
			break;

		case Cosine:
			result = new Operand(cos(arg1.getDoubleValue() * degreesToRadians));
			break;

		case Tangent:
			result = new Operand(tan(arg1.getDoubleValue() * degreesToRadians));
			break;

		case ArcSine:
			result = new Operand(asin(arg1.getDoubleValue()) * radiansToDegrees);
			break;

		case ArcCosine:
			result = new Operand(acos(arg1.getDoubleValue()) * radiansToDegrees);
			break;

		case ArcTangent:
			result = new Operand(atan(arg1.getDoubleValue()) * radiansToDegrees);
			break;

		case SquareRoot:
			result = new Operand(sqrt(arg1.getDoubleValue()));
			break;

		case Logarithm:
			result = new Operand(log(arg1.getDoubleValue()));
			break;

		case NaturalLog:
			result = new Operand(ln(arg1.getDoubleValue()));
			break;

		case Factorial:
			result = new Operand(_factorial(arg1.getIntValue()));
			break;

		case Memory:
			result = new Operand(_memory[cl_I_to_int(arg1.getIntValue())]);
			break;

		default:
			break;
	}

	return result;
}

cl_I Function::_factorial(cl_I arg)
{
	cl_I			index;
	cl_I			result;

	result = arg;

	if (arg > 1) {
		for (index = arg - 1;index > 0;index--) {
			result *= index;
		}
	}

	return result;
}

void Function::memoryStore(int memoryNum, cl_N value)
{
	_memory[memoryNum] = value;
}


Token * TokenFactory::createToken(const string & token, Base b)
{
	Token * t;

	if (Token::isOperand(token)) {
		t = new Operand(token, b);
	}
	else if (Token::isOperator(token)) {
		t = new Operator(token, b);
	}
	else if (Token::isBrace(token)) {
		t = new Brace(token, b);
	}
	else if (Token::isConstant(token)) {
		t = new Constant(token, b);
	}
	else if (Token::isFunction(token)) {
		t = new Function(token, b);
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

    t->setMode(b);
    
	return t;
}


CalcTokenizer::CalcTokenizer(const string & expression, Base b)
{
	this->_expression = expression;
	startIndex = 0;
	endIndex = 0;
	expressionLen = expression.length();
    this->_base = b;
}

bool CalcTokenizer::_isToken(char ch)
{
	return (tokens.find(ch) != string::npos);
}

bool CalcTokenizer::_isWhiteSpace(char ch)
{
	return (whiteSpace.find(ch) != string::npos);
}

int CalcTokenizer::_findNextTokenPos()
{
	int		i;
	char	ch;
	bool	lookingForWhiteSpace = true;
	int		tokenLen = 0;

	for (i = startIndex;i < (int)expressionLen;i++) {
		ch = _expression[i];

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
				if (ch == '-' && isdigit(_expression[i + 1])) {
					bool isNegativeOperand = false;

					if (i > 1) {
						bool isPreviousCharBrace = Token::isBraceRight(_expression[i - 1]);
						bool isPreviousCharDigit = isdigit(_expression[i - 1]) != 0 ? true : false;

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
	string		token;
	int			tokenLen;

	tokenLen = endIndex - startIndex;

	token = _expression.substr(startIndex, tokenLen);

	startIndex = endIndex;

	return TokenFactory::createToken(token, this->_base);
}
