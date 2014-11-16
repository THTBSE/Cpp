#ifndef _BASICSTRING_H_
#define _BASICSTRING_H_
#include <string>
#include <vector>
#include <numeric>
using std::string;
using std::vector;

class basicString
{
public:
	//C++ Primer 5th Ed exercise 9.43
	void replaceWith(string& s, const string& oldVal, const string& newVal);
	//C++ Primer 5th Ed exercise 9.44
	void replaceWith2(string& s, const string& oldVal, const string& newVal);
	//C++ Primer 5th Ed exercise 9.45
	void addPrefixAndPostfix(string& name, const string& prefix, const string& postfix);
	//C++ Primer 5th Ed exercise 9.46
	void addPrefixAndPostfix2(string& name, const string& prefix, const string& postfix);
	//C++ Primer 5th Ed exercise 9.47
	void findSpecificChar(const string& s, const string& charset);
	void findSpecificChar2(const string& s, const string& charset);
	//C++ Primer 5th Ed exercise 9.49
	void findLongestSpecificWord(const vector<string>& text, const string& notChar);
	//C++ Primer 5th Ed exercise 9.50
	template <typename T>
	T sum(const vector<string>& s, int type);
};

template <typename T>
T basicString::sum(const vector<string>& s, int type)
{
	T sum = static_cast<T>(0);
	switch (type)
	{
	case 0:
	{
		sum = std::accumulate(s.begin(), s.end(), sum, [](T val,const string& s) ->int
		{
			return std::stoi(s) + val;
		});
		break;
	}
	case 1:
	{
		sum = std::accumulate(s.begin(), s.end(), sum, [](T val,const string& s) ->double
		{
			return std::stod(s) + val;
		});
	}
	default:
		break;
	}
	return sum;
}

class Date
{
public:
	Date(const string& date);
private:
	void engVersion(const string& date);
	unsigned year, month, day;
};


#endif