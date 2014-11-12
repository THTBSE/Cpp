#ifndef _EXCEPTIONPRACTICE_H_
#define _EXCEPTIONPRACTICE_H_
#include <iostream>
#include <exception>
#include <string>

//exercises of exception mechanism 

template <typename T>
T Divide()
{
	std::cout << "Please input two number a and b,We will calculate the result of a/b" << std::endl;
	T a, b;
	while (std::cin >> a >> b)
	{
		try
		{
			if (b == 0)
				throw std::runtime_error("denominator can not be zero.");
			break;
		}
		catch (std::runtime_error &msg)
		{
			std::cout << msg.what() << "Enter 'y' try again or 'n' quit." << std::endl;
			char c;
			std::cin >> c;
			if (!std::cin || c == 'n')
				break;
		}
	}
	T ret = a / b;
	std::cout << "a/b is : " << ret << std::endl;
	return ret;
}

class people
{
public:
	people(std::string n, double m = 0.0) :name(n), money(m) {}
	people& operator+= (const people& rhs);
	const std::string& Name() const
	{
		return name; 
	}
	void showMoney() { std::cout << name << "has " << money << "$!" << std::endl; }
private:
	double money;
	std::string name;
};

class name_mismatch : public std::logic_error
{
public:
	name_mismatch(const std::string &s, const std::string &lhs,
		const std::string &rhs) :std::logic_error(s), left(lhs), right(rhs) {}
	const std::string left, right;
};

people& people::operator+= (const people& rhs)
{
	if (Name() != rhs.Name())
		throw name_mismatch("wrong people", Name(), rhs.Name());
	money += rhs.money;
	return *this;
}

#endif