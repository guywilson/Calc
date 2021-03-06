/******************************************************************************
SHUNTING YARD ALGORITHM
-----------------------

While there are tokens to be read:
	Read a token.
	If the token is a number, then push it to the output queue.
	If the token is a function token, then push it onto the stack.
	If the token is a function argument separator (e.g., a comma):
		Until the token at the top of the stack is a left parenthesis, pop
		operators off the stack onto the output queue. If no left parentheses
		are encountered, either the separator was misplaced or parentheses were
		mismatched.
	If the token is an operator, o1, then:
		while there is an operator token o2, at the top of the operator stack
		and either
		o1 is left-associative and its precedence is less than or equal to that
		of o2, or
		o1 is right associative, and has precedence less than that of o2,
		pop o2 off the operator stack, onto the output queue;
		at the end of iteration push o1 onto the operator stack.
	If the token is a left parenthesis (i.e. "("), then push it onto the stack.
	If the token is a right parenthesis (i.e. ")"):
		Until the token at the top of the stack is a left parenthesis, pop
		operators off the stack onto the output queue.
		Pop the left parenthesis from the stack, but not onto the output queue.
		If the token at the top of the stack is a function token, pop it onto
		the output queue.
		If the stack runs out without finding a left parenthesis, then there
		are mismatched parentheses.
		When there are no more tokens to read:
		While there are still operator tokens in the stack:
			If the operator token on the top of the stack is a parenthesis,
			then there are mismatched parentheses.
			Pop the operator onto the output queue.
Exit.

******************************************************************************/

#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>

#include "calc.h"
#include "token.h"
#include "stack.h"
#include "types.h"
#include "exception.h"
#include "debug.h"

using namespace std;

Calculator::Calculator()
{
    this->_base = Dec;
}

void Calculator::_convertToRPN(const string & expression, Queue * outputQueue)
{
	Stack * operatorStack = new Stack();

	CalcTokenizer tok(expression, this->_base);

	while (tok.hasMoreTokens()) {
		Token * t = tok.nextToken();

		/*
		** If the token is a number, then push it to the output queue.
		*/
		if (t->isOperand()) {
			outputQueue->addItem(t);
		}
		/*
		** If the token is a function token, then push it onto the stack.
		*/
		else if (t->isFunction()) {
			operatorStack->push(t);
		}
		/*
		** If the token is an operator, o1, then:
		**	while there is an operator token o2, at the top of the operator stack
		**	and either
		**	o1 is left-associative and its precedence is less than or equal to that
		**	of o2, or
		**	o1 is right associative, and has precedence less than that of o2,
		**	pop o2 off the operator stack, onto the output queue;
		**	at the end of iteration push o1 onto the operator stack.
		*/
		else if (t->isOperator()) {
			Operator * o1 = (Operator *)t;

			while (operatorStack->getItemCount() > 0) {
				int topOfStack = (int)(operatorStack->getItemCount() - 1);

				Token * topToken = (Token *)operatorStack->peek(topOfStack);

				if (!topToken->isOperator()) {
					break;
				}

				Operator * o2 = (Operator *)topToken;

				if ((o1->getAssociativity() == Left && o1->getPrecedence() <= o2->getPrecedence()) ||
					(o1->getAssociativity() == Right && o1->getPrecedence() < o2->getPrecedence()))
				{
					o2 = (Operator *)operatorStack->pop();
					outputQueue->addItem(o2);
				}
				else {
					break;
				}
			}

			operatorStack->push(o1);
		}
		else if (t->isBrace()) {
			Brace * br = (Brace *)t;

			/*
			** If the token is a left parenthesis (i.e. "("), then push it onto the stack.
			*/
			if (br->getType() == Open) {
				operatorStack->push(br);
			}
			else {
				/*
				If the token is a right parenthesis (i.e. ")"):
					Until the token at the top of the stack is a left parenthesis, pop
					operators off the stack onto the output queue.
					Pop the left parenthesis from the stack, but not onto the output queue.
					If the token at the top of the stack is a function token, pop it onto
					the output queue.
					If the stack runs out without finding a left parenthesis, then there
					are mismatched parentheses.
				*/
				bool foundLeftParenthesis = false;

				while (operatorStack->getItemCount() > 0) {
					Token * stackToken = (Token *)operatorStack->pop();

					if (stackToken->isBrace()) {
						Brace * br = (Brace *)stackToken;

						if (br->getType() == Open) {
							foundLeftParenthesis = true;
							break;
						}
					}
					else {
						outputQueue->addItem(stackToken);
					}
				}

				if (!foundLeftParenthesis) {
					/*
					** If we've got here, we must have unmatched parenthesis...
					*/
					throw new Exception(
								ERR_UNMATCHED_PARENTHESIS,
								"Failed to find left parenthesis on operator stack",
								__FILE__,
								"Calculator",
								"convertToRPN()",
								__LINE__);
				}
			}
		}
	}

	/*
	While there are still operator tokens in the stack:
		If the operator token on the top of the stack is a parenthesis,
		then there are mismatched parentheses.
		Pop the operator onto the output queue.
	*/
	while (operatorStack->getItemCount() > 0) {
		Token * stackToken = (Token *)operatorStack->pop();

		if (stackToken->isBrace()) {
			/*
			** If we've got here, we must have unmatched parenthesis...
			*/
			throw new Exception(
						ERR_UNMATCHED_PARENTHESIS,
						"Found too many parenthesis on operator stack",
						__FILE__,
						"Calculator",
						"convertToRPN()",
						__LINE__);
		}
		else {
			outputQueue->addItem(stackToken);
		}
	}

	delete operatorStack;
}

