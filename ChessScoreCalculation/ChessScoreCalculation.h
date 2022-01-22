#pragma once
#include <string>
#include <map>
#include "ChessPiece.h"

#define Chess_Col_Axis 8
#define Chess_Row_Axis 8
#define Number_Of_Samples 3 // The number of sample chess boards to be calculated 
#define Number_Of_Players 2 // Black and white
#define Index_Of_Black 0
#define Index_Of_White 1

using namespace std;

class ChessScoreCalculation
{
	private:
		string*** ChessArray;
		int** ChessScoresArray;
		typedef map<int, list<ChessPiece>> BasePairMap;
		BasePairMap chessPieceMap;
		void GetChessPieceDatas();
		void InitializeChessScoresArray();

	public:
		void Initialize();
		void GetChessPoints();
};

