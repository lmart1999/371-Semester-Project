/*Creates the UserInterface Object
Purpose: to create a UserInterface object controlling the menu and any user input fields such as file contents and names
Constructor requires the directory stack and the disk manager object
Output: none
Called by: RUFS.cpp UserInterface

*/
#ifndef USERINTERFACE
#define USERINTERFACE
#include <stack>
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include "Text.h"
#include "Program.h"
#include "Directory.h"
#include "Maker.h"
#include "DiskManager.h"
using namespace std;


class UserInterface {
	
	//variables
	private:
		Maker make;
		stack<Directory> *directories;
		DiskManager *dm;
		stack<Directory> list;

	
	public:
	
	//full constructor
	UserInterface(stack<Directory> &directories, DiskManager &dMan);
	//Processes all commands and calls the relevant function or class needed to complete them
	void menu();
	/*
	Purpose: obtains search parameter and either returns to previous directory or calls disk manager to search for a sub directory
	Input: user inputted directory name
	Output: none
	Calledby: menu
	calls: Directory, diskmanager, maker, directories
	*/
	void cd();
	/*
	Purpose: Print out the path of the current directory
	Input: none
	Output: full path of current directory
	Calledby: menu
	calls: Directory, directories, stack
	*/
	void pwd();
};

#endif
