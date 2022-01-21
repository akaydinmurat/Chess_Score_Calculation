#include "txtreadwrite.h"
#include <fstream> // Txt read, write functions
#include <iostream>
#include <string>

using namespace std;

void txtreadwrite::InitializeChessBoardArray() {
	try {
		// Number_Of_Samples * Chess_Row_Axis * Chess_Col_Axis'lik bir pointer array oluşturuluyor.
		ChessArray = new string * *[Number_Of_Samples];

		for (int i = 0; i < Number_Of_Samples; i++) {
			ChessArray[i] = new string * [Chess_Row_Axis];
			for (int j = 0; j < Chess_Row_Axis; j++) {
				ChessArray[i][j] = new string[Chess_Col_Axis];
				for (int k = 0; k < Chess_Col_Axis; k++) {
					ChessArray[i][j][k] = "";
				}
			}
		}
	}
	catch (exception ex) {
		cout << "InitializeChessBoardArray: " << ex.what() << endl;
	}
}

void txtreadwrite::ReadTxt() {
	try {
		for (int i = 0; i < Number_Of_Samples; i++) {
			ifstream boardFiles("../Assets/board" + to_string(i + 1) + ".txt");
			string readedChessBoardElement;
			int col, row;

			col = 0;
			row = 0;

			while (getline(boardFiles, readedChessBoardElement)) {

				char seperator = ' '; // space
				Split(readedChessBoardElement, seperator);//Her line için boşluk karekterine kadar ki verileri split ederek, txt icindeki her veriyi ayrı ayrı almaktadir.
				ChessArray[i][row][col] = readedChessBoardElement;

				for (int col = 0; col < Chess_Col_Axis; col++) {
					ChessArray[i][row][col] = chessBoardLineArray[col];
				}

				row++; //Her satırın sütunlarını yazdıktan sonra bir alt satıra geçmek için arttırılıyor.
			}
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

string*** txtreadwrite::GetChessBoardArray() {
	InitializeChessBoardArray();
	ReadTxt();

	return ChessArray;
}