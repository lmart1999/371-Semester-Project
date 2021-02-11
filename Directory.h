#ifndef DIRECTORY
#define DIRECTORY
#include <iostream>
#include <string>
using namespace std;
class Directory {
	
	//variables
	private:
	string name;
	int numObj;
	int memLoc;
	
	
	public:
	
	//full constructor
	Directory(string n, int o, int m);
	
	//getters and setters
	void setName(string n);
	string getName();
	void setNumObj(int o);
	int getNumObj();
	void setMemLoc(int m);
	int getMemLoc();
	
};

#endif
