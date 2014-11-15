#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_
#include <memory>

class BinaryNode;
class AddNode;
class MultiplyNode;

class Node
{
public:
	virtual double calculate() const = 0;
	friend std::shared_ptr<Node> operator+ (std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs);
	friend std::shared_ptr<Node> operator* (std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs);
	friend std::shared_ptr<Node> operator- (std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs);
	friend std::shared_ptr<Node> operator/ (std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs);
};

class NumNode :public Node
{
public:
	NumNode(double val) :value(val) {}
	virtual double calculate() const { return value; }
private:
	double value;
};

class BinaryNode :public Node
{
public:
	BinaryNode(std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs)
		:left(lhs), right(rhs) {}
protected:
	std::shared_ptr<Node> left, right;
};

class AddNode :public BinaryNode
{
public:
	AddNode(std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs) :BinaryNode(lhs, rhs){}
	virtual double calculate() const;
};

class MultiplyNode :public BinaryNode
{
public:
	MultiplyNode(std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs) :BinaryNode(lhs, rhs){}
	virtual double calculate() const;
};

class MinusNode :public BinaryNode
{
public:
	MinusNode(std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs) :BinaryNode(lhs, rhs){}
	virtual double calculate() const;
};

class DivideNode :public BinaryNode
{
public:
	DivideNode(std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs) :BinaryNode(lhs, rhs) {}
	virtual double calculate() const;
};


#endif