#ifndef _EXTRACTSTH_H_
#define _EXTRACTSTH_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*This program is for extracting a lot of filename such as "xxxxx.h" or "xxxx.inl" 
  or "xxxx.cpp" from a serious of html website.
*/

class extractSth
{
public:
	ifstream& getFilename(ifstream& in);
	void stateGraph(const string& str, string::size_type& ix);
	void getTarget();
	void writeResults();
private:
	vector<string> filename;
	vector<string> results;
};




#endif