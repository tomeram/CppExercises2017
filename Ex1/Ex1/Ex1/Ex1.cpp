// Ex1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iterator>
#include<string>
#include <stdexcept>
#include "Board.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::invalid_argument;

int main(int argc, char *argv[])
{
	Board board = Board();
	board.readBoard(argv[1], argv[2]);
	board.writeResponseToFile(argv[2]);
	return 0;
}

