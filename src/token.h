#include <string>
#include <cln/cln.h>

#include "types.h"

#ifndef _INCL_TOKEN
#define _INCL_TOKEN

using namespace std;
using namespace cln;

class Token
{
	private:
		string			_token;
		string			_className;
        Base            _base;
        
        static bool     isDecDigit(const char digit);
        static bool     isHexDigit(const char digit);
        static bool     isBinDigit(const char digit);
        static bool     isOctDigit(const char digit);

	protected:
		Token(const string & token, const string & className);

		void			setClass(const string & className);

	public:
		Token() {}
		Token(const string & token);

		virtual			~Token() {}

		string	&		getToken();
		string	&		getClass();

        void            setMode(Base b);
        Base            getMode();
        
		virtual bool	isOperand() {
							return false;
						}
		virtual bool	isOperator() {
							return false;
						}
		virtual bool	isBrace() {
							return false;
						}
		virtual bool	isConstant() {
							return false;
						}
		virtual bool	isFunction() {
							return false;
						}

		static bool		isOperand(const string & token, const Base b);
		static bool		isOperatorPlus(const string & token);
		static bool		isOperatorMinus(const string & token);
		static bool		isOperatorMultiply(const string & token);
		static bool		isOperatorDivide(const string & token);
		static bool		isOperatorPower(const string & token);
		static bool		isOperatorMod(const string & token);
		static bool		isOperatorAND(const string & token);
		static bool		isOperatorOR(const string & token);
		static bool		isOperatorXOR(const string & token);
		static bool		isOperator(const string & token);
		static bool		isBraceLeft(const string & token);
		static bool		isBraceRight(const string & token);
		static bool		isBrace(const string & token);
		static bool		isBraceLeft(char chToken);
		static bool		isBraceRight(char chtoken);
		static bool		isBrace(char chtoken);
		static bool		isConstantPi(const string & token);
		static bool		isConstantC(const string & token);
		static bool		isConstant(const string & token);
		static bool		isFunctionSine(const string & token);
		static bool		isFunctionCosine(const string & token);
		static bool		isFunctionTangent(const string & token);
		static bool		isFunctionArcSine(const string & token);
		static bool		isFunctionArcCosine(const string & token);
		static bool		isFunctionArcTangent(const string & token);
		static bool		isFunctionSquareRoot(const string & token);
		static bool		isFunctionLogarithm(const string & token);
		static bool		isFunctionNaturalLog(const string & token);
		static bool		isFunctionFactorial(const string & token);
		static bool		isFunctionMemory(const string & token);
		static bool		isFunction(const string & token);
};

class Operand : public Token
{
	private:
		cl_N			_value;
        
	protected:
		void 			setValue(cl_F x);
		void 			setValue(cl_I i);
		void 			setValue(cl_N n);

	public:
		Operand(Operand & src);
		Operand(const string & token, Base b);
		Operand(cl_F x);
		Operand(cl_I i);
		Operand(cl_N n);
        Operand(double d);
        Operand(int i);
        Operand(unsigned int i);
        Operand(long l);
        Operand(unsigned long l);
		Operand(const string & token, const string & className);

		virtual 		~Operand() {}

		Operand &		operator+(Operand & rhs);
		Operand	&		operator-(Operand & rhs);
		Operand	&		operator*(Operand & rhs);
		Operand	&		operator/(Operand & rhs);
		Operand	&		operator%(Operand & rhs);

		Operand	&		operator&(Operand & rhs);
		Operand	&		operator|(Operand & rhs);
		Operand	&		operator^(Operand & rhs);

        cl_N            getValue();
		cl_F			getDoubleValue();
        static cl_F     getDoubleValue(cl_N value);
		cl_I			getIntValue();
		static cl_I		getIntValue(cl_N value);

		virtual bool	isOperand() {
							return true;
						}

        void            toString(Base b, string & s);
        static void     toString(cl_N value, Base b, string & s);
};

class Operator : public Token
{
	private:
		int				precedence;
		Associativity	assoc;
		Op				op;

	protected:
		void			setPrecedence(int precedence);

	public:
		Operator(const string & token, Base b);
		Operator(const string & token, const string & className);

		virtual			~Operator() {}

		int				getPrecedence();
		Associativity	getAssociativity();
		Op				getOp();

		Operand *		evaluate(Operand & o1, Operand & o2);

		virtual bool	isOperator() {
							return true;
						}
};

class Brace : public Token
{
	private:
		BraceType		type;

	public:
		Brace(const string & token, Base b);

		BraceType		getType();

		virtual bool	isBrace() {
							return true;
						}
};

class Constant : public Operand
{
	private:
		Const			constant;
        string          strValue;

		cl_F			_pi();

	public:
		Constant(const string & token, Base b);

		Const			getConstant();

		virtual bool	isConstant() {
							return true;
						}
                        
        string &        constToStrValue(const string & constant);
};

class Function : public Operator
{
	private:
		Func			function;
		int				numArguments;
		cl_I			_factorial(cl_I arg);

	public:
		Function(const string & token, Base b);

		Operand *		evaluate(Operand & arg1);

		static void		memoryStore(int memoryNum, cl_N value);
        static cl_N     memoryRecall(int memoryNum);

		int				getNumArguments() {
							return numArguments;
						}

		virtual bool	isFunction() {
							return true;
						}
};


class TokenFactory
{
	public:
		static Token * createToken(const string & token, Base b);
};


class CalcTokenizer
{
	private:
		int				startIndex;
		int				endIndex;
		size_t			expressionLen;
		string			_expression;
		const string	whiteSpace = " \t\n\r";
		const string	tokens = " \t\n\r+-*/^%&|~()[]{}";

		bool			_isToken(char ch);
		bool			_isWhiteSpace(char ch);
		int				_findNextTokenPos();
        
        Base            _base;

	public:
		CalcTokenizer(const string & expression, Base b);

		bool			hasMoreTokens();
		Token *			nextToken();
};

#endif
