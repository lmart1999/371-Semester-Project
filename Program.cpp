#include <iostream>
#include "Program.h"


using namespace std;


	Program::Program(string n, int c, int m) {
		name = n;
		cpuReq = c;
		memReq = m;
		startIOTime = -1;
		totalIOTime = -1;
	}
		
	Program::Program(string n, int c, int m, int s, int t) {
		name = n;
		cpuReq = c;
		memReq = m;
		startIOTime = s;
		totalIOTime = t;
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
	void Program::setTotalIOTime(int t) {
		totalIOTime=t;
	}
	
	int Program::getTotalIOTime() {
		return totalIOTime;
	}
	void Program::setStartIOTime(int s) {
		startIOTime=s;
	}
	
	int Program::getStartIOTime() {
		return startIOTime;
	}
	void Program::setRunTime(int r) {
		runTime=r;
	}
	
	int Program::getRunTime() {
		return runTime;
	}
	void Program::setFinTime(int f) {
		finTime=f;
	}
	
	int Program::getFinTime() {
		return finTime;
	}
	void Program::setStartTime(int s) {
		startTime=s;
	}
	
	int Program::getStartTime() {
		return startTime;
	}