//
//  Dictionary.cpp
//  BoggleSolver
//
//  Created by Derrick Marshall on 5/4/17.
//  Copyright © 2017 Derrick Marshall. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Dictionary.h"

using namespace std;


Dictionary:: Dictionary(){
	root = NULL;
	numWords = 0;
}

Dictionary :: ~Dictionary(){
	
}

Dictionary :: Dictionary(string file){
	ifstream inFile;			// file containt operations
	string command;				// operation to be executed;
	
	inFile.open(file);
	
	if (!inFile) {
		string msg = "File Not Open\n";
		throw msg;
	}
	
	inFile >> command;

	while(!inFile.eof()){
		addWord(command);
		inFile >> command;
	}
	
	inFile.close();
}

int Dictionary:: wordCount(){
	return numWords;
}

void Dictionary:: addWord(string word){
	int letterVal = 0;
	
	if(root == NULL){
		root = newNode();
	}
	
	Node *currentPos = root;
	Node *temp;
	
	for(int index = 0; index < word.length(); index++){
		letterVal = (int)word[index] - (int)'a';
		
		if(currentPos -> letterLink[letterVal] == NULL){
			temp = newNode();
			currentPos -> letterLink[letterVal] = temp;
			currentPos = temp;
		}else
			currentPos = currentPos -> letterLink[letterVal];
	}
	currentPos -> wordFlag[letterVal] = true;
	numWords++;
}

bool Dictionary:: isWord(string word){
	int letterVal = 0;
	
	if(root == NULL)
		return false;
	
	Node *currentPos = root;
	
	for(int index = 0; index < word.length(); index++){
		letterVal = (int)word[index] - (int)'a';
		
		if(currentPos ->letterLink[letterVal] == NULL)
			return false;
		else
			currentPos = currentPos -> letterLink[letterVal];
	}
	
	if(currentPos -> wordFlag[letterVal] == true)
		return true;
	
	return false;
}

bool Dictionary:: isPrefix(string word){
	int letterVal = 0;
	
	if(root == NULL)
		return false;
	
	Node *currentPos = root;
	
	for (int index = 0; index < word.length(); index++) {
		letterVal = (int)word[index] - (int)'a';
		
		if(currentPos -> letterLink[letterVal] == NULL)
			return false;
		else
			currentPos = currentPos -> letterLink[letterVal];
	}
	
	return (NULL != currentPos);
}

void Dictionary:: PrintWords(string prefix){
	int letterVal = 0;
	string word = prefix;
	
	if(!(isPrefix(prefix)))
		return;
	
	Node *currentPos = root;
	
	for (int index = 0; index < prefix.length(); index++) {
		letterVal = (int)prefix[index] - (int)'a';
		
		currentPos = currentPos -> letterLink[letterVal];
	}

	PrintWordsWrapper(currentPos, prefix);
}

void Dictionary:: PrintWordsWrapper(Node *location, string prefix){
	char letter;

	for(int index = 0; index < ALPHA; index++){
		
		if(location -> letterLink[index] != NULL){
			letter = (char)index + 'a';
			PrintWordsWrapper(location->letterLink[index], prefix + letter);
			
			if(isWord(prefix + letter))
				cout << prefix + letter << endl;

		}
	}
}



