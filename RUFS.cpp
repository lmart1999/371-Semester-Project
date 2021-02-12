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

using namespace std;




/*
Purpose: calls the Text class to create a text file and input the contents
Input: a file name and user inputted contents
Output: a Text object
called by: createFileName
calls: Text and writes the file to the binary file

*/
void createTextFile(string fileName, DiskManager& dm) {
	string contents;
	cout << "Enter Text: ";
	cin.ignore();
	getline(cin, contents);
	Text text(fileName, contents);
	dm.writeTextF(text);
	return;
}
/*
Purpose: calls the Program class to create a program file and input the contents
Input: a file name and user inputted contents
Output: a Program object
called by: createFileName
calls: Program and writes the file to the binary file by calling writeProgramF

*/
void createProgramFile(string fileName, DiskManager &dm ) {
	int cpuReq;
	cout << "Enter CPU requirements: ";
	cin >> cpuReq;
	int memReq;
	cout << "Enter Memory Requirements: ";
	cin >> memReq;
	Program program(fileName, cpuReq, memReq);
	dm.writeProgramF(program);
	return;
}

/*
Input: a filename
output: a padded filename to the proper lenght
called by: createDirName, createFileName

*/

string namePadder(string name) {
	//pads shorter Directory with null characters before the extension
	while (name.length() <11) {
	name.insert(name.length()-2, 1, '\0');
	}
	return name;
}


/*
Purpose: checks the character types of file names to ensure their validity
input: a filename
output: a boolean declaring whether the filename was valid
called by: createFileName, createDirName
*/

bool checkString(std::string fileName) {
	char * name = new char[fileName.length()-1];
	fileName = fileName.substr(0,fileName.length()-2);
	std::strcpy (name, fileName.c_str());
	for (int i=0; i<fileName.length(); i++) {
		if((name[i] >= 'a' && name[i] <= 'z') || (name[i] >='A' && name[i] <='Z') || (name[i] >='0' && name[i]<='9') || name[i] =='\0') {
			//cout <<name[i] << endl;
			continue;
		}else{
			//cout <<name[i] << " This broke it" << endl;
			return false;
		}
	}
	return true;
}


/*
Purpose: checks the extension of the entered filenames validity
input: a filename
output: a int declaring the type of file
calledby: createDirName, createFileName
*/

int checkExtension(std::string fileName) {
	// retrieves the files extenstionclea
	string extension = fileName.substr(((fileName.length())-2), 2);
	
	if(extension ==".t") {
		return 1;
	}else if (extension==".p") {
		return 2;
	}else {
		return 3;
	}
}

/*
Purpose: creates and normalizes a file Name and determines which filemaker to call
input: User inputted file name
output: none
calls: checkExtension, checkString, namePadder, createProgramFile, createTextFile
called by: main
*/
void createFileName(DiskManager &dm) {
	cout <<"Enter File Name: ";
	std::string fileName;
	cin >> fileName;
	
	//to keep track of extension and name character type validity
	bool validExtension = false;
	bool validChars = false;
	int fileType;
	//check to see if filename is within length requirements
	while (fileName.length() >10 || validExtension == false || validChars == false) {
		
		//forces user to choose a filename within the acceptable length
		if(fileName.length()>10) {
			cout <<"Invalid file name, File names should be no more than 8 characters with a one character . extension" << endl;
			cout <<"Enter File Name: ";
			cin >>fileName;
			validExtension = false;		
		}
		
		
			//ensures it is a valid extension and sets the file type to be created, otherwise forces you to try again
		if (validExtension != true) {
			fileType = checkExtension(fileName);
			if(fileType ==3) {
				cout <<"Invalid Extension: Acceptable Extensions are .t and .p" << endl;
				cout <<"Enter File Name: ";
				cin >>fileName;
			}else {
				validExtension = true;
			}
		}
		//calls function to check if only letters and numbers are included in the file name
		validChars = checkString(fileName);
		//if the function says other things are in the name forces user to choose a new name
		if(!validChars) {
			cout <<"Invalid Character Types: Only Numbers and Letters are allowed in the Name" << endl;
			cout <<"Enter File Name: ";
			cin >>fileName;
			validExtension= false;
		}
			

		
	}
		
	//pads shorter filenames with null characters before the extension
	fileName =namePadder(fileName);
	if(fileType==1) {
		createTextFile(fileName, dm);
	}else if (fileType==2) {
		createProgramFile(fileName, dm);
	}
	
	return;
}

