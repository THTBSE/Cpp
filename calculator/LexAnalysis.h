#ifndef _LEXANALYSIS_H_
#define _LEXANALYSIS_H_
#include <string>
#include <memory>
#include <vector>
#include <unordered_set>
#include <iostream>
using std::string;
using std::unordered_set;
using std::shared_ptr;
using std::vector;

// 1 -> number 
// 2 -> operator '+' '-' '*' '/' '%' '(' ')' and so on

class elem
{
public:
	virtual int type() const = 0;
	virtual char getOp() const { return '#'; }
	virtual double getNum() const { return std::numeric_limits<double>::max(); }
};

class NumElem :public elem
{
public:
	NumElem(double v) :val(v){}
	virtual int type() const { return 1; }
	virtual double getNum() const { return val; }
private:
	double val;
};

class OpElem :public elem
{
public:
	OpElem(char c) :op(c){}
	virtual int type() const { return 2; }
	virtual char getOp() const { return op; }
private:
	char op;
};

class invalidInput :public std::runtime_error
{
public:
	invalidInput(const string& str) :std::runtime_error(str){}
};
//state graph for processing numeric 
class LexAnalysis
{
	typedef shared_ptr<elem> elemPtr;
public:
	LexAnalysis(const string& str) :input(str), state(0){ initializeOpTable(); }
	void runLex();

private:
	void initializeOpTable();
	string::size_type stateGraph(string::size_type ix, const string& str);
	unordered_set<char> opTable;
	string input;
	int state;
public:
	vector<elemPtr> elements;
};





#endif