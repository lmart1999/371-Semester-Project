#include <iostream>
#include <fstream>
#include "DiskManager.h"
#include <bits/stdc++.h>
#include "Text.h"
#include "Program.h"
#include "Directory.h"
#include <string>
using namespace std;
	
	
	char* name;
	fstream file;
	
	//Full Constructor
	DiskManager::DiskManager(char* s) {
		name =s;

		//createFile();
		
	}
	//Full Constructor
	DiskManager::DiskManager() {
		//createFile();
		
	}
	int DiskManager::createFile() {
		int flag = 0;
		//fstream file;
		file.open(name, ios::binary | ios::out | ios::in | ios::app );
		file.close();
		//opens file to edit it
		file.open(name, ios::binary | ios::out | ios::in );
		//creates pointers to keep track of location in file system
		streampos begin,end,pos;
		//location of start of file
		begin=file.tellg();
		//tells location of end of file
		file.seekg(0,ios::end);
		end =file.tellg();
		//returns pointer to beggining
		file.seekg(0, ios::beg);
		if (end == begin) {
			flag = 1;
			// initializes the root directory and writes it to the binary file
			string rootDir = "root.d";
			while (rootDir.length() <11) {
				rootDir.insert(rootDir.length()-2, 1, '\0');
			}
			Directory root = Directory(rootDir, 0, 0);
			writeDirectoryF(root);
		}
		return flag;
	}
		
		
	/*
	Purpose: checks the extension of the entered filename to determine the type of file to be read
	input: a filename	
	output: a int declaring the type of file
	calledby: reader
	*/

	int DiskManager::checkExtensionR(std::string fileName) {
		
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
	Purpose: to write the most recently created text file to the binary file
	output: none
	input: text file, fstream pointer
	called by:createTextFile
	*/
	
	void DiskManager::writeTextF(Text input) {
		
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
	
	void DiskManager::writeProgramF( Program input) {
		
		
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
	called by: main
	*/


	
	void DiskManager::writeEndDirectoryF(Directory input) {
		
		
		
		string name = input.getName();
	
		int numObj = input.getNumObj(); //retrieves number of objects in directory to be ended
		int memLoc= input.getMemLoc(); // retrieves memory location of start of directory
		memLoc = memLoc+11; //udjust memeory location for location for number of OBJ
		file.seekg(memLoc, ios::beg ); // seeks to the memory location 
		file.write((char*)&numObj, sizeof(numObj));//writes number of Objecs to binary file
		file.seekg(0, ios::end); //seeks to end of file
		name = "END" + name; // adds END to beggining of Directory name
		file.write(name.c_str(), 14); // writes file name to binary
		file.seekg(0,ios::end);

		
		
	}
	
	/*
	Purpose: to write the most recently created Program file to the binary file
	output: none
	input: text file, fstream pointer
	called by : createDirectory
	*/
	
	int DiskManager::writeDirectoryF(Directory input) {
		
		
		int curLoc = file.tellg();
		input.setMemLoc(file.tellg());
		string name = input.getName();
		//cout << name<< endl;
		int numObj = input.getNumObj();
		//int memLoc= input.getMemLoc();
		file.write(name.c_str(), 11); // writes file name to binary
		file.write((char*)&numObj, sizeof(numObj)); //writes number of Objecs to binary file
		//file.write((char*)&memLoc, sizeof(memLoc)); //writes mem req to binary file
		
		return curLoc;
	
	}
	
	
	/*
	Purpose: to read all input into the binary file thus far
	Input: an fstream pointer to the open file
	Output: the contents of the file to the console
	calls: checkExtensionR
	called by: main
	*/
	
	
	void DiskManager::reader() {
		
		
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
	Purpose: skip a Directory in memory
	Input: none
	Calls: skipFile, skip dir
	Called By: DiskManager.menu(), skipdir
	OutPut: none
	*/
	void DiskManager::skipDir() {
		file.seekp(4,ios::cur);
		char stringChar;
		string fname = "";
		int fileType = 0;
		for (int j =0; j<11; j++){
			file.read((char*)&stringChar, sizeof(char));
			fname = fname + stringChar;
		}
		
		fileType = checkExtensionR(fname);
		if( fileType ==4) {
			for (int j =0; j<3; j++){
				file.read((char*)&stringChar, sizeof(char));
				fname = fname + stringChar;
				return;
			}
		}
		while (fileType != 4) {
			
			if(fileType ==1 ||fileType ==2){
				skipFile(fileType);
			}else if(fileType ==3) {
				skipDir();
			}
			for (int j =0; j<11; j++){
				file.read((char*)&stringChar, sizeof(char));
				fname = fname + stringChar;
			}
			fileType = checkExtensionR(fname);
			if( fileType ==4) {
				for (int j =0; j<3; j++){
					file.read((char*)&stringChar, sizeof(char));
					fname = fname + stringChar;
					return;
				}
			}
		}
	}
	/*
	Purpose: skip a file in memory
	Input: position of end of file name
	Called By: DiskManager.menu(), skipdir
	OutPut: none
	*/
	void DiskManager::skipFile(int ext) {
		if (ext ==1){
			int skip;
			file.read((char*)&skip, sizeof(skip));
			file.seekg(skip, ios::cur);
		}else {
			file.seekg(8, ios::cur);
		}
		
	}
	/*
	Purpose: List all files and directories in the current directory
	Input: position of start of current directory
	Calls: skipDir, skipFile
	Called By: DiskManager.menu()
	OutPut: List of all current files and directories in the current directory
	
	*/
	void DiskManager::ls(int pos) {
		 file.seekg(pos+15, ios::beg);
		 //int numO;
		 int fileType = 0;
		 string fname;
		 //file.read((char*)&numO, sizeof(numO));
		 while(fileType !=4) {
			 
			 char stringChar;
			string fname = "";
		
			for (int j =0; j<11; j++){
				file.read((char*)&stringChar, sizeof(char));
				fname = fname + stringChar;
			}
		
		
			fileType = checkExtensionR(fname);
		
			if( fileType ==4) {
				for (int j =0; j<3; j++){
					file.read((char*)&stringChar, sizeof(char));
					fname = fname + stringChar;
					return;
				}
			}
			
			if (fileType ==1 || fileType ==2) {
				cout << fname << endl;
				skipFile(fileType);
			}else if (fileType ==3) {
				cout <<fname <<endl;
				skipDir();
			}
			
			
		}
		return;
		 
	}
	Directory DiskManager::cd(int pos, string search) {
		Directory change("null",0,0);
		 file.seekg(pos+15, ios::beg);
		 int numO;
		 int newPos;
		 int fileType = 0;
		 string fname;
		 //file.read((char*)&numO, sizeof(numO));
		 while(fileType !=4) {
			 
			 char stringChar;
			string fname = "";
		
			for (int j =0; j<11; j++){
				file.read((char*)&stringChar, sizeof(char));
				fname = fname + stringChar;
			}
			
		
			fileType = checkExtensionR(fname);
		
			if( fileType ==4) {
				for (int j =0; j<3; j++){
					file.read((char*)&stringChar, sizeof(char));
					fname = fname + stringChar;
					cout << "Directory " << search << " not found\n"; 
					return change;
				}
			}
			
			if (fileType ==1 || fileType ==2) {
				//cout << fname << endl;
				skipFile(fileType);
			}else if (fileType ==3) {
				if (search ==fname) {
					cout <<fname <<endl;
					file.read((char*)&numO, sizeof(numO));
					newPos = file.tellg()-15;
					change.setName(fname);
					change.setNumObj(numO);
					change.setMemLoc(newPos);
					//change(fname, numO, newPos);
					return change;
				}else {
					skipDir();
				}
			}
			
			
		}
		return change;
		 
	}
	
	
	// Getters and setters
	void DiskManager::setName(char* n) {
		name = n;
	}
	
	char* DiskManager::getName() {
		return name;
	}
	
	
