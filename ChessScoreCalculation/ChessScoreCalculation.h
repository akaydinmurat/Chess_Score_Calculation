#pragma once
#include <string>
#include <unordered_map>

#define Chess_Col_Axis 8
#define Chess_Row_Axis 8
#define Number_Of_Samples 3 // Hesaplanmak istenen ornek chess board sayisi
#define Number_Of_Players 2 // Siyah ve Kirmizi
#define Index_Of_Black 0
#define Index_Of_White 1

using namespace std;

class ChessScoreCalculation
{
	private:
		enum ChessElements { ps, as, fs, ks, vs, ss, pb, ab, fb, kb, vb, sb, outofrange };
		unordered_map<string, ChessElements> const ChessElementsMap = { {"ps",ChessElements::ps}, {"as",ChessElements::as}, {"fs",ChessElements::fs}, {"ks",ChessElements::ks}, {"vs",ChessElements::vs}, {"ss",ChessElements::ss}, 
		{"pb",ChessElements::pb}, {"ab",ChessElements::ab} ,{"fb",ChessElements::fb}, {"kb",ChessElements::kb}, {"vb",ChessElements::vb}, {"sb",ChessElements::sb}, {"--", ChessElements::outofrange} };
		string*** ChessArray;
		int** ChessScoresArray;
		void CalculateChessPoint();	
		void InitializeChessScoresArray();
		int GetPointOfChessElements(ChessElements chessElements);

	public:
		void GetChessPoints();
};

