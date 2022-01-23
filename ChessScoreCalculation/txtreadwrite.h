#pragma once
#include <string>
using namespace std;

#define Chess_Col_Axis 8
#define Chess_Row_Axis 8
#define Number_Of_Samples 3 // The number of sample chess boards to be calculated 

class txtreadwrite
{
private:
	void InitializeChessBoardArray();
	void DeleteChessBoardArray();
	void ReadTxt(string boardName);
	int Lenght(string line);
	void Split(string line, char seperator);
	string** ChessArray;
	string chessBoardLineArray[Chess_Col_Axis]; // define max string  

public:
	string** GetChessBoardArray(string boardName);
};

