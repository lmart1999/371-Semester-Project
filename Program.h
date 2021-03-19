/*Creates the Program Object
Purpose: to create a program object and store its relevant information memory requirements, cpu requirements, and name
Constructor requires all parameters to be input
Output: none
Called by: RUFS.cpp createProgramFile

*/
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
	int startIOTime;
	int totalIOTime;
	int runTime = 0;
	int finTime =0;
	int startTime = -1;

	
	public:
	
	//partial constructor
	Program(string n, int c , int m);
	//full constructor
	Program(string n, int c , int m, int s, int t);

	
	//getters and setters
	void setName(string n);
	string getName();
	void setCpuReq(int c);
	int getCpuReq();
	void setMemReq(int m);
	int getMemReq();	
	void setTotalIOTime(int t);
	int getTotalIOTime();
	void setStartIOTime(int s);
	int getStartIOTime();
	void setRunTime(int r);
	int getRunTime();
	void setFinTime(int t);
	int getFinTime();
	void setStartTime(int s);
	int getStartTime();
};

#endif
