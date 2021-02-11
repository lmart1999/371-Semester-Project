#include <iostream>
#include "Text.h"
using namespace std;

	//Full Constructor
	Text::Text(string n, int s, string c) {
		name = n;
		size = s;
		contents = c;
		
	}
	//primary constructor, called from main to create Text files and determine size
	Text::Text(string n, string c) {
		name = n;
		contents = c;
		findSize();
		
	}
	//Determines size of file based on contents
	void Text::findSize() {
		size = contents.length();
		
	}
	
	// Getters and setters
	void Text::setName(string n) {
		name = n;
	}
	
	string Text::getName() {
		return name;
	}
	
	void Text::setSize(int s) {
		size = s;
	}
	
	int Text::getSize() {
		return size;
	}
	
	void Text::setContents(string c) {
		contents=c;
	}
	
	string Text::getContents() {
		return contents;
	}
	
