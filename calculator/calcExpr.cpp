#include "calcExpr.h"
#include <algorithm>
#include <sstream>

void CalcExpr::setPriority()
{
	priorityTable.insert(std::make_pair('*', 2));
	priorityTable.insert(std::make_pair('/', 2));
	priorityTable.insert(std::make_pair('+', 1));
	priorityTable.insert(std::make_pair('-', 1));
}

std::istream& CalcExpr::getExpr(std::istream& is)
{
	std::getline(is, infixExpr);
	//need to do valid infix expression check !
	return is;
}

void CalcExpr::changeInfixToPostfix()
{
	std::stack<char> operStack;
	char leftP('('), rightP(')');
	std::for_each(infixExpr.begin(), infixExpr.end(), [&,this](char c)
	{
		if (isdigit(c))
			postfixExpr.push_back(c);
		else if (c == leftP)
			operStack.push(c);
		else if (c == rightP)
		{
			while (operStack.top() != leftP)
			{
				postfixExpr.push_back(operStack.top());
				operStack.pop();
			}
			operStack.pop();
		}
		else
		{
			while (!operStack.empty())
			{
				if (operStack.top() == leftP)
					break;
				else if (priorityTable[c] > priorityTable[operStack.top()])
				{
					break;
				}
				else
				{
					postfixExpr.push_back(operStack.top());
					operStack.pop();
				}
			}
			operStack.push(c);
		}
	});
	while (!operStack.empty())
	{
		postfixExpr.push_back(operStack.top());
		operStack.pop();
	}
}

double CalcExpr::calcResult()
{
	std::stack<std::shared_ptr<Node>> calcNode;
	std::stringstream ss;
	for (auto c : postfixExpr)
	{
		if (isdigit(c))
		{
			double val;
			ss << c;
			ss >> val;
			std::shared_ptr<Node> numNode = std::make_shared<NumNode>(NumNode(val));
			calcNode.push(numNode);
			ss.clear();
		}
		else
		{
			handleOperator(calcNode, c);
		}
	}
	return calcNode.top()->calculate();
}

void CalcExpr::handleOperator(std::stack<std::shared_ptr<Node>>& calcNode, char op)
{
	std::shared_ptr<Node> rhs = calcNode.top();
	calcNode.pop();
	std::shared_ptr<Node> lhs = calcNode.top();
	calcNode.pop();
	switch (op)
	{
	case '+':
	{
		calcNode.push(lhs + rhs);
		break;
	};
	case '-':
	{
		calcNode.push(lhs - rhs);
		break;
	}
	case '*':
	{
		calcNode.push(lhs * rhs);
		break;
	}
	case '/':
	{
		calcNode.push(lhs / rhs);
		break;
	}
	default:
		break;
	}
}