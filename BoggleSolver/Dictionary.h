//
//  Dictionary.h
//  BoggleSolver
//
//  Created by Derrick Marshall on 5/4/17.
//  Copyright © 2017 Derrick Marshall. All rights reserved.
//

#ifndef Dictionary_h
#define Dictionary_h

#include <string>
using namespace std;

const int ALPHA = 26;

struct Node{
	bool wordFlag[ALPHA];
	Node *letterLink[ALPHA];
};

class Dictionary{
private:
	Node *root;
	int numWords;
	
	Node *newNode(){
		Node *newLink = new Node();
		
		for(int index = 0; index < ALPHA; index++){
			newLink -> wordFlag[index] = false;
			newLink -> letterLink[index] = NULL;
		}
		return newLink;
	}
	
public:
	Dictionary();
	~Dictionary();
	Dictionary(string file);
	
	void addWord(string word);
	bool isWord(string word);
	bool isPrefix(string word);
	void PrintWords(string prefix);
	void PrintWordsWrapper(Node *loaction, string prefix);
	int wordCount();
};


#endif /* Dictionary_h */