/*
Purpose: creates and normalizes a Directory Name and adds the proper extensions
input: User inputted file name
output: returns the normalized directory name
called by:createDirectory
calls: checkString, namePadder

*/
string createDirName() {
	cout <<"Enter Directory Name: ";
	std::string dirName; //holds the inputted directory name
	cin >> dirName;
	dirName += ".d";
	//to keep track of extension and name character type validity
	bool validChars = false;
	//check to see if dirName is within length requirements
	while (dirName.length() >10  || validChars == false) {
		
		//forces user to choose a Directory within the acceptable length
		if(dirName.length()>10) {
			cout <<"Invalid Directory name, Directory names should be no more than 8 characters with no extension" << endl;
			cout <<"Enter Directory Name: ";
			cin >>dirName;
			dirName += ".d";

		}
		
		//calls function to check if only letters and numbers are included in the file name
		validChars = checkString(dirName);
		//if the function says other things are in the name forces user to choose a new name
		if(!validChars) {
			cout <<"Invalid Character Types: Only Numbers and Letters are allowed in the Name" << endl;
			cout <<"Enter Directory Name: ";
			cin >>dirName;
			dirName += ".d";
		}
	}
		
	//pads shorter Directory with null characters before the extension
	dirName = namePadder(dirName);
	
	return dirName;
}
/*
*Purpose: to create and return a directory 
* Calls createDirectoryName and Directory
* is called by Main
* Returns a Directory
*/

Directory createDirectory( DiskManager &dm) {
	string dirName =createDirName();
	Directory temp = Directory(dirName, 0, 0);
	int curLoc = dm.writeDirectoryF(temp);
	temp.setMemLoc(curLoc);
	return temp;	
}




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
	remove ( argv[1] );
	
	DiskManager diskManager(argv[1]);
	
	
	
	
	//variable that will be used to temporarily hold input data before putting it into the file
	string command;
	
	stack<Directory> directories;
	// initializes the root directory and writes it to the binary file
	string rootDir = namePadder("root.d");
	Directory root = Directory(rootDir, 0, 0);
	diskManager.writeDirectoryF(root);
	directories.push(root);
	
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
			Directory temp =createDirectory( diskManager); 
			//pulls top directory off, adds one to its num of programs and replaces it on the stack
			Directory mod = directories.top();
			mod.setNumObj(mod.getNumObj()+1);
			directories.pop();
			directories.push(mod);
			//adds new directory to the stack
			directories.push(temp);
			//Executes the CreateFile command
		}else if (command == "createfile") {
			createFileName(diskManager); //creates and writes a text or program file to the binary file
			
			//pulls top directory off, adds one to its num of programs and replaces it on the stack
			Directory mod = directories.top();
			mod.setNumObj(mod.getNumObj()+1);
			directories.pop();
			directories.push(mod);
			
			//Executes the EndDir Command
		}else if (command == "enddir") {
			Directory end = directories.top();
			diskManager.writeEndDirectoryF(end);
			directories.pop();
			//file.seekg(0,ios::end);
			if(directories.empty()) {
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
// ends all currently open directories
	while(!directories.empty()) {
		Directory end = directories.top();
		diskManager.writeEndDirectoryF(end);
		directories.pop();
	
	}
	
	diskManager.reader();

	//file.close();
	return 0;
}
