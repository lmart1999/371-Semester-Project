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
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include "Text.h"
#include "Program.h"
#include "Directory.h"

using namespace std;

/*
Purpose: to write the most recently created text file to the binary file
output: none
input: text file, fstream pointer
called by:createTextFile
*/

void writeTextF(fstream& file, Text input) {
	string name = input.getName(); //saves file name as a string
	string contents = input.getContents(); // saves file contents
	int size= input.getSize(); // gets size of contents
	file.write(name.c_str(), 11); // writes file name to binay file
	file.write((char*)&size, sizeof(size)); // writes content size to binary file
	file.write(contents.c_str(), size); // writes content to binary file
}
/*
Purpose: to write the most recently created Program file to the binary file
output: none
input: text file, fstream pointer
calledby: createProgramFile

*/

void writeProgramF(fstream& file, Program input) {
	string name = input.getName();
	//cout << name<< endl;
	int cpuReq = input.getCpuReq();
	int memReq= input.getMemReq();
	file.write(name.c_str(), 11); // writes file name to binary
	file.write((char*)&cpuReq, sizeof(cpuReq)); //writes cpuReq to binayr file
	file.write((char*)&memReq, sizeof(memReq)); //writes mem req to binary file
	
}

/*
Purpose: to write the most recently created Program file to the binary file
output: none
input: text file, fstream pointer
called by : createDirectory

*/

void writeDirectoryF(fstream& file, Directory input) {
	string name = input.getName();
	//cout << name<< endl;
	int numObj = input.getNumObj();
	//int memLoc= input.getMemLoc();
	file.write(name.c_str(), 11); // writes file name to binary
	file.write((char*)&numObj, sizeof(numObj)); //writes number of Objecs to binary file
	//file.write((char*)&memLoc, sizeof(memLoc)); //writes mem req to binary file
	
}

/*
Purpose: to write the most recently created Program file to the binary file
output: none
input: text file, fstream pointer
called by: main
*/

void writeEndDirectoryF(fstream& file, Directory input) {
	string name = input.getName();
	
	int numObj = input.getNumObj(); //retrieves number of objects in directory to be ended
	int memLoc= input.getMemLoc(); // retrieves memory location of start of directory
	memLoc = memLoc+11; //udjust memeory location for location for number of OBJ
	file.seekg(memLoc, ios::beg ); // seeks to the memory location 
	file.write((char*)&numObj, sizeof(numObj));//writes number of Objecs to binary file
	file.seekg(0, ios::end); //seeks to end of file
	name = "END" + name; // adds END to beggining of Directory name
	file.write(name.c_str(), 14); // writes file name to binary
	
	
}


