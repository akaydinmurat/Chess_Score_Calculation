#include "txtreadwrite.h"
#include <fstream> // Txt read, write functions
#include <iostream>
#include <string>

using namespace std;

string** txtreadwrite::GetChessBoardArray(string boardName) {
	InitializeChessBoardArray();
	ReadTxt(boardName);

	return ChessArray;
}
void txtreadwrite::InitializeChessBoardArray() {
	try {
		// Creating a pointer array of size "Chess_Row_Axis * Chess_Col_Axis".
		ChessArray = new string * [Chess_Row_Axis];

		for (int row = 0; row < Chess_Row_Axis; row++) {
			ChessArray[row] = new string[Chess_Col_Axis];
			for (int col = 0; col < Chess_Col_Axis; col++) {
				ChessArray[row][col] = "";
			}
		}
	}
	catch (exception ex) {
		cout << "InitializeChessBoardArray: " << ex.what() << endl;
	}
}

void txtreadwrite::ReadTxt(string boardName) {
	try {
		ifstream boardFiles("../Assets/" + boardName + ".txt");
		string readedChessBoardElement;
		int col, row;

		col = 0;
		row = 0;

		while (getline(boardFiles, readedChessBoardElement)) {

			char seperator = ' '; // space
			Split(readedChessBoardElement, seperator);//It takes each data in txt separately by splitting the data up to the space character for each line. 
			ChessArray[row][col] = readedChessBoardElement;

			for (int col = 0; col < Chess_Col_Axis; col++) {
				ChessArray[row][col] = chessBoardLineArray[col];
			}

			row++; //After writing the columns of each row, it is incremented to move to the next row. 
		}
	}
	catch (exception ex) {
		cout << "ReadTxt: " << ex.what() << endl;
	}
}

// length of the string  
int txtreadwrite::Lenght(string line)
{
	try {
		int length = 0;
		for (int i = 0; line[i] != '\0'; i++) {
			length++;
		}

		return length;
	}
	catch (exception ex) {
		cout << "Lenght: " << ex.what() << endl;
	}
}

void txtreadwrite::Split(string line, char seperator)
{
	try {
		int currIndex = 0, i = 0;
		int startIndex = 0, endIndex = 0;
		while (i <= Lenght(line))
		{
			if (line[i] == seperator || i == Lenght(line))
			{
				endIndex = i;
				string subStr = "";
				subStr.append(line, startIndex, endIndex - startIndex);
				chessBoardLineArray[currIndex] = subStr;
				currIndex += 1;
				startIndex = endIndex + 1;
			}
			i++;
		}
	}
	catch (exception ex) {
		cout << "Split: " << ex.what() << endl;
	}
}

void txtreadwrite::DeleteChessBoardArray() {
	try {
		free(ChessArray);
	}
	catch (exception ex) {
		cout << "DeleteChessBoardArray: " << ex.what() << endl;
	}
}