#include "ChessScoreCalculation.h"
#include "txtreadwrite.h"
#include <iostream>

void ChessScoreCalculation::CalculateChessPoint() {

	try {
		txtreadwrite txtReadWrite;
		ChessArray = txtReadWrite.GetChessBoardArray();

		InitializeChessScoresArray(); // Hesaplanan Skor'larin yazdirilacagi array

		for (int i = 0; i < Number_Of_Samples; i++) {
			for (int j = 0; j < Chess_Row_Axis; j++) {
				for (int k = 0; k < Chess_Col_Axis; k++) {
					string deneme = ChessArray[i][j][k];
					auto selectedChessElement = ChessElementsMap.find(ChessArray[i][j][k]);
					int point = GetPointOfChessElements(selectedChessElement->second);

					if (selectedChessElement->second < 6) { // Siyahlar icin puan toplami
						ChessScoresArray[i][Index_Of_Black] += point;
					}
					else {
						ChessScoresArray[i][Index_Of_White] += point; // Beyazlar icin puan toplami
					}
				}
			}
		}
	}
	catch (exception ex) {
		cout << "CalculateChessPoint: " << ex.what() << endl;
	}
}

void ChessScoreCalculation::GetChessPoints() {
	try {
		CalculateChessPoint();
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
		// Number_Of_Samples * Number_Of_Players bir pointer array oluşturuluyor.
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

int ChessScoreCalculation::GetPointOfChessElements(ChessElements chessElements) {
	try {
		int elementPoint = 0;

		switch (chessElements)
		{
		case ChessElements::ps :
		case ChessElements::pb :
			elementPoint = 1;
			break;

		case ChessElements::as :
		case ChessElements::ab :
			elementPoint = 3;
			break;

		case ChessElements::fs :
		case ChessElements::fb :
			elementPoint = 3;
			break;

		case ChessElements::ks :
		case ChessElements::kb :
			elementPoint = 5;
			break;

		case ChessElements::vs :
		case ChessElements::vb :
			elementPoint = 9;
			break;

		case ChessElements::ss :
		case ChessElements::sb :
			elementPoint = 100;
			break;

		default:
			elementPoint = 0;
			break;
		}

		return elementPoint;
	}
	catch (exception ex) {
		cout << "GetPointOfChessElements: " << ex.what() << endl;
	}
}

