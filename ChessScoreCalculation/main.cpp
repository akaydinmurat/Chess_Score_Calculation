#include <iostream>
#include "txtreadwrite.h"
#include "ChessScoreCalculation.h"

int main()
{
	for (int i = 1; i < 4; i++) {
		ChessScoreCalculation chessScoreCalculation;
		chessScoreCalculation.Initialize("board" + to_string(i));
		chessScoreCalculation.GetChessPoints();
	}

	return 0;
}