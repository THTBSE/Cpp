#include "basicString.h"
#include <iostream>
#include <algorithm>

void basicString::replaceWith(string& s, const string& oldVal, const string& newVal)
{
	auto pos = s.find(oldVal);
	while (pos != string::npos)
	{
		s.erase(pos, oldVal.size()).insert(pos, newVal);
		pos += newVal.size();
		pos = s.find(oldVal,pos);
	}
}

void basicString::replaceWith2(string& s, const string& oldVal, const string& newVal)
{
	auto pos = s.find(oldVal);
	while (pos != string::npos)
	{
		s.replace(pos, oldVal.size(), newVal);
		pos += newVal.size();
		pos = s.find(oldVal, pos);
	}
}

void basicString::addPrefixAndPostfix(string& name, const string& prefix, const string& postfix)
{
	name.insert(name.begin(), prefix.begin(), prefix.end());
	name.append(postfix);
}

void basicString::addPrefixAndPostfix2(string& name, const string& prefix, const string& postfix)
{
	name.insert(0, prefix).insert(name.size()+prefix.size(), postfix);
}

void basicString::findSpecificChar(const string& s, const string& charset)
{
	string::size_type pos = 0;
	while ((pos = s.find_first_of(charset,pos)) != string::npos)
	{
		std::cout << "specific character is at index: " << pos
			<< std::endl << "char is: " << s[pos] << std::endl;
		++pos;
	}
}

void basicString::findSpecificChar2(const string& s, const string& charset)
{
	string::size_type pos = 0;
	while ((pos = s.find_first_not_of(charset,pos)) != string::npos)
	{
		std::cout << "specific character is at index: " << pos
			<< std::endl << "char is: " << s[pos] << std::endl;
		++pos;
	}
}

void basicString::findLongestSpecificWord(const vector<string>& text,const string& notChar)
{
	auto iter = std::max_element(text.begin(), text.end(), [&](const string& lhs, const string& rhs) ->bool
	{
		string::size_type lsize(0), rsize(0);
		if (lhs.find_first_of(notChar) == string::npos)
			lsize = lhs.size();
		if (rhs.find_first_of(notChar) == string::npos)
			rsize = rhs.size();
		return lsize < rsize;
	});
	if (iter != text.end())
		std::cout << "Longest word without specific character is :" << *iter << std::endl;
	else
		std::cout << "input text is empty" << std::endl;
}

Date::Date(const string& date)
{
	if (date.find_first_of("JFMASOND") != string::npos)
		engVersion(date);
	else
	{
		string number("0123456789");
		string::size_type pos = 0, end_pos = 0;
		pos = date.find_first_of(number);
		end_pos = date.find_first_not_of(number, pos);
		day = std::stoi(date.substr(pos,end_pos - pos));
		pos = end_pos;
		month = std::stoi(date.substr(pos = date.find_first_of(number,pos),
			date.find_first_not_of(number, pos) - pos));
		year = std::stoi(date.substr(date.find_last_not_of(number)+1));
	}
}

void Date::engVersion(const string& date)
{
	string::size_type pos = 0;
	if ((pos = date.find("Jan")) != string::npos)
		month = 1;
	else if ((pos = date.find("Feb")) != string::npos)
		month = 2;
	else if ((pos = date.find("Mar")) != string::npos)
		month = 3;
	else if ((pos = date.find("Apr")) != string::npos)
		month = 4;
	else if ((pos = date.find("May")) != string::npos)
		month = 5;
	else if ((pos = date.find("Jun")) != string::npos)
		month = 6;
	else if ((pos = date.find("Jul")) != string::npos)
		month = 7;
	else if ((pos = date.find("Aug")) != string::npos)
		month = 8;
	else if ((pos = date.find("Sep")) != string::npos)
		month = 9;
	else if ((pos = date.find("Oct")) != string::npos)
		month = 10;
	else if ((pos = date.find("Nov")) != string::npos)
		month = 11;
	else if ((pos = date.find("Dec")) != string::npos)
		month = 12;
	string number("0123456789");
	day = std::stoi(date.substr(pos = date.find_first_of(number), 
		date.find_first_not_of(number, pos) - pos));
	year = std::stoi(date.substr(date.find_last_not_of(number)+1));
}