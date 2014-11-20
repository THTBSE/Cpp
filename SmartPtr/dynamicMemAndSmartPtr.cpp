#include "dynamicMemAndSmartPtr.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

vector<int>* dynamicMemAndSmartPtr::constructVec()
{
	return new vector < int > ;
}

void dynamicMemAndSmartPtr::cinVec(vector<int>* Vec)
{
	if (!Vec)
		throw std::runtime_error("empty pointer!");
	int val;
	while (cin >> val)
	{
		Vec->push_back(val);
	}
}

void dynamicMemAndSmartPtr::coutVec(vector<int>* Vec)
{
	if (!Vec)
		throw std::runtime_error("empty pointer!");
	for (auto iter = Vec->begin(); iter != Vec->end(); ++iter)
	{
		cout << *iter << endl;
	}
}

void dynamicMemAndSmartPtr::exec12_6()
{
	vector<int> *pv = constructVec();
	cinVec(pv);
	coutVec(pv);
	delete pv;
}