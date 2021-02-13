/*Creates the UserInterface Object
Purpose: to create a UserInterface object controlling the menu and any user input fields such as file contents and names
Constructor requires the directory stack and the disk manager object
Output: none
Called by: RUFS.cpp UserInterface

*/
#ifndef MAKER
#define MAKER
#include <stack>
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include "Text.h"
#include "Program.h"
#include "Directory.h"
#include "DiskManager.h"
using namespace std;


class Maker {
	
	//variables
	private:
	
	public:
	
	//full constructor
	Maker(DiskManager &d);
	
	Maker();
	
		/*
	Purpose: creates and normalizes a file Name and determines which filemaker to call
	input: User inputted file name
	output: none
	calls: checkExtension, checkString, namePadder, createProgramFile, createTextFile
	called by: main
	*/
	void createFileName(DiskManager &dm);
	/*
	Purpose: checks the extension of the entered filenames validity
	input: a filename
	output: a int declaring the type of file
	calledby: createDirName, createFileName
	*/
	int checkExtension(std::string fileName);
	/*
	Purpose: checks the character types of file names to ensure their validity
	input: a filename
	output: a boolean declaring whether the filename was valid
	called by: createFileName, createDirName
	*/
	bool checkString(std::string fileName);
	/*
	Input: a filename
	output: a padded filename to the proper lenght
	called by: createDirName, createFileName

	*/
	string namePadder(string name) ;
	/*
	Purpose: calls the Text class to create a text file and input the contents
	Input: a file name and user inputted contents
	Output: a Text object
	called by: createFileName
	calls: Text and writes the file to the binary file

	*/
	void createTextFile(string name, DiskManager &dm) ;
	/*
	Purpose: calls the Program class to create a program file and input the contents
	Input: a file name and user inputted contents
	Output: a Program object
	called by: createFileName
	calls: Program and writes the file to the binary file by calling writeProgramF

	*/
	void createProgramFile(string name, DiskManager &dm );

	/*
	*Purpose: to create and return a directory 
	* Calls createDirectoryName and Directory
	* is called by Main
	* Returns a Directory
	*/
	Directory createDirectory(DiskManager &dm);
	/*
	Purpose: to recieve user input for a directory name and call functions to normalize it
	input: n/a
	output: a directory name string
	calledby: createDirectory
	*/
	string createDirName();

};

#endif
