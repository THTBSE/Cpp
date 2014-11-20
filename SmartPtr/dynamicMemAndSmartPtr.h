#ifndef _DYNAMICMEMANDSMARTPTR_H_
#define _DYNAMICMEMANDSMARTPTR_H_
#include <vector>
using std::vector;

class dynamicMemAndSmartPtr
{
public:
	//C++ Primer 5th 12.6
	vector<int>* constructVec();
	void cinVec(vector<int>* Vec);
	void coutVec(vector<int>* Vec);
	void exec12_6();

	
};




#endif