/*Creates the DiskManager Object
Purpose: To manage the reading, writing and navigating of the binary file
Constructor requires name of file to be built
Output: the completed file
Called by: RUFS.cpp main

*/
#ifndef DISKMANAGER
#define DISKMANAGER
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include "Text.h"
#include "Program.h"
#include "Directory.h"


using namespace std;
class DiskManager {
	
	//variables
	private:
	char* name;
	fstream file;

	
	public:
	
	//full constructor
	DiskManager(char* s);
	
	DiskManager();

	/*
	Purpose: to initialize the file that will be used for all read write operations
	Called by the constructor
	*/
	int createFile();
	/*
	Purpose: checks the extension of the entered filename to determine the type of file to be read
	input: a filename	
	output: a int declaring the type of file
	calledby: reader
	*/
	int checkExtensionR(string fileName);
	
	/*
	Purpose: to write the most recently created text file to the binary file
	output: none
	input: text file, fstream pointer
	called by:createTextFile
	*/
	void writeTextF(Text input, int dirPos);
	/*
	Purpose: to write the most recently created Program file to the binary file
	output: none
	input: text file, fstream pointer
	calledby: createProgramFile
	*/
	void writeProgramF( Program input, int dirPos);
	
	/*
	Purpose: to copy everything after the insertion point
	Input: a position 
	output: the contents of the file after the position
	*/
	string copy(int dirPos);

	/*
	Purpose: to write the most recently created Program file to the binary file
	output: none
	input: text file, fstream pointer
	called by: main
	*/
	void writeEndDirectoryF(Directory input, int dirPos, int start);
	
	/*
	Purpose: to write the most recently created Program file to the binary file
	output: none
	input: text file, fstream pointer
	called by : createDirectory
	*/
	int writeDirectoryF(Directory input, int dirPos);
	/*
	Purpose: to read all input into the binary file thus far
	Input: an fstream pointer to the open file
	Output: the contents of the file to the console
	calls: checkExtensionR
	called by: main
	*/
	void reader(int curDir);
	//determines size of contents
	void findSize();
	/*
	Purpose: skip a file in memory
	Input: position of end of file name
	Called By: DiskManager.menu(), skipdir
	OutPut: none
	*/	
	void skipFile(int ext);
	/*
	Purpose: skip a Directory in memory
	Input: none
	Calls: skipFile, skip dir
	Called By: DiskManager.menu(), skipdir
	OutPut: none
	*/
	void skipDir();
	/*
	Purpose: to read the names of files or directories from the binary file and return the type
	input: none
	calls: checkextensionR
	outputs: int representing filetype
	*/
	int readName();
	/*
	Purpose:changes working directory to another directory in the current or to the parent directory
	Input: position of start of current directory and string of directory name to search for
	Calls: skipDir, skipFile
	Called By: DiskManager.menu()
	OutPut: A directory to make the new working directory
	
	*/
	Directory cd(int pos, string search);
	/*
	Purpose: List all files and directories in the current directory
	Input: position of start of current directory
	Calls: skipDir, skipFile
	Called By: DiskManager.menu()
	OutPut: List of all current files and directories in the current directory
	
	*/
	void ls(int pos);
	/*
	Purpose:opens a text file in the current directory and displays its contents
	Input: position of start of current directory and string of directory name to search for
	Calls: skipDir, skipFile
	Called By: DiskManager.menu()
	OutPut:contents of the text file
	*/
	void cat(int pos, string search);
	
	/*
	****
	Purpose:to search for a program file in the current directory determine if it exists
	Input: position of start of current directory and string of directory name to search for
	Calls: skipDir, skipFile
	Called By: start(), step(), run()
	OutPut:an int telling whether it exists or not
	int searchProg(int pos, string seatch);
	****
	*/
	
	/*Purpose: to check if the file or Directory being created already exists, if so returns true, if not returns false
	Input: a string to search for
	output: a boolean
	calls: skipfile, skipDirectory, checkExtensionR
	*/
	bool checkExists(string search, int dirPos);
	
	//place holder functions
	Program start(int pos, string seatch);

	//getters and setters
	void setName(char* n);
	char* getName();
	
};

#endif
