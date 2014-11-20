#include "LexAnalysis.h"

//int main()
//{
//	string str("3.145+((1e-2+0.3e2)*0.25)/3");
//	LexAnalysis la(str);
//	try
//	{
//		la.runLex();
//	}
//	catch (const invalidInput& msg)
//	{
//		std::cout << msg.what() << std::endl;
//	}
//	
//	for (size_t i = 0; i < la.elements.size(); i++)
//	{
//		if (la.elements[i]->type() == 1)
//			std::cout << la.elements[i]->getNum();
//		else
//			std::cout << la.elements[i]->getOp();
//	}
//	while (true)
//	{
//
//	}
//}