#include "ChessScoreCalculation.h"
#include "txtreadwrite.h"
#include "ChessPiece.h"
#include <map>
#include <iostream>

/* Initializes the arrays of board.txt and makes the information of the chess pieces ready. */
void ChessScoreCalculation::Initialize(string boardName) {
	InitializeChessScoresArray();
	GetChessPieceDatas(boardName);
}

/* The data of the chess pieces read from the txt are filled into the arrays to be used in the calculations.  */
void ChessScoreCalculation::GetChessPieceDatas(string boardName) {
	try {
		txtreadwrite txtReadWrite;
		ChessArray = txtReadWrite.GetChessBoardArray(boardName);

		for (int row = 0; row < Chess_Row_Axis; row++) {
			for (int col = 0; col < Chess_Col_Axis; col++) {

				ChessPiece* chessPiece = new ChessPiece(row, col);
				chessPiece->SetPieceTypeNamePoint(ChessArray[row][col]); // The information of the pieces is filled by calling the constructor for each square. 

				if (ChessArray[row][col] != "--") {
					ChessPieceList.push_back(chessPiece); //list of filled squares 
				}
				else {
					EmptyChessPieceList.push_back(chessPiece); //list of empty squares
				}
				BoardMap[make_pair(row, col)] = chessPiece; //contains the chess piece information in each coordinate. 
			}
		}
	}
	catch (exception ex) {
		cout << "GetChessPieceDatas: " << ex.what() << endl;
	}
}
/* Calculates the points according to the positions of the chess piecesand prints the score information to the screen. */
void ChessScoreCalculation::GetChessPoints(string boardName) {
	try {
		ChessPiece* chessPiece;
		double const isInDangerPointConst = 0.5;

		for (const auto& chessPieceMapItems : ChessPieceList) {
			FindEdibleChessPiece(chessPieceMapItems);
		}

		//Sum of points of chess pieces
		for (int row = 0; row < Chess_Row_Axis; row++) {
			for (int col = 0; col < Chess_Col_Axis; col++) {
				chessPiece = BoardMap[make_pair(row, col)];
				if (chessPiece->Player == chessPiece->siyah) {
					if (chessPiece->IsInDanger) {
						ChessScoresArray[Index_Of_Black] += chessPiece->Point * isInDangerPointConst;
					}
					else {
						ChessScoresArray[Index_Of_Black] += BoardMap[make_pair(row, col)]->Point;
					}

				}
				else if (chessPiece->Player == chessPiece->beyaz) {
					if (chessPiece->IsInDanger) {
						ChessScoresArray[Index_Of_White] += chessPiece->Point * isInDangerPointConst;
					}
					else {
						ChessScoresArray[Index_Of_White] += chessPiece->Point;
					}
				}
			}
		}

		// Printing the scores of chess pieces on the screen 
		for (int playerNumber = 0; playerNumber < Number_Of_Players; playerNumber++) {
			if (playerNumber == chessPiece->siyah) {
				cout << boardName << ":	" << "Siyah: " << ChessScoresArray[playerNumber] << "	";
			}
			else if (playerNumber == chessPiece->beyaz) {
				cout << "Beyaz: " << ChessScoresArray[playerNumber] << endl;
			}
		}
	}
	catch (exception ex) {
		cout << "GetChessPoints: " << ex.what() << endl;
	}
}

void ChessScoreCalculation::FindEdibleChessPiece(ChessPiece* chessPiece) {
	try {
		switch (chessPiece->Name)
		{
		case chessPiece->piyon:
			CheckForPawn(chessPiece);
			break;
		case chessPiece->at:
			CheckForKnight(chessPiece);
			break;
		case chessPiece->fil:
			CheckForBishop(chessPiece);
			break;
		case chessPiece->kale:
			CheckForRook(chessPiece);
			break;
		case chessPiece->vezir:
			CheckForQueen(chessPiece);
			break;
		case chessPiece->sah:
			CheckForKing(chessPiece);
			break;

		default:
			break;
		}
	}
	catch (exception ex) {
		cout << "FindEdibleChessPiece: " << ex.what() << endl;
	}
}

/* Calling the search algorithm for the Pawn(Piyon). */
void ChessScoreCalculation::CheckForPawn(ChessPiece* chessPiece) {
	try {
		PawnSearch(chessPiece);
	}
	catch (exception ex) {
		cout << "CheckForPawn: " << ex.what() << endl;
	}
}

/* Calling the search algorithm for the Knight(At).*/
void ChessScoreCalculation::CheckForKnight(ChessPiece* chessPiece) {
	try {
		KnightSearch(chessPiece);
	}
	catch (exception ex) {
		cout << "CheckForKnight: " << ex.what() << endl;
	}
}

/* Calling the search algorithm for the Bishop(Fil).*/
void ChessScoreCalculation::CheckForBishop(ChessPiece* chessPiece) {
	try {
		CrossSearch(chessPiece);
	}
	catch (exception ex) {
		cout << "CheckForBishop: " << ex.what() << endl;
	}
}

