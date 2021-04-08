/*
Purpose: To manage all running jobs and simulate job completion, IO, and a round robin style queue of variable burst size
Input: Takes a name and 3 queues, one for finished jobs, one for jobs in IO, and one for running jobs
Calls: Program
Called by: UserInterface
Programmer: Luke Martin
*/
#include <queue>
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include "Program.h"
#include "Simulator.h"
using namespace std;

	string name;
	queue<Program> *programs; //queue containing running jobs
	queue<Program> *finished; //Queue containing finished jobs
	queue<Program> *IO; //queue to contain jobs in IO

	
	//primary constructor, called from main to Simulator and initialize variabel
	Simulator::Simulator(string n, queue<Program> &p,queue<Program> &f ,queue<Program> &i) {
		name = n;
		//queue<Program> temp;
		programs = &p;
		//queue<Program> temp2;
		finished = &f;
		//queue<Program> temp3;
		IO = &i;
		sysTime = 0; //Holds overall system time
		sysMem = 0; //holds remaining system memory
		bCount = 0; //holds amount of burst time that has been executed
		totalMem=0; //holds total mem of the system
	}
	
	
	/*
	Purpose: to go through all current jobs and finish them in a round robin style based on burst time
	intput: burst time
	output: to console
	called by: menu
	calls: update Run
	
	*/
	
	void Simulator::run(int bt) {
		int done; //flag to know when to exit for loop
		int counter = 0; //counter to know when to stop cycling
		//Loop to check and update start times for all porgrams in the queue to ensure accurate total run times, only runs if queue is not empty
		if(!programs->empty() && (programs->size())>=1){
			while (counter < programs->size()) {
				//only updates start times if they have not been updated before
				if(programs->front().getStartTime() == -1) {
					programs->front().setStartTime(sysTime);
				}
				//cycles through the queue
				programs->push(programs->front());
				programs->pop();
				counter++; 
			}
		}
		
		int btO = bt;//stores original input burst time
		//loop to run until Queue is empty
		while (!programs->empty() || !IO->empty()) {
			//flag variable that lets the program know if a job went to IO
			done = 0;
			//prints out current stats
			updateRun();
			if(bCount >0) {
				bt = bt-bCount;
				bCount =0;
			}else {
				bt = btO;
			}
			
			//increments jobs by burst time
			for(int i = 0; i<bt;i++) {
				
				//if there is something in IO increments its IO time by one
				if(!IO->empty()) {
					IOup(i);
				}
				//checks to see if the program needs to be transferred from disk
				if(!programs->empty() && programs->front().getOnDisk() ==0){

				//checks to see if a program needs to go to IO, if so sends it there and removes it from running queue
					if(!programs->empty() && programs->front().getStartIOTime() == programs->front().getRunTime()) {
						IO->push(programs->front());
						programs->pop();
						i=bt;
						bCount = 0;
						done = -1;
					}
					//checks to see if a program was just sent to IO, if so skips this to reset bt before running
					if (!programs->empty() && done!=-1){
						sysTime++;
						programs->front().setCpuReq(programs->front().getCpuReq() -1); //increments time needed
						programs->front().setRunTime(programs->front().getRunTime() +1); //increments time run
						if(programs->front().getCpuReq() == 0){ //if time needed is zero, sets the finishe time of the program, re-adds the memory used by the program to sysMem and moves the job to the finished queue, resets the loop/bt
							programs->front().setFinTime(sysTime-(programs->front().getStartTime()));
							sysMem = sysMem+programs->front().getMemReq();
							finished->push(programs->front());
							programs->pop();
							bCount =0;
							i = bt+1;
						}
					
					}
				
					if(i == bt-1) {
						programs->push(programs->front());
						programs->pop();
					}	
				}else if(!programs->empty() && programs->front().getOnDisk() !=0){	
					sysTime++;
					if(programs->front().getOnDisk() ==2 && sysMem < programs->front().getMemReq()) {
						clearSpace(programs->front());
					}
					programs->front().setOnDisk(programs->front().getOnDisk()-1);
					if(i == bt-1) {
						programs->push(programs->front());
						programs->pop();
					}
				}

				
			}
			
			
		}
		updateRun(); //prints out final stats
		return;
	}
	/*
	Purpose: updates the IO Queue and prints out which jobs are in IO
	Input: nothing
	output: to console
	called by: step, run
	*/
	
	void Simulator::IOup(int i) {
		if(i!=0) {
			cout << "\nCurrent Time <" << sysTime << ">" << endl;
		}
		cout << "\tThe process " << IO->front().getName() << " is obtaining IO and will be back in " << IO->front().getTotalIOTime() << " units" <<endl;
		IO->front().setTotalIOTime(IO->front().getTotalIOTime() -1);
		if(programs->empty()) sysTime++; //if there are no other programs goes ahead and increments system time
		if(IO->front().getTotalIOTime() == 0) { //if the program is done with IO removoes it from the IO queue and puts it back in the Normal one
			IO->front().setStartIOTime(-1);
			programs->push(IO->front());
			IO->pop();
		}		
		
	}
	
	/*
	Purpose: to go through all current jobs for a certain amount of time and finish them in a round robin style based on burst time
	intput: burst time, step amount
	output: to console
	called by: menu
	calls: update Run
	
	*/
	
	void Simulator::step(int bt, int stepAmt) {
		int startTime = sysTime; //to keep track of total Time to Execute
		
		int counter = 0; //counter to know when to stop cycling
		
		if((!programs->empty()) &&(programs->size())>=1){
		//Loop to check and update start times for all porgrams in the queue to ensure accurate total run times, only runs if queue is not empty			
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
		int btO = bt;//stores original input burst time
		//loop to run until Queue is empty
		
		
		while (((!programs->empty() || !IO->empty()) )&& ((sysTime-startTime)<stepAmt)) {
			done = 0;
		
			updateRun(); //prints out current stats
			//if the remaining step amount is less than burst time changes bt so that it only runs for the remaining time
			if(bt>(stepAmt-(sysTime-startTime))){
				bt = stepAmt-(sysTime-startTime);
			}
			
			//increments jobs by burst time
			for(int i = 0; i<bt;i++) {
				
				
				//if there is something in IO increments its IO time by one
				if(!IO->empty()) {
					IOup(i);
					
				}
				//checks to see if a program needs to go to IO, if so sends it there and removes it from running queue
				if(!programs->empty() && programs->front().getOnDisk() ==0){
					if(!programs->empty() && programs->front().getStartIOTime() == programs->front().getRunTime()) {
						programs->front().setStartIOTime(-1);
						IO->push(programs->front());
						programs->pop();
						i=bt+1;
						bCount = 0;
						done = -1;
					}
					//checks to see if a program was just sent to IO, if so skips this to reset bt before running
					if (!programs->empty() && done!=-1 &&(sysTime-startTime !=stepAmt)){
						sysTime++;
						programs->front().setCpuReq(programs->front().getCpuReq() -1); //increments time needed
						programs->front().setRunTime(programs->front().getRunTime() +1); //increments time run
						if(programs->front().getCpuReq() == 0){ //if time needed is zero, sets the finishe time of the program, re-adds the memory used by the program to sysMem and moves the job to the finished queue, resets the loop/bt
							programs->front().setFinTime(sysTime-(programs->front().getStartTime()));
							sysMem = sysMem+programs->front().getMemReq();
							finished->push(programs->front());
							programs->pop();
							bCount =0;
							i = bt+1;
						}	
					}
					if(i == bt-1&& bCount == btO) {
						programs->push(programs->front());
						programs->pop();
						bCount =0;
					}else {
						bCount++;
					}
					//If the program to run is on disk
					/*
					Needs updating for if available memory needs to be allocated
					
					
					*/
					
				}else if(!programs->empty() && programs->front().getOnDisk() !=0){
					sysTime++;
					if(programs->front().getOnDisk() ==2 && sysMem < programs->front().getMemReq()) {
						clearSpace(programs->front());
					}
					programs->front().setOnDisk(programs->front().getOnDisk()-1);
					if(i == bt-1&& bCount == btO) {
						programs->push(programs->front());
						programs->pop();
						bCount =0; //resets executed burst time to 0
					}else {
						bCount++;
					}
				}
				
				//ends the loop if reaches the end of the step amt
				if(sysTime-startTime ==stepAmt) {
					i = bt;
				}
				
			}
			
			
		}
		//updates the system time based on remaining step amount
		if((sysTime-startTime) < stepAmt) {
			updateRun();
			sysTime = sysTime+(stepAmt-(sysTime-startTime));
		}
		return;
	}
	
	/*
	Purpose: to Print info about currently running, queued and finished jobs to the console
	input: none
	called by: run, step
	calls: nothing
	*/
	
	
	void Simulator::updateRun() {
		cout << "\nCurrent Time <" << sysTime << ">" << endl; //prints current times
		
		 
		if(!programs->empty() && programs->size()>0){ //loops through programs the running job and how long its got left
			if(programs->front().getOnDisk()==0){
				cout <<"Running job " << programs->front().getName() << " has " << programs->front().getCpuReq() << " time left and is using "<< programs->front().getMemReq() << " memory resources." << endl;
			}else {
				cout <<"Running job " << programs->front().getName() << " has " << programs->front().getCpuReq() << " time left and is using "<< programs->front().getMemReq() << " resources on disk." << endl;
			}
		}else {
			cout << "Running Job is empty" << endl;
		}
			cout <<"The queue is: ";
			int counter = 1;
		if(!programs->empty()){ //loops once through the program
			programs->push(programs->front());
			programs->pop();
		}
		if(!programs->empty() &&(programs->size())>1){ //loops through the rest of the queued jobs displaying their position and remaining time
			cout << endl;
			while (counter < programs->size()) {
				if(programs->front().getOnDisk()==0){
					cout << "\tPosition " << counter << ": job " << programs->front().getName() << " has " << programs->front().getCpuReq() << " units left and is using "<< programs->front().getMemReq() << " memory resources." << endl;
				}else {
					cout << "\tPosition " << counter << ": job " << programs->front().getName() << " has " << programs->front().getCpuReq() << " units left and is using "<< programs->front().getMemReq() << " resources on disk." << endl;
				}
				programs->push(programs->front());
				programs->pop();
				counter++;
			}
		} else {
			cout << "empty" << endl;
		}
		
		
		if(!finished->empty()) { //loops through the finished jobs displaying their CPU req and how long they actually took
			cout << "Finished Jobs are: "<< endl;
			for (int j = 0; j < finished->size(); j++) {
				cout << "\t" << finished->front().getName() << " " << finished->front().getRunTime() << " " << finished->front().getFinTime() << " " << endl;
				finished->push(finished->front());
				finished->pop();
			}
			
		}
		
	}
	//adds a program to the running jobs if there is enough memory to support it
	void Simulator::addProg(Program p) {
		if(p.getMemReq()<=totalMem){
			if(p.getMemReq()>sysMem) {
				virtualize(p);
			} else {
				programs->push(p);
				sysMem = sysMem-p.getMemReq();
			}
		}else{
			cout <<"Program is to large to run on this system" << endl;
		}
	}
	
	void Simulator::virtualize(Program p) {
		int counter = 1;
		bool allocated = false;
		if(!programs->empty()){ //loops once through the program
			programs->push(programs->front());
			programs->pop();
		
			while (counter < programs->size()) {
				if(programs->front().getOnDisk() ==0 && allocated ==false){
					programs->front().setOnDisk(2);
					sysMem = sysMem+programs->front().getMemReq();
					if(p.getMemReq()<=sysMem) {
						allocated =true;
					}

				}
				programs->push(programs->front());
				programs->pop();
				counter++;
			}
		}
		if(allocated == false) {
			p.setOnDisk(2);
		}
		programs->push(p);
		sysMem = sysMem-p.getMemReq();
		return;
	}
	
	/*
	Purpose: to free memory when a program must go from the Queue to running and there is not enough memory for it
	Input: The program about to run
	Called by: step, run
	
	*/
	
	void Simulator::clearSpace(Program p) {
		int counter = 1;
		bool allocated = false;
		if(!programs->empty()){ //loops once through the program
			programs->push(programs->front());
			programs->pop();
		
			while (counter < programs->size()) {
				if(programs->front().getOnDisk() ==0 && allocated ==false){
					programs->front().setOnDisk(2);
					sysMem = sysMem+programs->front().getMemReq();
					if(p.getMemReq()<=sysMem) {
						allocated =true;
					}

				}
				programs->push(programs->front());
				programs->pop();
				counter++;
			}
		}
		//programs->push(p);
		sysMem = sysMem-p.getMemReq();
		return;
	}
	//getters/setters
	void Simulator::setSysMem(int s) {
		if(totalMem ==sysMem) {
			sysMem=s;
			totalMem=s;
		}else {
			sysMem = (s-totalMem) + sysMem;
			totalMem=s;
		}
		
		
	}
	
	int Simulator::getSysMem() {
		return sysMem;
	}
	