#include "dynamicMemAndSmartPtr.h"
#include <memory>
using std::shared_ptr;

void process(shared_ptr<int> ptr)
{
	int i = *ptr;
}



int main()
{
	shared_ptr<int> p(new int(42));
	process(p);
	int k = *p;
	dynamicMemAndSmartPtr dmasp;
	dmasp.exec12_6();
	while (true)
	{

	}
}