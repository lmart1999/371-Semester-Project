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
		
		//variable that will be used to temporarily hold input data before putting it into the file
		string command;
		
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
			if (command == "createdir") {
				//calls the create directoy file to make a new properly named and formatted directory object to add to the stack
				Directory temp =make.createDirectory(); 
				//pulls top directory off, adds one to its num of programs and replaces it on the stack
				Directory mod = directories->top();
				mod.setNumObj(mod.getNumObj()+1);
				directories->pop();
				directories->push(mod);
				//adds new directory to the stack
				directories->push(temp);
				//Executes the CreateFile command
			}else if (command == "createfile") {
				make.createFileName(); //creates and writes a text or program file to the binary file
			
				//pulls top directory off, adds one to its num of programs and replaces it on the stack
				Directory mod = directories->top();
				mod.setNumObj(mod.getNumObj()+1);
				directories->pop();
				directories->push(mod);
			
			//Executes the EndDir Command
			}else if (command == "enddir") {
				Directory end = (directories->top());
				dMan->writeEndDirectoryF(end);
				directories->pop();
				//file.seekg(0,ios::end);
				if(directories->empty()) {
					break;
				}
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
	
	
	