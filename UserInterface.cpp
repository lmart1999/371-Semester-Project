/*
Purpose: to manage user input and call the correct class or function based on inputted command, also validates the command
Input: takes a stack of Directories containing the root as well as a Diskmanager reference in the constructor
Calls: Directory, Program, Text, Maker, DiskManager
Called by: RUSH
Programmer: Luke Martin
*/
#include <stack>
#include <queue>
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include "Text.h"
#include "Program.h"
#include "Directory.h"
#include "DiskManager.h"
#include "Maker.h"
#include "Simulator.h"
#include "UserInterface.h"
using namespace std;


	Maker make;
	stack<Directory> *directories;
	DiskManager *dMan;
	stack<Directory> list;
	Simulator *sim;

	
	//primary constructor, called from main to create Text files and determine size
	UserInterface::UserInterface(stack<Directory> &d, DiskManager &dd) {
		directories = &d;
		make.setDiskManager(dd);
		dMan = &dd;
		
		//No Idea why I had to do this and couldn't declare them in Simulator but gave me a segmentation error
		queue<Program> temp;
		queue<Program> temp2;
		queue<Program> temp3;
		Simulator s("sim", temp, temp2, temp3);
		sim = &s;
		menu();
		
	}
	
	
	//Processes all commands and calls the relevant function or class needed to complete them
	void UserInterface::menu() {
		//variable that will be used for all searchs
		string search;
		//variables for program simulation
		int burst = -1; //varaibel for the birst amount of the round robin style advancement
		int stepAmt; // variablle to control the amount the simulation advances
		//variable that will be used to temporarily hold input data before putting it into the file
		string command;
			//Introduction to the Program
		cout << "Welcome to RATCH. Enter A Command "<< endl;
		//cout << "mkdir or CreateFile or quit "<< endl;
		//Enter Commands
		cout << "Command: " ;
		cin >> command;
		//changes command to all lowercase
		transform(command.begin(), command.end(), command.begin(), ::tolower);
		//Loop that goes through the commands and calls functions to create files, directories, or quit the program
		while (command != "quit") {
			//Executes the createDir command
			if (command == "mkdir") {
				//calls the create directoy file to make a new properly named and formatted directory object to add to the stack
				Directory temp =make.createDirectory(directories->top().getMemLoc()); 
				//adds new directory to the stack
				//directories->push(temp);
				//Executes the CreateFile command
			}else if (command == "createfile") {
				make.createFileName(directories->top().getMemLoc()); //creates and writes a text or program file to the binary file
				//pulls top directory off, adds one to its num of programs and replaces it on the stack
				Directory mod = directories->top();
				mod.setNumObj(mod.getNumObj()+1);
				directories->pop();
				directories->push(mod);
			//Executes the EndDir Command
			}else if (command == "ls") {
				cout<<"\n";
				cout << "Directory Name: " << directories->top().getName() << endl;
				dMan->ls(directories->top().getMemLoc());
			}else if (command == "pwd") {
				pwd();
			}else if (command == "cat") {
				cin >>search;
				search = make.namePadder(search);
				dMan->cat(directories->top().getMemLoc(), search);	
			}else if (command == "run") {
				if(burst != -1) {
					cout << "Advancing the System until all jobs are finished" << endl;
					sim->run(burst);
				}else {
					cout <<"You must set the burst time" <<endl;
				}
			}else if (command == "start") { //starts a program if memory is available
				cin >>search;
				search = search +".p";
				search = make.namePadder(search);
				Program temp = dMan->start(directories->top().getMemLoc(), search);
				if(temp.getName()!="NULL" && temp.getCpuReq()!=-1) {
					sim->addProg(temp);
				}
			}else if (command == "cd") {
				cd();
			}else if (command == "step") { //steps through the programs
				cin >>stepAmt;
				if(burst != -1) {
					cout << "Advancing the System " << stepAmt << " units" << endl;
					sim->step(burst, stepAmt);
				}else {
					cout <<"You must set the burst time" <<endl;
				}
			}else if (command == "setburst") { //sets Burst Time
				cin >>burst;
				while(burst<2) {
					cout <<"Burst size must be at least 2. Please enter a new burst size: ";
					cin >> burst;
				}
				
			}else if (command == "setmemory") { //sets system Memory
				int mem; //temp variable that stores current sys mem to be outputted
				cin >> mem;
				while(mem<1) {
					cout <<"Memory size must be at least 1. Please enter a new memory size: ";
					cin >> mem;
				}
				sim->setSysMem(mem);
			}else if (command == "addprogram") { //adds a program by calling createProgramFileName in maker
				make.createProgFileName(directories->top().getMemLoc());
			}else if (command == "getmemory") { //returns current amount of system memory
				cout <<"System Memory = " << sim->getSysMem() << endl;
			}else if (command == "printinfo") { //prints all info about the file systme
				dMan->reader(directories->top().getMemLoc());
			}else {
				cout <<command << " Invalid Command" << endl;
			}
			//Enter Commands
			cout << "Command: " ;
			cin >> command;
			//changes command to all lowercase
			transform(command.begin(), command.end(), command.begin(), ::tolower);
		}
	}
	/*
	Purpose: obtains search parameter and either returns to previous directory or calls disk manager to search for a sub directory
	Input: user inputted directory name
	Output: none
	Calledby: menu
	calls: Directory, diskmanager, maker, directories
	
	*/
	
	void UserInterface::cd() {
		string search;
		cin >>search;
		if(search == "..") {
			Directory temp = directories->top();
			directories->pop();
			if( directories->empty()) {
				cout << "In root directory" << endl;
				directories->push(temp);
			}
		}else {
			search = search +".d";
			search = make.namePadder(search);
			Directory temp = dMan->cd(directories->top().getMemLoc(), search);
			if(temp.getName() != "null") {
				directories->push(temp);
			}
		}
		return;
	}
	/*
	Purpose: Print out the path of the current directory
	Input: none
	Output: full path of current directory
	Calledby: menu
	calls: Directory, directories, stack
	
	*/
	
	void UserInterface::pwd() {
		cout <<"Current Directory: ";
		while (!directories->empty()){
			Directory temp = directories->top();
			directories->pop();
			list.push(temp);
		}
		while (!list.empty()){
			Directory temp = list.top();
			list.pop();
			directories->push(temp);
			cout <<"/"<< temp.getName() ;
		}
		cout <<"\n";
	}
	
