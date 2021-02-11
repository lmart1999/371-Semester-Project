/*Creates the Directory Object
Purpose: to create a Directory object and store its relevant information memory location, number of stored objects, and name
	Memory location is stored so main can go back into the binary file and change the number of written objects
Constructor requires all parameters to be input but number of objects will likely be updated later
Output: none
Called by: RUFS.createDirrctory, RUFS.writeDir, RUFS.main
S

*/
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