/* Calling the search algorithm for the Rook(Kale).*/
void ChessScoreCalculation::CheckForRook(ChessPiece* chessPiece) {
	try {
		StraightSearch(chessPiece);
	}
	catch (exception ex) {
		cout << "CheckForRook: " << ex.what() << endl;
	}
}

/* Calling the search algorithm for the Queen(Vezir).*/
void ChessScoreCalculation::CheckForQueen(ChessPiece* chessPiece) {
	try {
		StraightSearch(chessPiece);
		CrossSearch(chessPiece);
	}
	catch (exception ex) {
		cout << "CheckForQueen: " << ex.what() << endl;
	}
}

/* Calling the search algorithm for the King(Sah).*/
void ChessScoreCalculation::CheckForKing(ChessPiece* chessPiece) {
	try {
		KingSearch(chessPiece);
	}
	catch (exception ex) {
		cout << "CheckForKing: " << ex.what() << endl;
	}
}

/* Edible chess piece search algorithm for Pawn(Piyon).*/
void ChessScoreCalculation::PawnSearch(ChessPiece* chessPiece) {
	try {
		int row = chessPiece->Row;
		int col = chessPiece->Column;
		int nextPositionRow_0 = 0, nextPositionCol_0 = 0, nextPositionRow_1 = 0, nextPositionCol_1 = 0;
		bool isCheckPossible_0 = true, isCheckPossible_1 = true;

		if (chessPiece->Player == chessPiece->siyah) {
			nextPositionRow_0 = row + 1; nextPositionCol_0 = col - 1; nextPositionRow_1 = row + 1; nextPositionCol_1 = col + 1;
		}
		else if (chessPiece->Player == chessPiece->beyaz) {
			nextPositionRow_0 = row - 1; nextPositionCol_0 = col - 1; nextPositionRow_1 = row - 1; nextPositionCol_1 = col + 1;
		}

		if ((nextPositionRow_0 < 0 || nextPositionCol_0 < 0) || (nextPositionRow_0 > 7 || nextPositionCol_0 > 7)) {
			isCheckPossible_0 = false;
		}

		if ((nextPositionRow_1 < 0 || nextPositionCol_1 < 0) || (nextPositionRow_1 > 7 || nextPositionCol_1 > 7)) {
			isCheckPossible_1 = false;
		}

		if (isCheckPossible_0) {
			if (BoardMap[make_pair(nextPositionRow_0, nextPositionCol_0)]->Player != chessPiece->Player && BoardMap[make_pair(nextPositionRow_0, nextPositionCol_0)]->Player != chessPiece->undefinedPlayer) {
				BoardMap[make_pair(nextPositionRow_0, nextPositionCol_0)]->IsInDanger = true;
			}
		}

		if (isCheckPossible_1) {
			if (BoardMap[make_pair(nextPositionRow_1, nextPositionCol_1)]->Player != chessPiece->Player && BoardMap[make_pair(nextPositionRow_1, nextPositionCol_1)]->Player != chessPiece->undefinedPlayer) {
				BoardMap[make_pair(nextPositionRow_1, nextPositionCol_1)]->IsInDanger = true;
			}
		}
	}
	catch (exception ex) {
		cout << "CrossSearch: " << ex.what() << endl;
	}
}

/* Edible chess piece search algorithm for Knight(At).*/
void ChessScoreCalculation::KnightSearch(ChessPiece* chessPiece) {
	try {
		int row = chessPiece->Row;
		int col = chessPiece->Column;
		int nextPositionRow = 0, nextPositionCol_0 = 0, nextPositionCol_1 = 0;
		bool isCheckPossible_0 = true, isCheckPossible_1 = true;

		for (int i = -2; i < 3; i++) {
			isCheckPossible_0 = true;
			isCheckPossible_1 = true;
			if (i == -2) {
				nextPositionCol_0 = -1;
				nextPositionCol_1 = 1;
			}
			else if (i == -1 || i == 1) {
				nextPositionCol_0 = -2;
				nextPositionCol_1 = 2;
			}
			else if (i == 2) {
				nextPositionCol_0 = -1;
				nextPositionCol_1 = 1;
			}
			else {
				continue;
			}
			nextPositionRow = i + row;
			nextPositionCol_0 = nextPositionCol_0 + col;
			nextPositionCol_1 = nextPositionCol_1 + col;

			if ((nextPositionRow < 0 || nextPositionCol_0 < 0) || (nextPositionRow > 7 || nextPositionCol_0 > 7)) {
				isCheckPossible_0 = false;
			}

			if ((nextPositionRow < 0 || nextPositionCol_1 < 0) || (nextPositionRow > 7 || nextPositionCol_1 > 7)) {
				isCheckPossible_1 = false;
			}

			if (isCheckPossible_0) {
				if (BoardMap[make_pair(nextPositionRow, nextPositionCol_0)]->Player != chessPiece->Player && BoardMap[make_pair(nextPositionRow, nextPositionCol_0)]->Player != chessPiece->undefinedPlayer) {
					BoardMap[make_pair(nextPositionRow, nextPositionCol_0)]->IsInDanger = true;
				}
			}

			if (isCheckPossible_1) {
				if (BoardMap[make_pair(nextPositionRow, nextPositionCol_1)]->Player != chessPiece->Player && BoardMap[make_pair(nextPositionRow, nextPositionCol_1)]->Player != chessPiece->undefinedPlayer) {
					BoardMap[make_pair(nextPositionRow, nextPositionCol_1)]->IsInDanger = true;
				}
			}
		}
	}
	catch (exception ex) {
		cout << "KnightSearch: " << ex.what() << endl;
	}
}

