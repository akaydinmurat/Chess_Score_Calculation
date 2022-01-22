#pragma once
#include <string>
#include <unordered_map>

using namespace std;



class ChessPiece
{
	public:
		enum ChessPieceNames { piyon, at, fil, kale, vezir, sah, undefinedName };
		enum ChessPlayers { siyah, beyaz, undefinedPlayer };
		enum ChessElements { ps, as, fs, ks, vs, ss, pb, ab, fb, kb, vb, sb, outofrange };
		unordered_map<string, ChessElements> const ChessElementsMap = { {"ps",ChessElements::ps}, {"as",ChessElements::as}, {"fs",ChessElements::fs}, {"ks",ChessElements::ks}, {"vs",ChessElements::vs}, {"ss",ChessElements::ss},
		{"pb",ChessElements::pb}, {"ab",ChessElements::ab} ,{"fb",ChessElements::fb}, {"kb",ChessElements::kb}, {"vb",ChessElements::vb}, {"sb",ChessElements::sb}, {"--", ChessElements::outofrange} };

		int Row;
		int Column;
		int Point;
		ChessPieceNames Name;
		ChessPlayers Player;
		ChessPiece(int row, int column);
		void SetPieceTypeNamePoint(string pieceType);
		int GetPointOfChessElements(ChessElements chessElements);
};



