#include "extractSth.h"


//a line only contain a filename.
ifstream& extractSth::getFilename(ifstream& in)
{
	string fname;
	while (in >> fname)
	{
		filename.push_back(std::move(fname));
	}
	return in;
}

void extractSth::getTarget()
{
	if (filename.empty())
		return;
	ifstream in;
	string line;
	for (const auto& s : filename)
	{
		in.open(s.c_str());
		size_t ii = 1;
		while (std::getline(in,line))
		{
			if (ii == 134)
			{
				int kk = 1;
			}
			for (string::size_type ix = 0; ix < line.size(); ++ix)
			{
				if (line[ix] == '\"')
					stateGraph(line, ix);
			}
			++ii;
		}
		in.close();
		in.clear();
	}
}

void extractSth::writeResults()
{
	ofstream os;
	os.open("reults.txt");
	for (const auto& s : results)
	{
		os << s << " ";
	}
	os.close();
}
void extractSth::stateGraph(const string& str, string::size_type& ix)
{
	int state = 0;
	string ret("Gte");
	bool endFlag = false;
	for (string::size_type ie = ix; ie != str.size(); ++ie)
	{
		switch (state)
		{
		case 0:
		{
			if (str[ie] == '\"')
			{
				state = 1;
			}
			break;
		}
		case 1:
		{
			char c = str[ie];
			if (isalpha(str[ie]))
			{
				state = 2;
				ret.push_back(str[ie]);
			}
			else
				return;
			break;
		}
		case 2:
		{
			if (isalpha(str[ie]) || isdigit(str[ie]))
			{
				ret.push_back(str[ie]);
			}
			else if (str[ie] == '.')
			{
				ret.push_back(str[ie]);
				state = 3;
			}
			else
				return;
			break;
		}
		case 3:
		{
			if (str[ie] == 'h')
			{
				ret.push_back(str[ie]);
				state = 4;
			}
			else if (str[ie] == 'i')
			{
				ret.push_back(str[ie]);
				state = 5;
			}
			else if (str[ie] == 'c')
			{
				ret.push_back(str[ie]);
				state = 8;
			}
			else
				return;
			break;
		}
		case 4:
		{
			if (str[ie] == '\"')
				endFlag = true;
			else
				return;
			break;
		}
		case 5:
		{
			if (str[ie] == 'n')
			{
				ret.push_back(str[ie]);
				state = 6;
			}
			else
				return;
			break;
		}
		case 6:
		{
			if (str[ie] == 'l')
			{
				ret.push_back(str[ie]);
				state = 7;
			}
			else
				return;
			break;
		}
		case 7:
		{
			if (str[ie] == '\"')
			{
				endFlag = true;
			}
			else
				return;
			break;
		}
		case 8:
		{
			if (str[ie] == 'p')
			{
				ret.push_back(str[ie]);
				state = 9;
			}
			else
				return;
			break;
		}
		case 9:
		{
			if (str[ie] == 'p')
			{
				ret.push_back(str[ie]);
				state = 10;
			}
			else
				return;
			break;
		}
		case 10:
		{
			if (str[ie] == '\"')
			{
				endFlag = true;
			}
			else
				return;
			break;
		}
		}
		if (endFlag)
		{
			results.push_back(std::move(ret));
			ix = ie;
			break;
		}
	}
}