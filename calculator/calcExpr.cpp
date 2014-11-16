#include "calcExpr.h"
#include <algorithm>
#include <sstream>

class emptyInput :public std::runtime_error
{
public:
	emptyInput(const std::string& msg) :std::runtime_error(msg){}
};

class invalidParentheses :public std::runtime_error
{
public:
	invalidParentheses(const std::string& msg) :std::runtime_error(msg){}
};

class invalidSymbol :public std::runtime_error
{
public:
	invalidSymbol(const std::string& msg) :std::runtime_error(msg){}
};

void CalcExpr::setPriority()
{
	priorityTable.insert(std::make_pair('*', 2));
	priorityTable.insert(std::make_pair('/', 2));
	priorityTable.insert(std::make_pair('+', 1));
	priorityTable.insert(std::make_pair('-', 1));
}

std::istream& CalcExpr::getExpr(std::istream& is)
{
	std::string infixExpr;
	while (std::getline(is,infixExpr))
	{
		try
		{
			check(infixExpr);
			break;
		}
		catch (const emptyInput& msg)
		{
			std::cout << msg.what() << std::endl;
		}
		catch (const invalidParentheses& msg)
		{
			std::cout << msg.what() << std::endl;
		}
		catch (const invalidSymbol& msg)
		{
			std::cout << msg.what() << std::endl;
		}
	}
	infixExpr = preprocess(infixExpr);
	infix = getSmartInfix(infixExpr);
	return is;
}

//check the input expression is valid
void CalcExpr::check(const std::string& str)
{
	//str cannot be empty
	//parentheses should be valid ,such as (()()(()))
	//situation "3++2 , 3+*2 " is invalid
	switch (assistCheck(str))
	{
	case 0:
		throw emptyInput("empty input is invalid!");
		break;
	case 1:
		throw invalidParentheses("invalid parentheses!");
		break;
	case 2:
		throw invalidSymbol("invalid symbol!");
		break;
	default:
		break;
	} 
}

//return 0 : empty input
//return 1 : invalid parentheses,only '(' and ')' , it's easy.
//return 2 : invalid symbol exists
//return 3 : valid!
int CalcExpr::assistCheck(const std::string& str)
{
	const int EMPTYINPUT(0), INVALIDP(1), INVALIDSYMBOL(2), VALID(3);
	if (str.empty())
		return EMPTYINPUT;
	std::stack<char> leftP;
	for (auto c : str)
	{
		if (c == '(')
			leftP.push(c);
		else if (c == ')')
		{
			if (leftP.empty())
				return INVALIDP;
			else
				leftP.pop();
		}
		else if (isdigit(c) || isspace(c) || c == '.')
			continue;
		else if (priorityTable.find(c) == priorityTable.end())
		{
			return INVALIDSYMBOL;
		}
	}
	if (leftP.empty())
		return VALID;
	else
		return INVALIDP;
}

//str is certainly not empty 
//handle the situation such as '-3+2 or 3+(-2)' 
//and remove trivial space character ' '
std::string CalcExpr::preprocess(const std::string& str)
{
	std::string ret;
	char plus('+'), minus('-'), leftP('('), zero('0');
	if (str[0] == plus || str[0] == minus)
		ret.push_back(zero);
	for (auto iter = str.begin(); iter != str.end(); ++iter)
	{
		if (isspace(*iter))
			continue;
		if (*iter == plus || *iter == minus)
		{
			if (ret.back() == leftP)
				ret.push_back(zero);
		}
		ret.push_back(*iter);
	}
	return ret;
}

//process float digit such as '6.5' '100.2' 
std::vector<std::string> CalcExpr::getSmartInfix(const std::string& str)
{
	std::vector<std::string> ret;
	std::string number("0123456789.");
	size_t interval = 1;
	for (size_t pos = 0; pos < str.size(); pos += interval)
	{
		if (isdigit(str[pos]))
		{
			auto end_pos = str.find_first_not_of(number, pos);
			if (end_pos != std::string::npos)
			{
				interval = end_pos - pos;
				ret.push_back(str.substr(pos, interval));
			}
			else
			{
				ret.push_back(str.substr(pos));
				break;
			}
		}
		else
		{
			ret.push_back(str.substr(pos,1));
			interval = 1;
		}
	}
	return std::move(ret);
}

void CalcExpr::changeInfixToPostfix()
{
	std::stack<char> operStack;
	char leftP('('), rightP(')');
	std::for_each(infix.begin(), infix.end(), [&,this](const std::string& str)
	{
		if (IsDigit(str))
			postfix.push_back(str);
		else
		{
			char c = str[0];
			if (c == leftP)
				operStack.push(c);
			else if (c == rightP)
			{
				while (operStack.top() != leftP)
				{
					std::string temp;
					temp += operStack.top();
					postfix.push_back(temp);
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
						std::string temp;
						temp += operStack.top();
						postfix.push_back(temp);
						operStack.pop();
					}
				}
				operStack.push(c);
			}
		}
	});
	while (!operStack.empty())
	{
		std::string temp;
		temp += operStack.top();
		postfix.push_back(temp);
		operStack.pop();
	}
} 

double CalcExpr::calcResult()
{
	std::stack<std::shared_ptr<Node>> calcNode;
	for (const auto &str : postfix)
	{
		if (IsDigit(str))
		{
			std::shared_ptr<Node> numNode = std::make_shared<NumNode>(NumNode(std::stod(str)));
			calcNode.push(numNode);
		}
		else
		{
			char c(str[0]);
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