#ifndef PROGRAM
#define PROGRAM
#include <iostream>
#include <string>
using namespace std;
class Program {
	//variables
	private:
	string name;
	int cpuReq;
	int memReq;
	
	public:
	
	//full constructor
	Program(string n, int c , int m);
	

	
	//getters and setters
	void setName(string n);
	string getName();
	void setCpuReq(int c);
	int getCpuReq();
	void setMemReq(int m);
	int getMemReq();	
		
		
	
};

#endif
