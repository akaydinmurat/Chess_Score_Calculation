#include <iostream>
#include "txtreadwrite.h"
#include "ChessScoreCalculation.h"

int main()
{
	ChessScoreCalculation chessScoreCalculation;
	chessScoreCalculation.Initialize();
	chessScoreCalculation.GetChessPoints();

	return 0;
}