Base Calculator::getMode()
{
    return this->_base;
}

void Calculator::setMode(Base b)
{
    this->_base = b;
}

string Calculator::getModeStr()
{
    string      mode;
    
    switch (_base) {
        case Dec:
            mode = "DEC";
            break;
            
        case Hex:
            mode = "HEX";
            break;
            
        case Bin:
            mode = "BIN";
            break;
            
        case Oct:
            mode = "OCT";
            break;
    }
    
    return mode;
}

cl_N Calculator::evaluate(const string & expression, string & resultBuffer)
{
	cl_N 						result;
	istreambuf_iterator<char>	eos;

	Queue * outputQueue = new Queue();

	DebugHelper * dbg = DebugHelper::getInstance();

	/*
	** Convert the calculation in infix notation to the postfix notation
	** (Reverse Polish Notation) using the 'shunting yard algorithm'...
	*/
	_convertToRPN(expression, outputQueue);

	Stack * stack = new Stack();

	while (outputQueue->getItemCount() > 0) {
		Token * t = (Token *)outputQueue->getItem();

		if (dbg->getDebugState()) {
			cout << "RPN: Got Token '" << t->getToken() << "'" << endl;
		}

		if (t->isOperand()) {
			stack->push(t);
		}
		/*
		** Must be Operator or Function...
		*/
		else {
			if (t->isOperator()) {
				if (t->isFunction()) {
					Function * f = (Function *)t;

					if ((int)stack->getItemCount() < f->getNumArguments()) {
						throw new Exception(
									ERR_INVALID_NUM_ARGUMENTS,
									"Too few arguments for function",
									__FILE__,
									"Calculator",
									"evaluate()",
									__LINE__);
					}

					Operand * o1 = (Operand *)stack->pop();

					Operand * result = f->evaluate(*o1);

					stack->push(result);

					delete o1;
				}
				else {
					if (stack->getItemCount() < 2) {
						throw new Exception(
									ERR_INVALID_NUM_ARGUMENTS,
									"Too few arguments for operator",
									__FILE__,
									"Calculator",
									"evaluate()",
									__LINE__);
					}

					Operand * o2 = (Operand *)stack->pop();
					Operand * o1 = (Operand *)stack->pop();

					Operator * op = (Operator *)t;

					Operand * result = op->evaluate(*o1, *o2);

					stack->push(result);

					delete o1;
					delete o2;
				}
			}
		}
	}

	/*
	** If there is one and only one item left on the stack,
	** it is the result of the calculation. Otherwise, we
	** have too many tokens and therefore an error...
	*/
	if (stack->getItemCount() == 1) {
		Operand * o = (Operand *)stack->pop();

        cl_F f = o->getDoubleValue();
        cl_I i = o->getIntValue();

        if (dbg->getDebugState()) {
			cout << "RPN: Got Result - DoubleValue [" << f << "], IntValue [" << i << "]"<< endl;
		}

        o->toString(this->getMode(), resultBuffer);
        
        switch (this->getMode()) {
            case Dec:
                result = f;
                break;
                
            case Hex:
                result = i;
                break;
                
            case Bin:
                result = i;
                break;
                
            case Oct:
                result = i;
                break;
        }
        
		delete o;
		delete stack;
	}
	else {
		delete stack;

		throw new Exception(
					ERR_RPN_PARSE,
					"Too many arguments left on stack",
					__FILE__,
					"Calculator",
					"evaluate()",
					__LINE__);
	}

	return result;
}

string & Calculator::evaluate(const string & expression)
{
	string * pResult = new string();

	Calculator::evaluate(expression, *pResult);

	return *pResult;
}

void Calculator::store(int memoryNum, cl_N result)
{
	Function::memoryStore(memoryNum, result);
}

cl_N Calculator::recall(int memoryNum)
{
	return Function::memoryRecall(memoryNum);
}
