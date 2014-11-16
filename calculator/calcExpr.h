#ifndef _CALCEXPR_H_
#define _CALCEXPR_H_
#include <string>
#include <vector>
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
private:
	void check(const std::string& str);
	int assistCheck(const std::string& str);
	std::string preprocess(const std::string& str);
	std::vector<std::string> getSmartInfix(const std::string& str);
	bool IsDigit(const std::string& str) const;
	void setPriority();
	void handleOperator(std::stack<std::shared_ptr<Node>>& calcNode, char op);
	std::vector<std::string> infix,postfix;
	std::map<char, int> priorityTable;
};

inline
bool CalcExpr::IsDigit(const std::string& str) const
{
	const std::string numbers("0123456789.");
	auto pos = str.find_first_not_of(numbers);
	return pos == std::string::npos;
}



#endif