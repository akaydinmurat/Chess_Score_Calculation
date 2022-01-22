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
			chessPieceMap.insert(pair<int, list<ChessPiece>>(i, ChessPieceList));
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
			for (auto chessPieceMapItems : chessPieceMap[i]) {
				ChessPiece chessPiece = chessPieceMapItems;

				if (chessPiece.Player == chessPiece.siyah) {
					ChessScoresArray[i][Index_Of_Black] += chessPiece.Point;
				}
				else if (chessPiece.Player == chessPiece.beyaz) {
					ChessScoresArray[i][Index_Of_White] += chessPiece.Point;
				}
				else {
					cout << "Points cannot be set for an undefined player !" << endl;
				}		
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

