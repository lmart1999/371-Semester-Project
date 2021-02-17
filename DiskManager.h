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
	Purpose: to write the most recently created Program file to the binary file
	output: none
	input: text file, fstream pointer
	called by: main
	*/
	void writeEndDirectoryF(Directory input, int dirPos);
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
	void skipFile(int ext);
	void skipDir();
	int readName();
	Directory cd(int pos, string search);
	void ls(int pos);
	
	//getters and setters
	void setName(char* n);
	char* getName();
	
};

#endif
