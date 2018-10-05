//
//  main.cpp
//  BoggleSolver
//
//  Created by Derrick Marshall on 5/4/17.
//  Copyright © 2017 Derrick Marshall. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

#include "Dictionary.h"

using namespace std;

struct dataItem {
	string letter;
	int val;
};

int rowSz = 4;
int colSz = 4;

void solveBoard(int row, int column, string prefix, string postPrefix, char answer, int count, int &wordC, dataItem matrix[][4], Dictionary &dic, Dictionary &boggleWord, ofstream &outFile);

void printBoard(dataItem matrix[][4], ofstream &outFile);


int main() {
	
	string inFileName;			// input file external name
	string outFileName;
	string command;				// operation to be executed;
	
	dataItem matrix[4][4];
	
	char val, val2, val3, val4;
	char answer = '\n';
	int wordC = 0;
	
	ofstream outFile;			//file contain ing output
	
	try {
		cout << "Enter name of input dictionary file; press return :";
		cin >> inFileName;
		
		cout << "Enter name of output file; press return : ";
		cin >> outFileName;
		cout << endl;
		
		Dictionary dic(inFileName);
		Dictionary boggleWord;
		
		cout << dic.wordCount() << " words loaded\n";
		cout << "Enter Board\n" << "-----------\n";
		
		for(int index = 0; index < rowSz; index++){
			cout << "Row " << index << ": ";
			cin >> val >> val2 >> val3 >> val4;
			
			matrix[index][0].letter = val;
			matrix[index][1].letter = val2;
			matrix[index][2].letter = val3;
			matrix[index][3].letter = val4;
			
			matrix[index][0].val = 0;
			matrix[index][1].val = 0;
			matrix[index][2].val = 0;
			matrix[index][3].val = 0;
		}
		
		cout << endl << "Show Board (y/n)? :";
		cin >> answer;
		
		outFile.open(outFileName);
		
		printBoard(matrix, outFile);
		
		for (int row = 0; row < 4; row++) {
			for (int column = 0; column < 4; column++) {
				string prefix = "", postPrefix = "";
				solveBoard(row, column, prefix, postPrefix, answer, 0, wordC, matrix, dic, boggleWord, outFile);
			}
		}
		
	} catch (string msg) {
		cout << msg << endl;
		outFile.close();
		return 1;
	}
	
	outFile.close();
    return 0;
}


void solveBoard(int row, int column, string prefix, string postPrefix, char answer, int count, int &wordC, dataItem matrix[][4], Dictionary &dic, Dictionary &boggleWord, ofstream &outFile){
	string letChar = "";
	int letNum = 0;
	
	if(row < 0 || row >= rowSz|| column < 0 || column >= colSz)
		return;

	if(matrix[row][column].val != 0)
		return;
	
	if(!dic.isPrefix(prefix))
		return;
	
	
	prefix = postPrefix = prefix + matrix[row][column].letter;
	
	letNum = matrix[row][column].val;
	matrix[row][column].val = count + 1;
	
	if(answer == 'y'){
		letChar = matrix[row][column].letter;
		matrix[row][column].letter = "'" + matrix[row][column].letter + "'";
	}
	
	if((!boggleWord.isWord(prefix)) && dic.isWord(prefix)){
		
		if (answer == 'y') {
			outFile << "Word: " << prefix << endl;
			outFile << "Number of Words: " << wordC + 1 << endl;
		
			for (int index = 0; index < rowSz; index++) {
				outFile << matrix[index][0].letter << "\t";
				outFile << matrix[index][1].letter << "\t";
				outFile << matrix[index][2].letter << "\t";
				outFile << matrix[index][3].letter << "\t";
				outFile << "\t \t";
				outFile << matrix[index][0].val << "\t";
				outFile << matrix[index][1].val << "\t";
				outFile << matrix[index][2].val << "\t";
				outFile << matrix[index][3].val << "\n";
			}
			outFile << endl;
			
		}else
			outFile << wordC + 1 << "\t" <<prefix << endl;
		
		
		boggleWord.addWord(prefix);
		wordC++;
	}
	
	solveBoard(row, column + 1, prefix, postPrefix, answer, count + 1, wordC, matrix, dic, boggleWord, outFile);
	
	solveBoard(row, column - 1, prefix, postPrefix, answer, count + 1, wordC, matrix, dic, boggleWord, outFile);
	
	solveBoard(row + 1, column, prefix, postPrefix, answer, count + 1, wordC, matrix, dic, boggleWord, outFile);
	
	solveBoard(row - 1, column, prefix, postPrefix, answer, count + 1, wordC, matrix, dic, boggleWord, outFile);
	
	solveBoard(row - 1, column - 1, prefix, postPrefix, answer, count + 1, wordC, matrix, dic, boggleWord, outFile);

	solveBoard(row - 1, column + 1, prefix, postPrefix, answer, count + 1, wordC, matrix, dic, boggleWord, outFile);
	
	solveBoard(row + 1, column - 1, prefix, postPrefix, answer, count + 1, wordC, matrix, dic, boggleWord, outFile);
	
	solveBoard(row + 1, column + 1, prefix, postPrefix, answer, count + 1, wordC, matrix, dic, boggleWord, outFile);
	
	if(answer == 'y')
		matrix[row][column].letter = letChar;

	matrix[row][column].val = letNum;
	
	prefix = postPrefix;
	
}

void printBoard(dataItem matrix[][4], ofstream &outFile){
	for(int index = 0; index < rowSz; index++){
		outFile << "Row " << index + 1 << ": ";
		outFile << matrix[index][0].letter << " ";
		outFile << matrix[index][1].letter << " ";
		outFile << matrix[index][2].letter << " ";
		outFile << matrix[index][3].letter << " ";
		outFile << endl;
	}
	outFile << endl;
}


