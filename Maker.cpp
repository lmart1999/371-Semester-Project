#include <stack>
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include "Text.h"
#include "Program.h"
#include "Directory.h"
#include "DiskManager.h"
#include "Maker.h"
using namespace std;

	//primary constructor, called from main to create Text files and determine size
	
	Maker::Maker() {
	}
	
	
	
	/*
	Purpose: creates and normalizes a file Name and determines which filemaker to call
	input: User inputted file name
	output: none
	calls: checkExtension, checkString, namePadder, createProgramFile, createTextFile
	called by: main
	*/
	void Maker::createFileName(DiskManager &dm) {
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
	Purpose: checks the extension of the entered filenames validity
	input: a filename
	output: a int declaring the type of file
	calledby: createDirName, createFileName
	*/

	int Maker::checkExtension(std::string fileName) {
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
	Purpose: checks the character types of file names to ensure their validity
	input: a filename
	output: a boolean declaring whether the filename was valid
	called by: createFileName, createDirName
	*/

	bool Maker::checkString(std::string fileName) {
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
	Input: a filename
	output: a padded filename to the proper lenght
	called by: createDirName, createFileName

	*/

	string Maker::namePadder(string name) {
		//pads shorter Directory with null characters before the extension
		while (name.length() <11) {
		name.insert(name.length()-2, 1, '\0');
		}
		return name;
	}

	/*
	Purpose: calls the Text class to create a text file and input the contents
	Input: a file name and user inputted contents
	Output: a Text object
	called by: createFileName
	calls: Text and writes the file to the binary file

	*/
	void Maker::createTextFile(string name, DiskManager &dm) {
		string contents;
		cout << "Enter Text: ";
		cin.ignore();
		getline(cin, contents);
		
		Text text(name, contents);
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
	void Maker::createProgramFile(string name, DiskManager &dm) {
		int cpuReq;
		int memReq;
		cout << "Enter CPU requirements: ";
		cin >> cpuReq;
		cout << "Enter Memory Requirements: ";
		cin >> memReq;
		Program prog(name, cpuReq,memReq);
		dm.writeProgramF(prog);
		return;
	}

	/*
	Purpose: to recieve user input for a directory name and call functions to normalize it
	input: n/a
	output: a directory name string
	calledby: createDirectory
	*/
	string Maker::createDirName() {
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

	Directory Maker::createDirectory(DiskManager &dm) {
		string dirName =createDirName();
		Directory temp = Directory(dirName, 0, 0);
		int curLoc = dm.writeDirectoryF(temp);
		temp.setMemLoc(curLoc);
		return temp;	
	}