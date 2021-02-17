#include <stack>
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

	//primary constructor, called from main to create Text files and determine size
	UserInterface::UserInterface(stack<Directory> &d, DiskManager &dd) {
		directories = &d;
		make.setDiskManager(dd);
		dMan = &dd;
		menu();
	}
	
	
	//Processes all commands and calls the relevant function or class needed to complete them
	void UserInterface::menu() {
		//variable that will be used for all searchs
		string search;

		//variable that will be used to temporarily hold input data before putting it into the file
		string command;
		stack<Directory> list;
			//Intorduction to the Program
		cout << "Welcome to RUFS. Enter one of the following commands: "<< endl;
		cout << "CreateDir or CreateFile or EndDir or quit "<< endl;
	
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
			}else if (command == "cat") {
				cin >>search;
				search = make.namePadder(search);
				dMan->cat(directories->top().getMemLoc(), search);
					
					
			}else if (command == "run") {
				cin >>search;
				search = make.namePadder(search);
				dMan->run(directories->top().getMemLoc(), search);
			}else if (command == "start") {
				cin >>search;
				search = make.namePadder(search);
				dMan->start(directories->top().getMemLoc(), search);
			}else if (command == "cd") {
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
			}else if (command == "step") {
				cin >>search;
				search = make.namePadder(search);
				dMan->step(directories->top().getMemLoc(), search);
			}else if (command == "printinfo") {
				dMan->reader(directories->top().getMemLoc());
			}else {
				cout << "Invalid Command" << endl;
			}
		
			//Enter Commands
			cout << "Command: " ;
			cin >> command;
			//changes command to all lowercase
			transform(command.begin(), command.end(), command.begin(), ::tolower);
	
		}
		
	}
	
	
	