#ifndef TEXT
#define TEXT
#include <iostream>
#include <string>
using namespace std;
class Text {
	
	//variables
	private:
	string name;
	int size;
	string contents;
	
	public:
	
	//full constructor
	Text(string n, int s , string c);
	
	//constructor without size, calls findSize function, primary constructor
	Text(string n, string c);
	
	//determines size of contents
	void findSize();
	
	//getters and setters
	void setName(string n);
	string getName();
	void setSize(int s);
	int getSize();
	void setContents(string c);
	string getContents();	
		
		
	
};

#endif
