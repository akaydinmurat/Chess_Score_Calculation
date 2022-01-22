#include "ChessScoreCalculation.h"
#include "txtreadwrite.h"
#include "ChessPiece.h"
#include <map>
#include <iostream>

void ChessScoreCalculation::GetChessPieceDatas() {

	try {
		txtreadwrite txtReadWrite;
		ChessArray = txtReadWrite.GetChessBoardArray();

		for (int i = 0; i < Number_Of_Samples; i++) {

			list<ChessPiece> ChessPieceList;

			for (int row = 0; row < Chess_Row_Axis; row++) {
				for (int col = 0; col < Chess_Col_Axis; col++) {

					if (ChessArray[i][row][col] != "--") {
						ChessPiece chessPiece(row, col);
						chessPiece.SetPieceTypeNamePoint(ChessArray[i][row][col]); // The information of the pieces is filled by calling the constructor for each occupied square. 
						ChessPieceList.push_back(chessPiece);
					}
				}
			}
			ChessPieceMap.insert(pair<int, list<ChessPiece>>(i, ChessPieceList));
		}
	}
	catch (exception ex) {
		cout << "CalculateChessPoint: " << ex.what() << endl;
	}
}

void ChessScoreCalculation::Initialize() {
	InitializeChessScoresArray();
	GetChessPieceDatas();
}

void ChessScoreCalculation::GetChessPoints() {
	try {

		for (int i = 0; i < Number_Of_Samples; i++) {
			for (auto chessPieceMapItems : ChessPieceMap[i]) {

				FindEdibleChessPiece(i, chessPieceMapItems);

				/*if (chessPieceMapItems.Player == chessPieceMapItems.siyah) {
					ChessScoresArray[i][Index_Of_Black] += chessPieceMapItems.Point;
				}
				else if (chessPieceMapItems.Player == chessPieceMapItems.beyaz) {
					ChessScoresArray[i][Index_Of_White] += chessPieceMapItems.Point;
				}
				else {
					cout << "Points cannot be set for an undefined player !" << endl;
				}	*/
			}
		}


		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++) {
				cout << ChessScoresArray[i][j] << endl;
			}
		}
	}
	catch (exception ex) {
		cout << "GetChessPoints: " << ex.what() << endl;
	}
}

void ChessScoreCalculation::InitializeChessScoresArray() {
	try {
		// Creating a pointer array of size "Number_Of_Samples * Number_Of_Players".  
		ChessScoresArray = new int* [Number_Of_Samples];

		for (int i = 0; i < Number_Of_Samples; i++) {
			ChessScoresArray[i] = new int[Number_Of_Players];
			for (int j = 0; j < Number_Of_Players; j++) {
				ChessScoresArray[i][j] = 0;
			}
		}
	}
	catch (exception ex) {
		cout << "GetChessPoints: " << ex.what() << endl;
	}
}

void ChessScoreCalculation::FindEdibleChessPiece(int boardNumber, ChessPiece chessPiece) {

	switch (chessPiece.Name)
	{
	case chessPiece.piyon:
		CheckForPawn(boardNumber, chessPiece);
		break;
	case chessPiece.at:
		CheckForKnight(boardNumber, chessPiece);
		break;
	case chessPiece.fil:
		CheckForBishop(boardNumber, chessPiece);
		break;
	case chessPiece.kale:
		CheckForRook(boardNumber, chessPiece);
		break;
	case chessPiece.vezir:
		CheckForQueen(boardNumber, chessPiece);
		break;
	case chessPiece.sah:
		CheckForKing(boardNumber, chessPiece);
		break;

	default:
		break;
	}

}

void ChessScoreCalculation::CheckForPawn(int boardNumber, ChessPiece chessPiece) { // Piyon
	int row = chessPiece.Row;
	int col = chessPiece.Column;
	int moveableRowPosition_0 = 0;
	int moveableColPosition_0 = 0;
	int moveableRowPosition_1 = 0;
	int moveableColPosition_1 = 0;


	if (chessPiece.Player == chessPiece.siyah) {
		moveableRowPosition_0 = row + 1;
		moveableColPosition_0 = col - 1;
		moveableRowPosition_1 = row + 1;
		moveableColPosition_1 = col + 1;

	}
	else if (chessPiece.Player == chessPiece.beyaz) {
		moveableRowPosition_0 = row - 1;
		moveableColPosition_0 = col - 1;
		moveableRowPosition_1 = row - 1;
		moveableColPosition_1 = col + 1;
	}

	for (auto chessPieceMapItems : ChessPieceMap[boardNumber]) {

		if (chessPieceMapItems.Player != chessPiece.Player) {
			int pieceRow = chessPieceMapItems.Row;
			int pieceCol = chessPieceMapItems.Column;

			if (pieceRow == moveableRowPosition_0 && pieceCol == moveableColPosition_0) {
				chessPieceMapItems.IsInDanger = true;
			}
			else if (pieceRow == moveableRowPosition_1 && pieceCol == moveableColPosition_1) {
				chessPieceMapItems.IsInDanger = true;
			}
		}
	}
}

void ChessScoreCalculation::CheckForKnight(int boardNumber, ChessPiece chessPiece) { // At

}

void ChessScoreCalculation::CheckForBishop(int boardNumber, ChessPiece chessPiece) { // Fil

}

void ChessScoreCalculation::CheckForRook(int boardNumber, ChessPiece chessPiece) { // Kale

}

void ChessScoreCalculation::CheckForQueen(int boardNumber, ChessPiece chessPiece) { // Vezir

}

void ChessScoreCalculation::CheckForKing(int boardNumber, ChessPiece chessPiece) { // Sah

}

