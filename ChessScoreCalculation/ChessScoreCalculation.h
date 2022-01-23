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
	string** ChessArray;
	double* ChessScoresArray;
	list<ChessPiece*> ChessPieceList;
	list<ChessPiece*> EmptyChessPieceList;
	map<pair<int, int>, ChessPiece*> BoardMap;
	void GetChessPieceDatas(string boardName);
	void InitializeChessScoresArray();
	void FindEdibleChessPiece(ChessPiece* chessPiece);
	void CheckForPawn(ChessPiece* chessPiece); // Piyon
	void CheckForKnight(ChessPiece* chessPiece); // At
	void CheckForBishop(ChessPiece* chessPiece); // Fil
	void CheckForRook(ChessPiece* chessPiece); // Kale
	void CheckForQueen(ChessPiece* chessPiece); // Vezir
	void CheckForKing(ChessPiece* chessPiece); // Sah
	void PawnSearch(ChessPiece* chessPiece);
	void CrossSearch(ChessPiece* chessPiece);
	void StraightSearch(ChessPiece* chessPiece);

public:
	void Initialize(string boardName);
	void GetChessPoints(string boardName);
};