/*
Purpose: calls the Text class to create a text file and input the contents
Input: a file name and user inputted contents
Output: a Text object
called by: createFileName
calls: Text and writes the file to the binary file

*/
void createTextFile(string fileName, fstream& file) {
	string contents;
	cout << "Enter Text: ";
	cin.ignore();
	getline(cin, contents);
	Text text(fileName, contents);
	writeTextF(file, text);
	return;
}
/*
Purpose: calls the Program class to create a program file and input the contents
Input: a file name and user inputted contents
Output: a Program object
called by: createFileName
calls: Program and writes the file to the binary file by calling writeProgramF

*/
void createProgramFile(string fileName, fstream &file ) {
	int cpuReq;
	cout << "Enter CPU requirements: ";
	cin >> cpuReq;
	int memReq;
	cout << "Enter Memory Requirements: ";
	cin >> memReq;
	Program program(fileName, cpuReq, memReq);
	writeProgramF(file, program);
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
void createFileName(fstream &file) {
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
		createTextFile(fileName, file);
	}else if (fileType==2) {
		createProgramFile(fileName, file);
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

Directory createDirectory(int curLoc, fstream & file) {
	string dirName =createDirName();
	Directory temp = Directory(dirName, 0, file.tellg());
	writeDirectoryF(file, temp);
	return temp;	
}

/*
Purpose: checks the extension of the entered filename to determine the type of file to be read
input: a filename
output: a int declaring the type of file
calledby: reader
*/


int checkExtensionR(std::string fileName) {
	// retrieves the files extenstionclea
	string extension = fileName.substr(((fileName.length())-2), 2);
	
	if(extension ==".t") {
		return 1;
	}else if (extension==".p") {
		return 2;
	}else if (extension==".d") {
		return 3;
	}else {
		return 4;
	}
}


/*
Purpose: to read all input into the binary file thus far
Input: an fstream pointer to the open file
Output: the contents of the file to the console
calls: checkExtensionR
called by: main
*/
void reader(fstream &file) {
	file.seekg(0, ios::beg);
	int numO = 0;
	
	cout <<"\n";
	while(!file.eof()){
		cout<< file.tellg() << ": " ;
	
		char stringChar;
        string name = "";
		
        for (int j =0; j<11; j++){
            file.read((char*)&stringChar, sizeof(char));
            name = name + stringChar;
        }
		
		
		int fileType = checkExtensionR(name);
		
		if( fileType ==4) {
			for (int j =0; j<3; j++){
				file.read((char*)&stringChar, sizeof(char));
				name = name + stringChar;
			}
		}
		
		
		if(fileType ==1) {
			cout << "	"<< name << endl;
			cout << "	Type:	Text" << endl;
			cout<< file.tellg() ; //tells current memlocation
			int size = 0; // to store size of text file contents

			file.read((char*)&size, sizeof(size)); // reads in size of text file contents
			cout << ": Size of Text File:	" <<size << " byte"<< endl;  //tells size
			string contents = ""; //holder string
			cout<< file.tellg() << ": " ;

			//for loop that reads in the contents of the text file
			for (int j =0; j<size; j++){
				file.read((char*)&stringChar, sizeof(char));
				contents = contents + stringChar;
			}
		cout << "Contents of text file:	"<< contents <<  endl;
	
		
		}else if(fileType ==2) {
			cout << "	Filename:"<< name << endl;
			int cReq = 0;
			int mReq = 0;
			cout << "	Type: Program" << endl;
			cout<< file.tellg() << ": " ; //tells current memory location
			file.read((char*)&cReq, sizeof(cReq)); // reads in CPU req of text file contents
			file.read((char*)&mReq, sizeof(mReq)); // reads in memory req of text file contents
			cout << " Contents: CPU Requirement:\t " << cReq << ", Memory Requirement " << mReq << endl; // prints out data of file
		
		}else if(fileType ==3) {
			cout << "Directory:"<< name << endl;
			int numO = 0;
			//cout << "	Type: Directory" << endl;
			cout<< file.tellg() << ": " ; //tells current memory location
			file.read((char*)&numO, sizeof(numO)); // reads in number of Objects of text file contents
			cout << "Directory " << name << " contains " << numO << " file/directory" << endl; // prints out data of Directory
		
		}else {
		    cout<< "End of Directory " << name.substr(3,11) << endl;
			//ends if final directory is ended
			char test;
			file.read((char*)&test, sizeof(test));			
			if (file.eof()) {
				return;
			}else{
				file.seekg(-1, ios::cur);
			}
			
		}
		
	}
	
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
	fstream file;
	if(argv[1] ==NULL) {
		argv[1] = "RUFS.txt";
	}
	//if file for argv already exists removes it so overwriting doesnt cause issues
	remove ( argv[1] );
	//opens and closes the binary file, allows us to overrwrite just first entries of file rather than whole file/ creates file if not existent
    file.open(argv[1], ios::binary | ios::out | ios::in | ios::app );
    file.close();
	//opens file to edit it
	file.open(argv[1], ios::binary | ios::out | ios::in );
	//creates pointers to keep track of location in file system
	streampos begin,end,pos;
	//location of start of file
    begin=file.tellg();
	//tells location of end of file
    file.seekg(0,ios::end);
    end =file.tellg();
	//returns pointer to beggining
    file.seekg(0, ios::beg);
	//variable that will be used to temporarily hold input data before putting it into the file
	string command;
	
	stack<Directory> directories;
	// initializes the root directory and writes it to the binary file
	string rootDir = namePadder("root.d");
	Directory root = Directory(rootDir, 0, 0);
	writeDirectoryF(file, root);
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
			Directory temp =createDirectory(file.tellg(), file);
			//pulls top directory off, adds one to its num of programs and replaces it on the stack
			Directory mod = directories.top();
			mod.setNumObj(mod.getNumObj()+1);
			directories.pop();
			directories.push(mod);
			//adds new directory to the stack
			directories.push(temp);
			//Executes the CreateFile command
		}else if (command == "createfile") {
			createFileName(file); //creates and writes a text or program file to the binary file
			
			//pulls top directory off, adds one to its num of programs and replaces it on the stack
			Directory mod = directories.top();
			mod.setNumObj(mod.getNumObj()+1);
			directories.pop();
			directories.push(mod);
			
			//Executes the EndDir Command
		}else if (command == "enddir") {
			Directory end = directories.top();
			writeEndDirectoryF(file, end);
			directories.pop();
			file.seekg(0,ios::end);
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
		writeEndDirectoryF(file, end);
		directories.pop();
		file.seekg(0,ios::end);
	
	}
	
	reader(file);

	file.close();
	return 0;
}
