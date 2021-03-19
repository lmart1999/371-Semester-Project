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
#include "UserInterface.h"
using namespace std;


	Maker make;
	stack<Directory> *directories;
	DiskManager *dMan;
	stack<Directory> list;
	queue<Program> *programs;
	queue<Program> *finished;
	queue<Program> *IO;
	int sysTime = 0;
	int sysMem = 0;

	
	//primary constructor, called from main to create Text files and determine size
	UserInterface::UserInterface(stack<Directory> &d, DiskManager &dd) {
		directories = &d;
		make.setDiskManager(dd);
		dMan = &dd;
		queue<Program> temp;
		programs = &temp;
		queue<Program> temp2;
		finished = &temp2;
		queue<Program> temp3;
		IO = &temp3;
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
			//Intorduction to the Program
		cout << "Welcome to RUSH. Enter A Command "<< endl;
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
					run(burst);
				}else {
					cout <<"You must set the burst time" <<endl;
				}
				
			}else if (command == "start") {
				cin >>search;
				search = search +".p";
				search = make.namePadder(search);
				Program temp = dMan->start(directories->top().getMemLoc(), search);
				if(temp.getMemReq()>sysMem) {
					cout <<"Not enough memory to run" <<endl;
				} else {
					sysMem = sysMem-temp.getMemReq();
					programs->push(temp);
				}
			}else if (command == "cd") {
				cd();
			}else if (command == "step") {
				cin >>stepAmt;
				if(burst != -1) {
					cout << "Advancing the System " << stepAmt << " units" << endl;
					step(burst, stepAmt);
				}else {
					cout <<"You must set the burst time" <<endl;
				}
			}else if (command == "setburst") {
				
				cin >>burst;
				
			}else if (command == "setmemory") {
				
				cin >> sysMem;
				
			}else if (command == "addprogram") {
				
				make.createProgFileName(directories->top().getMemLoc());
				
			}else if (command == "getmemory") {
				
				cout <<"System Memory = " << sysMem << endl;
				
			}else if (command == "printinfo") {
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
	
	/*
	Purpose: to go through all current jobs and finish them in a round robin style based on burst time
	intput: burst time
	output: to console
	called by: menu
	calls: update Run
	
	*/
	
	void UserInterface::run(int bt) {
		int startTime = sysTime; //to keep track of total Time to Execute
		int done; //flag to know when to exit for loop
		int sIO; //start IO time
		//loop to run until Queue is empty
		while (!programs->empty() || !IO->empty()) {
			done = 0;
			
			updateRun();
			
			
			//increments jobs by burst time
			for(int i = 0; i<bt;i++) {
				
				//cout << "\n\n" << programs->front().getName() << "\n\n";

				
				if(!IO->empty()) {
					cout << "\tThe process " << IO->front().getName() << " is obtaining IO and will be back in " << IO->front().getTotalIOTime() << " units" <<endl;
					IO->front().setTotalIOTime(IO->front().getTotalIOTime() -1);
					if(programs->empty()) sysTime++;
					if(IO->front().getTotalIOTime() == 0) {
						IO->front().setStartIOTime(-1);
						programs->push(IO->front());
						IO->pop();
					}
				}
				if(programs->front().getStartIOTime() == programs->front().getRunTime()) {
					IO->push(programs->front());
					programs->pop();
					i=bt;
					done = -1;
				}
				if (done!=-1){
					sysTime++;
					programs->front().setCpuReq(programs->front().getCpuReq() -1);
					programs->front().setRunTime(programs->front().getRunTime() +1);
					if(programs->front().getCpuReq() == 0){
						programs->front().setFinTime(sysTime-startTime);
						sysMem = sysMem+programs->front().getMemReq();
						finished->push(programs->front());
						programs->pop();
						i = bt+1;
					}
					
				}
					
				
			}
			
			
		}
		updateRun();
		return;
	}
	/*
	Purpose: to go through all current jobs for a certain amount of time and finish them in a round robin style based on burst time
	intput: burst time, step amount
	output: to console
	called by: menu
	calls: update Run
	
	*/
	
	void UserInterface::step(int bt, int stepAmt) {
		int startTime = sysTime; //to keep track of total Time to Execute
		
		int counter = 0;
		if((programs->size())>=1){
			while (counter < programs->size()) {
				if(programs->front().getStartTime() == -1) {
					programs->front().setStartTime(sysTime);
				}
				programs->push(programs->front());
				programs->pop();
				counter++;
			}
		}
		
		int done; //flag to know when to exit for loop
		int sIO; //start IO time
		//loop to run until Queue is empty
		if((programs->empty() && IO->empty()) ) {
			sysTime = sysTime +stepAmt;
		}
		
		while (((!programs->empty() || !IO->empty()) )&& ((sysTime-startTime)<stepAmt)) {
			done = 0;
		
			updateRun();
			if(bt>(stepAmt-(sysTime-startTime))){
				bt = stepAmt-(sysTime-startTime);
			}
			
			//increments jobs by burst time
			for(int i = 0; i<bt;i++) {
				
				//cout << "\n\n" << programs->front().getName() << "\n\n";

				
				if(!IO->empty()) {
					cout << "\tThe process " << IO->front().getName() << " is obtaining IO and will be back in " << IO->front().getTotalIOTime() << " units" <<endl;
					IO->front().setTotalIOTime(IO->front().getTotalIOTime() -1);
					if(programs->empty()) sysTime++;
					if(IO->front().getTotalIOTime() == 0) {
						IO->front().setStartIOTime(-1);
						programs->push(IO->front());
						IO->pop();
					}
				}
				if(programs->front().getStartIOTime() == programs->front().getRunTime()) {
					IO->push(programs->front());
					programs->pop();
					i=bt;
					done = -1;
				}
				if (done!=-1 &&(sysTime-startTime !=stepAmt)){
					sysTime++;
					programs->front().setCpuReq(programs->front().getCpuReq() -1);
					programs->front().setRunTime(programs->front().getRunTime() +1);
					if(programs->front().getCpuReq() == 0){
						programs->front().setFinTime(sysTime-(programs->front().getStartTime()));
						sysMem = sysMem+programs->front().getMemReq();
						finished->push(programs->front());
						programs->pop();
						i = bt+1;
					}
					
				}
				if(sysTime-startTime ==stepAmt) {
					i = bt;
				}
				
			}
			
			
		}
		
		if(sysTime-startTime <stepAmt) {
			updateRun();
			sysTime = sysTime+(stepAmt-(sysTime-startTime));
		}
		
		updateRun();
		return;
	}
	/*
	Purpose: to Print infor about currently running, queued and finished jobs to the console
	input: none
	called by: run
	calls: nothing
	
	*/
	
	
	void UserInterface::updateRun() {
		cout << "\nCurrent Time <" << sysTime << ">" << endl;
		
		if(programs->size()>0){
		cout <<"Running job " << programs->front().getName() << " has " << programs->front().getCpuReq() << " time left and is using "<< programs->front().getMemReq() << " memory resources." << endl;
		}else {
			cout << "Running Job is empty" << endl;
		}
		cout <<"The queue is: ";
		int counter = 1;
		if(!programs->empty()){
			programs->push(programs->front());
			programs->pop();
		}
		if((programs->size())>1){
			cout << endl;
			while (counter < programs->size()) {
				cout << "\tPosition " << counter << ": job " << programs->front().getName() << " has " << programs->front().getCpuReq() << " units left and is using "<< programs->front().getMemReq() << " memory resources." << endl;
				programs->push(programs->front());
				programs->pop();
				counter++;
			}
		} else {
			cout << "empty" << endl;
		}
		
		
		if(!finished->empty()) {
			cout << "Finished Jobs are: "<< endl;
			for (int j = 0; j <finished->size(); j++) {
				cout << "\t" << finished->front().getName() << " " << finished->front().getRunTime() << " " << finished->front().getFinTime() << " " << endl;
				finished->push(finished->front());
				finished->pop();
			}
			
		}
		
	}