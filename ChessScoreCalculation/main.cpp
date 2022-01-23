#include <iostream>
#include "txtreadwrite.h"
#include "ChessScoreCalculation.h"

int main()
{
	for (int i = 1; i < 4; i++) {
		ChessScoreCalculation chessScoreCalculation;
		chessScoreCalculation.Initialize("board" + to_string(i)); // Initializes the arrays of board.txt and makes the information of the chess pieces ready.
		chessScoreCalculation.GetChessPoints("board" + to_string(i)); // Calculates the points according to the positions of the chess pieces and prints the score information to the screen. 
	}

	return 0;
}