/*
Purpose - takes a single binary file as an input and creates a file system oon it starting at 0
	file names will have names of 8 characters, plus a one character . extension (ie .p) 
	and be terminated with a null character, directorieswill be inputed only as up to 8 character names
Output:A binary file holding all inputed files and directories along with their contents, will output this to the 
	terminal along with their memory locations
Input: either user input responding to text prompts or a textfile of format discussed in the readme
Basic Algorithm: creates file to write too
	creates root directory and adds to stack, writes root directory with 0 for num of included objects
	user can create files and directores, when either is created the current directory is edited in the stack and
	its number of included objects is increased
	creating a directory adds it to the stack and writes it to memory
	creating a file simply writes it to memory
	upon ending a directory the directory is removed from the stack and the memory location of its number of
	objects is found in the binary file, this number is then overwritten with the final number of objects  and the
	ENDdirName.d tag is written to the file with 14 characters instead of standard 11
	upon quitting the program all directories are ended by popping everything off the stack
	binary file is then read
Programmer: Luke Martin
*/
#include <stack>
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include "Text.h"
#include "Program.h"
#include "Directory.h"
#include "DiskManager.h"
#include "UserInterface.h"

using namespace std;

/*
Purpose: to create initial directory and file to write to as well as to manage the directory stack
	and call all necessary functions as determined by user input at the menu
Input: from cosole
Output: the command prompt
calls: fstream, namePadder, writeDirectoryF, writeEndDirectoryF, Directory, createDir, createFileName, reader
called by: console
return type: int
*/

int main(int argc, char** argv)
{
	if(argv[1] ==NULL) {
		argv[1] = "RUFS.txt";
	}
	//if file for argv already exists removes it so overwriting doesnt cause issues
	//remove ( argv[1] );
	
	DiskManager diskManager(argv[1]);
	
	int fin = diskManager.createFile();
	
	//Maker make();
	//variable that will be used to temporarily hold input data before putting it into the file
	//string command;
	
	stack<Directory> directories;
	// initializes the root directory and writes it to the binary file
	string rootDir = "root.d";
	while (rootDir.length() <11) {
		rootDir.insert(rootDir.length()-2, 1, '\0');
	}
	Directory root = Directory(rootDir, 0, 0);
	//diskManager.writeDirectoryF(root);
	directories.push(root);
	
	UserInterface(directories, diskManager);
	
	// ends all currently open directories
	//cout <<fin <<endl;
	if (fin == 1) {
		while(!directories.empty()) {
			Directory end = directories.top();
			//if (end.getName().substr(0,4) !="root") {
				diskManager.writeEndDirectoryF(end);
				directories.pop();
			//}else {
			//	break;
			//}
	
		}
	}

	//file.close();
	return 0;
}