#include "calculator.h"
#include <iostream>

std::shared_ptr<Node> operator+ (std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs)
{
	return std::make_shared<AddNode>(AddNode(lhs, rhs));
}

std::shared_ptr<Node> operator* (std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs)
{
	return std::make_shared<MultiplyNode>(MultiplyNode(lhs, rhs));
}

std::shared_ptr<Node> operator- (std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs)
{
	return std::make_shared<MinusNode>(MinusNode(lhs, rhs));
}

std::shared_ptr<Node> operator/ (std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs)
{
	return std::make_shared<DivideNode>(DivideNode(lhs, rhs));
}

double AddNode::calculate() const
{
	return left->calculate() + right->calculate();
}

double MultiplyNode::calculate() const
{
	return left->calculate() * right->calculate();
}

double MinusNode::calculate() const
{
	return left->calculate() - right->calculate();
}

double DivideNode::calculate() const
{
	double lhs = left->calculate();
	double rhs = right->calculate();
	auto isZero = [](double val) ->bool
	{
		return fabs(val) < 1.0e-6;
	};
	if (isZero(rhs))
		throw std::runtime_error("denominator can not be zero.");
	return lhs / rhs;
}