#include <iostream>
#include "txtreadwrite.h"
#include "ChessScoreCalculation.h"

#define Number_Of_Samples 3 // The number of sample chess boards to be calculated

int main()
{
	for (int i = 0; i < Number_Of_Samples; i++) {
		ChessScoreCalculation chessScoreCalculation;
		chessScoreCalculation.Initialize("board" + to_string(i+1)); // Initializes the arrays of board.txt and makes the information of the chess pieces ready.
		chessScoreCalculation.GetChessPoints("board" + to_string(i+1)); // Calculates the points according to the positions of the chess pieces and prints the score information to the screen. 
	}

	return 0;
}