#include "LexAnalysis.h"

void LexAnalysis::runLex()
{
	for (string::size_type ix = 0; ix < input.size();)
	{
		if (opTable.count(input[ix]))
		{
			elements.push_back(std::make_shared<OpElem>(OpElem(input[ix])));
			++ix;
		}
		else if (isdigit(input[ix]))
		{
			ix = stateGraph(ix, input);
		}
		else
			throw invalidInput("invalid input!");
	}
}

void LexAnalysis::initializeOpTable()
{
	vector<char> oper{ '+', '-', '*', '/', '(', ')' };
	for (auto c : oper)
	{
		opTable.insert(c);
	}
}

string::size_type 
LexAnalysis::stateGraph(string::size_type ix, const string& str)
{
	state = 13;
	string number;
	string::size_type ret = str.size();
	bool endFlag = false;
	for (string::size_type ie = ix; ie != str.size(); ++ie)
	{
		switch (state)
		{
		case 13:
		{
			if (isdigit(str[ie]))
			{
				number.push_back(str[ie]);
			}
			else if (str[ie] == '.')
			{
				number.push_back(str[ie]);
				state = 14;
			}
			else if (str[ie] == 'e')
			{
				number.push_back(str[ie]);
				state = 16;
			}
			else
			{
				endFlag = true;
			}
			break;
		}
		case 14:
		{
			if (isdigit(str[ie]))
			{
				number.push_back(str[ie]);
				state = 15;
			}
			else
				throw invalidInput("invalid input for a number after \'.\' ");
			break;
		}
		case 15:
		{
			if (isdigit(str[ie]))
				number.push_back(str[ie]);
			else if (str[ie] == 'e')
			{
				number.push_back(str[ie]);
				state = 16;
			}
			else
			{
				endFlag = true;
			}
			break;
		}
		case 16:
		{
			if (isdigit(str[ie]))
			{
				number.push_back(str[ie]);
				state = 18;
			}
			else if (str[ie] == '+' || str[ie] == '-')
			{
				number.push_back(str[ie]);
				state = 17;
			}
			else
				throw invalidInput("invalid input for a number after \'+\' or \'-\' ");
			break;
		}
		case 17:
		{
			if (isdigit(str[ie]))
			{
				number.push_back(str[ie]);
				state = 18;
			}
			else
				throw invalidInput("invalid input for a number");
			break;
		}
		case 18:
		{
			if (isdigit(str[ie]))
				number.push_back(str[ie]);
			else
				endFlag = true;
			break;
		}
		}
		if (endFlag)
		{
			ret = ie;
			break;
		}
	}
	state = 0;
	elements.push_back(std::make_shared<NumElem>(NumElem(std::stod(number))));
	return ret;
}