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
	list<ChessPiece*> ChessPieceList; //list of filled squares 
	list<ChessPiece*> EmptyChessPieceList; //list of empty squares
	map<pair<int, int>, ChessPiece*> BoardMap; //contains the chess piece information in each coordinate. 
	void GetChessPieceDatas(string boardName); // the data of the chess pieces read from the txt are filled into the arrays to be used in the calculations.
	void InitializeChessScoresArray(); // The pointer array to hold the points is initialized. 
	void FindEdibleChessPiece(ChessPiece* chessPiece); // Calculates the points according to the positions of the chess piecesand prints the score information to the screen.
	void CheckForPawn(ChessPiece* chessPiece); // Calling the search algorithm for the Pawn(Piyon). 
	void CheckForKnight(ChessPiece* chessPiece); // Calling the search algorithm for the Knight(At).
	void CheckForBishop(ChessPiece* chessPiece); // Calling the search algorithm for the Bishop(Fil).
	void CheckForRook(ChessPiece* chessPiece); // Calling the search algorithm for the Rook(Kale).
	void CheckForQueen(ChessPiece* chessPiece); // Calling the search algorithm for the Queen(Vezir).
	void CheckForKing(ChessPiece* chessPiece); // Calling the search algorithm for the King(Sah).
	void PawnSearch(ChessPiece* chessPiece); // Edible chess piece search algorithm for Pawn(Piyon).
	void KnightSearch(ChessPiece* chessPiece); // Edible chess piece search algorithm for Knight(At).
	void KingSearch(ChessPiece* chessPiece); // Edible chess piece search algorithm for King(Sah).
	void CrossSearch(ChessPiece* chessPiece); // Edible chess piece search algorithm for Bishop(Fil) and Queen(Vezir).
	void StraightSearch(ChessPiece* chessPiece); // Edible chess piece search algorithm for Rook(Kale) and Queen(Vezir).

public:
	void Initialize(string boardName); // Initializes the arrays of board.txt and makes the information of the chess pieces ready.
	void GetChessPoints(string boardName); // Calculates the points according to the positions of the chess piecesand prints the score information to the screen.
};

