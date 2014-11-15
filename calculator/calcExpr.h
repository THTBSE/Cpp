#ifndef _CALCEXPR_H_
#define _CALCEXPR_H_
#include <string>
#include <map>
#include <stack>
#include <iostream>
#include <memory>
#include "calculator.h"

//changing infix expression to postfix expression , and using calculator's Node->calculate()
//to get the result.

class CalcExpr
{
public:
	CalcExpr() { setPriority(); }
	std::istream& getExpr(std::istream& is = std::cin);
	void changeInfixToPostfix();
	double calcResult();


	void setPriority();
	void handleOperator(std::stack<std::shared_ptr<Node>>& calcNode, char op);
	std::string infixExpr, postfixExpr;
	std::map<char, int> priorityTable;
};




#endif