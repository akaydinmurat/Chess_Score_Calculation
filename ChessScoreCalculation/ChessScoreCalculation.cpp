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

void ChessScoreCalculation::GetChessPieceDatas(string boardName) {

	try {
		txtreadwrite txtReadWrite;
		ChessArray = txtReadWrite.GetChessBoardArray(boardName);

		for (int row = 0; row < Chess_Row_Axis; row++) {
			for (int col = 0; col < Chess_Col_Axis; col++) {

				ChessPiece* chessPiece = new ChessPiece(row, col);
				chessPiece->SetPieceTypeNamePoint(ChessArray[row][col]); // The information of the pieces is filled by calling the constructor for each occupied square. 

				if (ChessArray[row][col] != "--") {
					ChessPieceList.push_back(chessPiece);
				}
				else {
					EmptyChessPieceList.push_back(chessPiece);
				}
				BoardMap[make_pair(row, col)] = chessPiece;
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
		double isInDangerPointConst = 0.5;

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

void ChessScoreCalculation::CheckForPawn(ChessPiece* chessPiece) { // Piyon
	try {
		PawnSearch(chessPiece);
	}
	catch (exception ex) {
		cout << "CheckForPawn: " << ex.what() << endl;
	}
}

void ChessScoreCalculation::CheckForKnight(ChessPiece* chessPiece) { // At
	try {
		//CrossSearch(chessPiece);
	}
	catch (exception ex) {
		cout << "CheckForKnight: " << ex.what() << endl;
	}
}

void ChessScoreCalculation::CheckForBishop(ChessPiece* chessPiece) { // Fil
	try {
		CrossSearch(chessPiece);
	}
	catch (exception ex) {
		cout << "CheckForBishop: " << ex.what() << endl;
	}
}

void ChessScoreCalculation::CheckForRook(ChessPiece* chessPiece) { // Kale
	try {
		StraightSearch(chessPiece);
	}
	catch (exception ex) {
		cout << "CheckForRook: " << ex.what() << endl;
	}
}

void ChessScoreCalculation::CheckForQueen(ChessPiece* chessPiece) { // Vezir
	try {
		StraightSearch(chessPiece);
		CrossSearch(chessPiece);
	}
	catch (exception ex) {
		cout << "CheckForQueen: " << ex.what() << endl;
	}
}

void ChessScoreCalculation::CheckForKing(ChessPiece* chessPiece) { // Sah

}

void ChessScoreCalculation::PawnSearch(ChessPiece* chessPiece) {
	try {
		int row = chessPiece->Row;
		int col = chessPiece->Column;
		int moveableRowPosition_0 = 0, moveableColPosition_0 = 0, moveableRowPosition_1 = 0, moveableColPosition_1 = 0;
		bool isCheckPossible_0 = true, isCheckPossible_1 = true;


		if (chessPiece->Player == chessPiece->siyah) {
			moveableRowPosition_0 = row + 1; moveableColPosition_0 = col - 1; moveableRowPosition_1 = row + 1; moveableColPosition_1 = col + 1;
		}
		else if (chessPiece->Player == chessPiece->beyaz) {
			moveableRowPosition_0 = row - 1; moveableColPosition_0 = col - 1; moveableRowPosition_1 = row - 1; moveableColPosition_1 = col + 1;
		}

		if ((moveableRowPosition_0 < 0 || moveableColPosition_0 < 0) || (moveableRowPosition_0 > 7 || moveableColPosition_0 > 7)) {
			isCheckPossible_0 = false;
		}
		else if ((moveableRowPosition_1 < 0 || moveableColPosition_1 < 0) || (moveableRowPosition_1 > 7 || moveableColPosition_1 > 7)) {
			isCheckPossible_1 = false;
		}


		if (isCheckPossible_0) {
			if (BoardMap[make_pair(moveableRowPosition_0, moveableColPosition_0)]->Player != chessPiece->Player) {
				BoardMap[make_pair(moveableRowPosition_0, moveableColPosition_0)]->IsInDanger = true;
			}
		}

		if (isCheckPossible_1) {
			if (BoardMap[make_pair(moveableRowPosition_1, moveableColPosition_1)]->Player != chessPiece->Player) {
				BoardMap[make_pair(moveableRowPosition_1, moveableColPosition_1)]->IsInDanger = true;
			}
		}
	}
	catch (exception ex) {
		cout << "CrossSearch: " << ex.what() << endl;
	}
}

void ChessScoreCalculation::CrossSearch(ChessPiece* chessPiece) {
	try {
		int row = chessPiece->Row;
		int col = chessPiece->Column;
		int nextPositionRow = 0, nextPositionCol = 0;
		nextPositionRow = row, nextPositionCol = col;

		while (true) {
			nextPositionRow++, nextPositionCol++;
			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}
			else if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
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
			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}
			else if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
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
			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}
			else if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
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
			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}
			else if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
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

void ChessScoreCalculation::StraightSearch(ChessPiece* chessPiece) {
	try {
		int row = chessPiece->Row;
		int col = chessPiece->Column;
		int nextPositionRow = 0, nextPositionCol = 0;
		nextPositionRow = row, nextPositionCol = col;

		while (true) {
			nextPositionCol++;
			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}
			else if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
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
			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}
			else if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
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
			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}
			else if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
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
			ChessPiece* checkedChessPiece = BoardMap[make_pair(nextPositionRow, nextPositionCol)];
			if ((nextPositionRow < 0 || nextPositionCol < 0) || (nextPositionRow > 7 || nextPositionCol > 7)) {
				break;
			}
			else if (checkedChessPiece->Player != chessPiece->Player && checkedChessPiece->Player != chessPiece->undefinedPlayer) {
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

