#include <iostream>
#include "Program.h"


using namespace std;


	Program::Program(string n, int c, int m) {
		name = n;
		cpuReq = c;
		memReq = m;
	}
		
		
		
		
	//getters and Setters
	void Program::setName(string n) {
	name = n;
	}
	
	string Program::getName() {
		return name;
	}
	
	void Program::setCpuReq(int c) {
		cpuReq = c;
	}
	
	int Program::getCpuReq() {
		return cpuReq;
	}
	
	void Program::setMemReq(int m) {
		memReq=m;
	}
	
	int Program::getMemReq() {
		return memReq;
	}
	