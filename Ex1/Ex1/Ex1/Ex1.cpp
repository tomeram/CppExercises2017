// Ex1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iterator>
#include<string>

//using namesapce std;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

int main()
{
	/*

	//parse the first line and derive NumElements
	int numElements;
	string first_line;
	getline(cin, first_line, "=");
	if (first_line != "NumElements") {
		cout << "first line is in a wrong format" << endl;
	}
	getline(cin, first_line);
	try {
		numElements = stoi(first_line);
	
		//create the board and its pieces
		string strLine;
		int id;
		int sides[4];
		int ids[numElements];
		Board *board = &new Board(numElements);
		board->readBoard();
		if (board->error) {
			if (!board->missingID.empty()) {
				cout << "Missing puzzle element(s) with the following IDs: ";
				for (iter = missingID.begin(); iter != missingID.end(); iter++) {
					if (iter != keywords.begin() && iter != keywords.end()-1)
						cout << ", ";
					cout << *iter;
				}
				cout << endl;
			}
			if (!board->wrongID.empty()) {
				cout << "Puzzle of size " << numElements << " cannot have the following IDs: ";
				for (iter = wrongID.begin(); iter != wrongID.end(); iter++) {
					if (iter != wrongID.begin() && iter != wrongID.end() - 1)
						cout << ", ";
					cout << *iter;
				}
				cout << endl;
			}
			if (!board->wrongLineID.empty()) {
				for (int i=0; i<board->wrongLineID.size(); i++) {
					cout << "Puzzle ID " << board->wrongLineID[i] << "has wrong data" << board->wrongLineString[i];
				}
				cout << endl;
			}
		}
		else {
			//Solve the board...
		}
	}
	catch (const invalid_argument& e) {
		cout << "ERROR: could not extract number of elements" << endl;
	}

	*/

	return 0;
}

