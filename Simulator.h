/*Creates the UserInterface Object
Purpose: to create and manage the Queues needed for job Simulation
Constructor requires no input
Output: none
Called by: UserInterface.cpp UserInterface

*/
#ifndef SIMULATOR
#define SIMULATOR
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include "Program.h"
using namespace std;


class Simulator {
	
	//variables
	private:
		string name;
		queue<Program> *programs;
		queue<Program> *finished;
		queue<Program> *IO; //queue to contain jobs in IO
		int sysTime;
		int sysMem;
		int bCount;

	
	public:
	
	//full constructor
	Simulator(string n, queue<Program> &p, queue<Program> &f, queue<Program> &i);
	/*
	Purpose: to go through all current jobs and finish them in a round robin style based on burst time
	intput: burst time
	output: to console
	called by: menu
	calls: update Run
	
	*/
	void run(int bt);
	/*
	Purpose: updates the IO Queue and prints out which jobs are in IO
	Input: nothing
	output: to console
	called by: step, run
	*/
	void IOup(int i);
	/*
	Purpose: to go through all current jobs for a certain amount of time and finish them in a round robin style based on burst time
	intput: burst time, step amount
	output: to console
	called by: menu
	calls: update Run
	
	*/
	void step(int bt, int stepAmt);
	
	/*
	Purpose: To display information about currently running and finished programs
	input: none
	called by: run, step
	*/
	void updateRun();
	
	//adds a program to the running jobs if there is enough memory to support it, basically a setter

	void addProg(Program p);
	//getters and setters
	void setSysMem(int s);
	int getSysMem();

};

#endif
