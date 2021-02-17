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
			writeDirectoryF(root, 0);
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
	
	void DiskManager::writeTextF(Text input, int dirPos) {
		
		int toRead;
		file.seekg(0,ios::end);
		//cout <<file.tellg();
		toRead = file.tellg()-(dirPos+15);
		char stringChar;
		string fileC = "";
		file.seekg(dirPos+15,ios::beg);
		for (int j =0; j<toRead; j++){
			file.read((char*)&stringChar, sizeof(char));
			fileC = fileC + stringChar;
		}
		file.seekg((dirPos+11), ios::beg);
		//updates objects in directory
		int newO;
		file.read((char*)&newO, sizeof(int));
		newO++;
		file.seekg(-4,ios::cur);
		file.write((char*)&newO, sizeof(newO));
		
		string name = input.getName(); //saves file name as a string
		string contents = input.getContents(); // saves file contents
		int size= input.getSize(); // gets size of contents
		file.write(name.c_str(), 11); // writes file name to binay file
		file.write((char*)&size, sizeof(size)); // writes content size to binary file
		file.write(contents.c_str(), size); // writes content to binary file
		file.write(fileC.c_str(), fileC.length());

		
	}
	
	
	
	/*
	Purpose: to write the most recently created Program file to the binary file
	output: none
	input: text file, fstream pointer
	calledby: createProgramFile
	*/
	
	void DiskManager::writeProgramF( Program input, int dirPos) {
		int toRead;
		file.seekg(0,ios::end);
		//cout <<file.tellg();
		toRead = file.tellg()-(dirPos+15);
		char stringChar;
		string fileC = "";
		file.seekg(dirPos+15,ios::beg);
		for (int j =0; j<toRead; j++){
			file.read((char*)&stringChar, sizeof(char));
			fileC = fileC + stringChar;
		}
		file.seekg((dirPos+11), ios::beg);

		//updates objects in directory
		int newO;
		file.read((char*)&newO, sizeof(int));
		newO++;
		file.seekg(-4,ios::cur);
		file.write((char*)&newO, sizeof(newO));
		
		string name = input.getName();
		//cout << name<< endl;
		int cpuReq = input.getCpuReq();
		int memReq= input.getMemReq();
		file.write(name.c_str(), 11); // writes file name to binary
		file.write((char*)&cpuReq, sizeof(cpuReq)); //writes cpuReq to binayr file
		file.write((char*)&memReq, sizeof(memReq)); //writes mem req to binary file
		file.write(fileC.c_str(), fileC.length());
	}
	
	/*
	Purpose: to write the most recently created Program file to the binary file
	output: none
	input: text file, fstream pointer
	called by: main
	*/


	
	void DiskManager::writeEndDirectoryF(Directory input, int dirPos) {
		string test = "root.d";
		string fileC = "";
		while (test.length() <11) {
			test.insert(test.length()-2, 1, '\0');
		}
		if(input.getName() != test) {
		
			int toRead;
			file.seekg(0,ios::end);
			//cout <<file.tellg() << "\n" << dirPos<< endl;
			toRead = file.tellg()-(dirPos+15);
			char stringChar;
			file.seekg(dirPos+15,ios::beg);
			for (int j =0; j<toRead; j++){
				file.read((char*)&stringChar, sizeof(char));
				fileC = fileC + stringChar;
			}
		
			file.seekg((dirPos+15), ios::beg);
		}
		
		
		string name = input.getName();
	
		//int numObj = input.getNumObj(); //retrieves number of objects in directory to be ended
		int memLoc= input.getMemLoc(); // retrieves memory location of start of directory
		//memLoc = memLoc+11; //adjust memeory location for location for number of OBJ
		//file.seekg(memLoc, ios::beg ); // seeks to the memory location 
		//file.write((char*)&numObj, sizeof(numObj));//writes number of Objecs to binary file
		file.seekg((dirPos+15), ios::beg); //seeks to end of file
		name = "END" + name; // adds END to beggining of Directory name
		file.write(name.c_str(), 14); // writes file name to binary
		//file.seekg(0,ios::end);
		if(input.getName() != test) {
			file.write(fileC.c_str(), fileC.length());
		}
		
		
	}
	
	/*
	Purpose: to write the most recently created Directory to the binary file
	output: none
	input: text file, fstream pointer
	called by : createDirectory
	*/
	
	int DiskManager::writeDirectoryF(Directory input, int dirPos) {
		string test = "root.d";
		string fileC = "";
		while (test.length() <11) {
			test.insert(test.length()-2, 1, '\0');
		}
		if(input.getName() != test) {
		
		
			int toRead;
			file.seekg(0,ios::end);
			//cout <<file.tellg() << "\n" << dirPos<< endl;
			toRead = file.tellg()-(dirPos+15);
			char stringChar;
			file.seekg(dirPos+15,ios::beg);
			for (int j =0; j<toRead; j++){
				file.read((char*)&stringChar, sizeof(char));
				fileC = fileC + stringChar;
			}
		
			file.seekg((dirPos+11), ios::beg);
			//updates objects in directory
			int newO;
			file.read((char*)&newO, sizeof(int));
			newO++;
			file.seekg(-4,ios::cur);
			file.write((char*)&newO, sizeof(newO));
		}
		
		int curLoc = file.tellg();
		input.setMemLoc(file.tellg());
		string name = input.getName();
		//cout << name<< endl;
		int numObj = input.getNumObj();
		//int memLoc= input.getMemLoc();
		file.write(name.c_str(), 11); // writes file name to binary
		file.write((char*)&numObj, sizeof(numObj)); //writes number of Objecs to binary file
		if(input.getName() != test) {

			file.write(fileC.c_str(), fileC.length());
		}
		
		writeEndDirectoryF(input, curLoc);
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
	
	
	void DiskManager::reader(int curDir) {
		
		
		file.seekg(0, ios::beg);
		int numO = 0;
	
		cout <<"\n";
		while(!file.eof()){
			cout<< file.tellg() << ": " ;
	
			char stringChar;
			string fname = "";
		
			for (int j =0; j<11; j++){
				file.read((char*)&stringChar, sizeof(char));
				fname = fname + stringChar;
			}
		
		
			int fileType = checkExtensionR(fname);
		
			if( fileType ==4) {
				for (int j =0; j<3; j++){
					file.read((char*)&stringChar, sizeof(char));
					fname = fname + stringChar;
				}
			}
		
		
			if(fileType ==1) {
				cout << "	"<< fname << endl;
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
				cout << "	Filename:"<< fname << endl;
				int cReq = 0;
				int mReq = 0;
				cout << "	Type: Program" << endl;
				cout<< file.tellg() << ": " ; //tells current memory location
				file.read((char*)&cReq, sizeof(cReq)); // reads in CPU req of text file contents
				file.read((char*)&mReq, sizeof(mReq)); // reads in memory req of text file contents
				cout << " Contents: CPU Requirement:\t " << cReq << ", Memory Requirement " << mReq << endl; // prints out data of file
		
			}else if(fileType ==3) {
				cout << "Directory:"<< fname << endl;
				int numO = 0;
				//cout << "	Type: Directory" << endl;
				cout<< file.tellg() << ": " ; //tells current memory location
				file.read((char*)&numO, sizeof(numO)); // reads in number of Objects of text file contents
				cout << "Directory " << fname << " contains " << numO << " file/directory" << endl; // prints out data of Directory
		
			}else {
				cout<< "End of Directory " << fname.substr(3,11) << endl;
				//ends if final directory is ended
				//char test;
				//file.read((char*)&test, sizeof(test));			
				//if (file.eof()) {
				if (fname.substr(3,4)=="root") {
					file.seekg(curDir,ios::beg);
					return;
				}/*else{
					file.seekg(-1, ios::cur);
				}*/
			
			}
		
		}
		file.seekg(0, ios::beg);

	}
	
	int DiskManager::readName() {
		char stringChar;
		string fname = "";
		//stores int representing filetype
		int fileType = 0;
		//reads in the next name in the file
		for (int j =0; j<11; j++){
			file.read((char*)&stringChar, sizeof(char));
			fname = fname + stringChar;
		}
		//checks that names file type
		fileType = checkExtensionR(fname);
		//if its the end of the directory reads rest of it then returns to original function
		if( fileType ==4) {
			for (int j =0; j<3; j++){
				file.read((char*)&stringChar, sizeof(char));
				fname = fname + stringChar;
				
			}
			return fileType;
		}
		return fileType;
	}
	
	
	/*
	Purpose: skip a Directory in memory
	Input: none
	Calls: skipFile, skip dir
	Called By: DiskManager.menu(), skipdir
	OutPut: none
	*/
	void DiskManager::skipDir() {
		//seeks to the end of the directory name just read in
		file.seekp(4,ios::cur);
		//variables for storing names read in
		char stringChar;
		string fname = "";
		//stores int representing filetype
		int fileType = 0;
		
		//checks that names file type
		fileType = readName();
		//if its the end of the directory reads rest of it then returns to original function
		if( fileType ==4) {
			return;

		}
		//reads and skips files and subdirectories until it reaches the end of the current directory
		while (fileType != 4) {
			//call skipFile if its a text or program filel next
			if(fileType ==1 ||fileType ==2){
				skipFile(fileType);
				//calls skip Dir if there is a sub directory
			}else if(fileType ==3) {
				skipDir();
			}
			
			
			//reads in next file and returns type of extension
			fileType = readName();
			//if end of Dir finishes reading and returns it
			if( fileType ==4) {
				return;
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
		//if input file is type text, reads size and skips that many bytes
		if (ext ==1){
			int skip;
			file.read((char*)&skip, sizeof(skip));
			file.seekg(skip, ios::cur);
			//of input file is type program skips 8 bytes, the size of 2 ints
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
		//seeks to end of current directory
		 file.seekg(pos+15, ios::beg);
		 //file.seekg(0,ios::end);
		 //cout <<file.tellg() <<endl;

		 //int to store fileTyoe;
		 int fileType = 0;
		 //stores File name
		 string fname;
		 //file.read((char*)&numO, sizeof(numO));
		 //while it hasnt reached the end of the current directory read in the name of the files in it and print them, skipping contents of sub directories and files
		 while(fileType !=4) {
			 //stores characters read in and initializes fname
			 char stringChar;
			 fname = "";
			// reads in first file name
			for (int j =0; j<11; j++){
				file.read((char*)&stringChar, sizeof(char));
				fname = fname + stringChar;
			}
		
			// checks extension
			fileType = checkExtensionR(fname);
			// if its the ned of the directory finishes reading it and returns function
			if( fileType ==4) {
				for (int j =0; j<3; j++){
					file.read((char*)&stringChar, sizeof(char));
					fname = fname + stringChar;
					
				}
				return;
			}
			//if its a program or text file prints its name then skips its contents and continues
			if (fileType ==1 || fileType ==2) {
				cout << fname << endl;
				skipFile(fileType);
				//if its a directory prints its name then skips its contents
			}else if (fileType ==3) {
				cout <<fname <<endl;
				skipDir();
			}
			
			
		}
		return;
		 
	}
	/*
	Purpose:changes working directory to another directory in the current or to the parent directory
	Input: position of start of current directory and string of directory name to search for
	Calls: skipDir, skipFile
	Called By: DiskManager.menu()
	OutPut: A directory to make the new working directory
	
	*/
	Directory DiskManager::cd(int pos, string search) {
		//placeholder for the directory that will become the new working directory, if none is found this is returned and nothing happens
		Directory change("null",0,0);
		//seeks to end of current directory
		 file.seekg(pos+15, ios::beg);
		 //stores number of objects in new directory
		 int numO;
		 //stores position of new directory
		 int newPos;
		 //stores filetype being read in
		 int fileType = 0;
		 //stores file name being read
		 string fname;
		 //file.read((char*)&numO, sizeof(numO));
		 //reads contents of current directory until the end of the directory or until the target is found, skips contents of sub directories
		 while(fileType !=4) {
			 //holds characters read in and initializes fname
			 char stringChar;
			fname = "";
			//reads in first file name
			for (int j =0; j<11; j++){
				file.read((char*)&stringChar, sizeof(char));
				fname = fname + stringChar;
			}
			
			//checks Extension
			fileType = checkExtensionR(fname);
			//if end of Directorysays that the searched directory is not found and returns the null directory
			if( fileType ==4) {
				for (int j =0; j<3; j++){
					file.read((char*)&stringChar, sizeof(char));
					fname = fname + stringChar;
				}
				cout << "Directory " << search << " not found\n"; 
				return change;
			}
			//if the namne read in is a program or text file skips it
			if (fileType ==1 || fileType ==2) {
				//cout << fname << endl;
				skipFile(fileType);
				//if name read in is a directory checks to see if it matches, if so gets its info and sets it to the change directory and returns it, if not skips it
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
	
	
