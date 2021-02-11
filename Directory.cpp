#include <iostream>
#include "Directory.h"
using namespace std;

	//Full constructor
	Directory::Directory(string n, int o, int m) {
		name = n;
		numObj= o;
		memLoc = m;
	}
		
		
	//Getters and Setters
	void Directory::setName(string n) {
	name = n;
	}
	string Directory::getName() {
		return name;
	}
	void Directory::setNumObj(int n) {
		numObj = n;
	}
	
	int Directory::getNumObj() {
		return numObj;
	}
	void Directory::setMemLoc(int m) {
		memLoc = m;
	}
	
	int Directory::getMemLoc() {
		return memLoc;
	}