/* Edible chess piece search algorithm for King(Sah).*/
void ChessScoreCalculation::KingSearch(ChessPiece* chessPiece) {
	try {
		int row = chessPiece->Row;
		int col = chessPiece->Column;
		int nextPositionRow = 0, nextPositionCol = 0;

		// looking for all the squares around King(Sah). 
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				nextPositionRow = i + row;
				nextPositionCol = j + col;

				if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
					continue;
				}
				else {
					if (BoardMap[make_pair(nextPositionRow, nextPositionCol)]->Player != chessPiece->Player && BoardMap[make_pair(nextPositionRow, nextPositionCol)]->Player != chessPiece->undefinedPlayer) {
						BoardMap[make_pair(nextPositionRow, nextPositionCol)]->IsInDanger = true;
					}
				}
			}
		}
	}
	catch (exception ex) {
		cout << "KingSearch: " << ex.what() << endl;
	}
}

/* Edible chess piece search algorithm for Bishop(Fil) and Queen(Vezir).*/
void ChessScoreCalculation::CrossSearch(ChessPiece* chessPiece) {
	try {
		int row = chessPiece->Row;
		int col = chessPiece->Column;
		int nextPositionRow = 0, nextPositionCol = 0;
		nextPositionRow = row, nextPositionCol = col;

		while (true) {
			nextPositionRow++, nextPositionCol++;
			
			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}

			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
				checkedChessPiece->IsInDanger = true;
				break;
			}
			else if (checkedChessPiece->Player == chessPiece->Player) {
				break;
			}

		}
		nextPositionRow = row, nextPositionCol = col;
		while (true) {
			nextPositionRow++, nextPositionCol--;

			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}

			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
				checkedChessPiece->IsInDanger = true;
				break;
			}
			else if (checkedChessPiece->Player == chessPiece->Player) {
				break;
			}
		}
		nextPositionRow = row, nextPositionCol = col;
		while (true) {
			nextPositionRow--, nextPositionCol++;

			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}

			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
				checkedChessPiece->IsInDanger = true;
				break;
			}
			else if (checkedChessPiece->Player == chessPiece->Player) {
				break;
			}
		}
		nextPositionRow = row, nextPositionCol = col;
		while (true) {
			nextPositionRow--, nextPositionCol--;

			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}

			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
				checkedChessPiece->IsInDanger = true;
				break;
			}
			else if (checkedChessPiece->Player == chessPiece->Player) {
				break;
			}
		}
	}
	catch (exception ex) {
		cout << "CrossSearch: " << ex.what() << endl;
	}
}

/* Edible chess piece search algorithm for Rook(Kale) and Queen(Vezir).*/
void ChessScoreCalculation::StraightSearch(ChessPiece* chessPiece) {
	try {
		int row = chessPiece->Row;
		int col = chessPiece->Column;
		int nextPositionRow = 0, nextPositionCol = 0;
		nextPositionRow = row, nextPositionCol = col;

		while (true) {
			nextPositionCol++;

			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}

			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
				checkedChessPiece->IsInDanger = true;
				break;
			}
			else if (checkedChessPiece->Player == chessPiece->Player) {
				break;
			}
		}

		nextPositionRow = row, nextPositionCol = col;
		while (true) {
			nextPositionCol--;
			
			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}

			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
				checkedChessPiece->IsInDanger = true;
				break;
			}
			else if (checkedChessPiece->Player == chessPiece->Player) {
				break;
			}
		}

		nextPositionRow = row, nextPositionCol = col;
		while (true) {
			nextPositionRow++;

			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}

			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
				checkedChessPiece->IsInDanger = true;
				break;
			}
			else if (checkedChessPiece->Player == chessPiece->Player) {
				break;
			}
		}

		nextPositionRow = row, nextPositionCol = col;
		while (true) {
			nextPositionRow--;
			
			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}

			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
				checkedChessPiece->IsInDanger = true;
				break;
			}
			else if (checkedChessPiece->Player == chessPiece->Player) {
				break;
			}
		}
	}
	catch (exception ex) {
		cout << "StraightSearch: " << ex.what() << endl;
	}
}

/*The pointer array to hold the points is initialized. */
void ChessScoreCalculation::InitializeChessScoresArray() {
	try {
		// Creating a pointer array of size "Number_Of_Players".  
		ChessScoresArray = new double[Number_Of_Samples];
		for (int i = 0; i < Number_Of_Players; i++) {
			ChessScoresArray[i] = 0;
		}
	}
	catch (exception ex) {
		cout << "InitializeChessScoresArray: " << ex.what() << endl;
	}
}

