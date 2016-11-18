#include "types.h"

#ifndef _INCL_TOKEN
#define _INCL_TOKEN

#define TOKEN_LENGTH		64
#define CLASSNAME_LENGTH	16

class Token
{
	private:
		char			_szToken[TOKEN_LENGTH];
		char			_szClassName[CLASSNAME_LENGTH];
	
	protected:
		Token(char *pszToken, const char *pszClassName);

		void			setClass(const char *pszClassName);
		
	public:
		Token() {}
		Token(char *pszToken);
		
		char *			getToken();
		char *			getClass();

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
		
		static bool		isOperand(char * pszToken);
		static bool		isOperatorPlus(char * pszToken);
		static bool		isOperatorMinus(char * pszToken);
		static bool		isOperatorMultiply(char * pszToken);
		static bool		isOperatorDivide(char * pszToken);
		static bool		isOperatorPower(char * pszToken);
		static bool		isOperator(char * pszToken);
		static bool		isBraceLeft(char * pszToken);
		static bool		isBraceRight(char * pszToken);
		static bool		isBrace(char * pszToken);
		static bool		isConstantPi(char * pszToken);
		static bool		isConstantC(char * pszToken);
		static bool		isConstant(char * pszToken);
		static bool		isFunctionSine(char * pszToken);
		static bool		isFunctionCosine(char * pszToken);
		static bool		isFunctionTangent(char * pszToken);
		static bool		isFunctionArcSine(char * pszToken);
		static bool		isFunctionArcCosine(char * pszToken);
		static bool		isFunctionArcTangent(char * pszToken);
		static bool		isFunctionSquareRoot(char * pszToken);
		static bool		isFunctionLogarithm(char * pszToken);
		static bool		isFunction(char * pszToken);
};

class Operand : public Token
{
	protected:
		double			value;
	
	public:
		Operand(char *pszToken);
		Operand(double x);
		Operand(char * pszToken, const char * pszClassName);
		
		double			getValue();
		
		virtual bool	isOperand() {
							return true;
						}
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
		Operator(char *pszToken);
		Operator(char *pszToken, const char *pszClassName);
		
		int				getPrecedence();
		Associativity	getAssociativity();
		Op				getOp();
		
		Operand *		evaluate(Operand * o1, Operand * o2);
						
		virtual bool	isOperator() {
							return true;
						}
};

class Brace : public Token
{
	private:
		BraceType		type;
	
	public:
		Brace(char *pszToken);
		
		BraceType		getType();
		
		virtual bool	isBrace() {
							return true;
						}
};

class Constant : public Operand
{
	private:
		Const			constant;
		
		double			_pi();
		
	public:
		Constant(char *pszToken);
		
		Const			getConstant();
		
		virtual bool	isConstant() {
							return true;
						}
};

class Function : public Operator
{
	private:
		Func			function;
		int				numArguments;
		
	public:
		Function(char *pszToken);
		
		Operand *		evaluate(Operand * arg1);
		
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
		static Token * createToken(char *pszToken);
};


class CalcTokenizer
{
	private:
		int				startIndex;
		int				endIndex;
		size_t			expressionLen;
		size_t			maxLen;
		char *			pszExpression;
		const char *	szWhiteSpace = " \t\n\r";
		const char *	szTokens = " \t\n\r+-*/^()[]{}";
		
		bool			_isToken(char ch);
		bool			_isWhiteSpace(char ch);
		int				_findNextTokenPos();
		
	public:
		CalcTokenizer(char *pszExpression, size_t bufferLength);
		
		bool			hasMoreTokens();
		Token *			nextToken();
};

#endif
