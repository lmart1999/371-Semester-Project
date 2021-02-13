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

	
	public:
	
	//full constructor
	UserInterface(stack<Directory> &directories, DiskManager &dMan);
	//Processes all commands and calls the relevant function or class needed to complete them
	void menu();

};

#endif
