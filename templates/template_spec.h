#ifndef _TEMPLATE_SPEC_H_
#define _TEMPLATE_SPEC_H_
#include <algorithm>
#include <string>
#include <iostream>

//C++ Primer 4th 16.52 
template <typename Container, typename T>
size_t Count(const Container& vec, const T& val)
{
	size_t count = 0;
	std::for_each(vec.begin(), vec.end(), [&](const T& item)
	{
		if (item == val)
			++count;
	});
	return count;
}

//C++ Primer 4th 16.54
template <>
size_t Count<std::string, char>(const std::string& str, const char& c)
{
	size_t count = 0;
	std::for_each(str.begin(), str.end(), [&](char x)
	{
		if (x == c)
			++count;
	});
	return count;
}

//C++ Primer 4th 16.61
template <typename T>
int Compare(const T& lhs, const T& rhs)
{
	std::cout << "standard Compare<T>" << std::endl;
	if (lhs < rhs)
		return 1;
	else if (rhs < lhs)
		return -1;
	else
		return 0;
}

template <typename Iter1, typename Iter2>
int Compare(Iter1 beg1, Iter1 end1, Iter2 beg2)
{
	std::cout << "sequence Compart<Iter1,Iter2>" << std::endl;
	while (beg1 != end1)
	{
		if (*beg1 < *beg2)
			return 1;
		else if (*beg2 < *beg1)
			return -1;
		else
		{
			++beg1;
			++beg2;
		}
	}
	return 0;
}

template <>
int Compare<double>(const double& lhs, const double& rhs)
{
	std::cout << "specialization template ,double edition" << std::endl;
	if (lhs < rhs)
		return 1;
	else if (rhs < lhs)
		return -1;
	else
		return 0;
}

int Compare(const char* str1, const char* str2)
{
	std::cout << "ordinary Compare" << std::endl;
	return strcmp(str1, str2);
}
#endif