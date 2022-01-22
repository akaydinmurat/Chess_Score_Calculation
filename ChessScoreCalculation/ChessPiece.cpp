#include "ChessPiece.h"
#include <string>
#include <iostream>

using namespace std;

ChessPiece::ChessPiece(int row, int column) {
	Row = row;
	Column = column;
}

void ChessPiece::SetPieceTypeNamePoint(string pieceType) {
	try {
		// Set ChessPiece name
		auto selectedChessElement = ChessElementsMap.find(pieceType);
		int point = GetPointOfChessElements(selectedChessElement->second);

		Point = point; // set selected point of chess piece

		if (pieceType[0] == 'p') {
			Name = ChessPieceNames::piyon;
		}
		else if (pieceType[0] == 'a') {
			Name = ChessPieceNames::at;
		}
		else if (pieceType[0] == 'f') {
			Name = ChessPieceNames::fil;
		}
		else if (pieceType[0] == 'k') {
			Name = ChessPieceNames::kale;
		}
		else if (pieceType[0] == 'v') {
			Name = ChessPieceNames::vezir;
		}
		else if (pieceType[0] == 's') {
			Name = ChessPieceNames::sah;
		}
		else {
			Name = ChessPieceNames::undefinedName;
		}

		// Set Chess player type
		if (pieceType[1] == 's') {
			Player = ChessPlayers::siyah;
		}
		else if (pieceType[1] == 'b') {
			Player = ChessPlayers::beyaz;
		}
		else {
			Player = ChessPlayers::undefinedPlayer;
		}
	}
	catch (exception ex) {
		cout << "SetPieceTypeNamePoint: " << ex.what() << endl;
	}
}

int ChessPiece::GetPointOfChessElements(ChessElements chessElements) {
	try {
		int elementPoint = 0;

		switch (chessElements)
		{
		case ChessElements::ps:
		case ChessElements::pb:
			elementPoint = 1;
			break;

		case ChessElements::as:
		case ChessElements::ab:
			elementPoint = 3;
			break;

		case ChessElements::fs:
		case ChessElements::fb:
			elementPoint = 3;
			break;

		case ChessElements::ks:
		case ChessElements::kb:
			elementPoint = 5;
			break;

		case ChessElements::vs:
		case ChessElements::vb:
			elementPoint = 9;
			break;

		case ChessElements::ss:
		case ChessElements::sb:
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