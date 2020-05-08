/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, pieceAtInit1) {
	Piezas p;
	ASSERT_EQ(p.pieceAt(0, 0), Blank);
}

TEST(PiezasTest, pieceAtInit2) {
	Piezas p;
	ASSERT_EQ(p.pieceAt(1, 1), Blank);
}

TEST(PiezasTest, pieceAtInit3) {
	Piezas p;
	ASSERT_EQ(p.pieceAt(3, 4), Invalid);
}

TEST(PiezasTest, pieceAtInit4) {
	Piezas p;
	ASSERT_EQ(p.pieceAt(4, 4), Invalid);
}

TEST(PiezasTest, pieceAtInit5) {
	Piezas p;
	ASSERT_EQ(p.pieceAt(4, 3), Invalid);
}

TEST(PiezasTest, pieceAtInit6) {
	Piezas p;
	ASSERT_EQ(p.pieceAt(-1, 0), Invalid);
}

TEST(PiezasTest, pieceAtInit7) {
	Piezas p;
	ASSERT_EQ(p.pieceAt(2, 3), Blank);
}



TEST(PiezasTest, placeInit1) {
	Piezas p;
	p.dropPiece(0);
	ASSERT_EQ(p.pieceAt(0, 0), X);
}

TEST(PiezasTest, placeInit2) {
	Piezas p;
	p.dropPiece(3);
	ASSERT_EQ(p.pieceAt(0, 3), X);
}

TEST(PiezasTest, placeInit3) {
	Piezas p;
	Piece ret = p.dropPiece(-1);
	bool bad = p.pieceAt(0,0) == X || p.pieceAt(0,1) == X || p.pieceAt(0,2) == X || p.pieceAt(0,3) == X;
	bad = bad || (ret != Invalid);
	ASSERT_FALSE(bad);
}

TEST(PiezasTest, placeInit4) {
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(0);
	ASSERT_EQ(p.pieceAt(1, 0), O);
}

TEST(PiezasTest, placeInit5) {
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(0);
	p.dropPiece(0);
	ASSERT_EQ(p.pieceAt(2, 0), X);
}

TEST(PiezasTest, placeInit6) {
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(0);
	p.dropPiece(0);
	Piece ret = p.dropPiece(0);
	ASSERT_EQ(ret, Blank);
}

TEST(PiezasTest, placeInit7) {
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(0);
	ASSERT_EQ(p.pieceAt(2, 0), O);
}

TEST(PiezasTest, placeInit8) {
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(2);
	p.dropPiece(3);
	bool bad = false;
	for (int i = 0; i < BOARD_COLS; i++) {
		if (p.pieceAt(1, i) != Blank) {
			bad = true;
			break;
		}
	}
	ASSERT_FALSE(bad);
}

TEST(PiezasTest, reset1) {
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(1);
	p.dropPiece(1);
	p.dropPiece(2);
	p.dropPiece(2);
	p.dropPiece(2);
	p.dropPiece(3);
	p.dropPiece(3);
	p.reset();
	bool bad = false;
	for (int i = 0; i < BOARD_ROWS; i++) {
		for (int j = 0; j < BOARD_COLS; j++) {
			if (p.pieceAt(i, j) != Blank) {
				bad = true;
				break;
			}
		}
	}
	ASSERT_FALSE(bad);
}

TEST(PiezasTest, game0) {
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(2);
	p.dropPiece(0);
	ASSERT_EQ(p.gameState(), Invalid);
}

TEST(PiezasTest, game1) {
	// - - - -
	// X O X O
	// O X O X
	// X O X O
	Piezas p;
	for (int i = 0; i < BOARD_COLS; i++) {
		for (int j = 0; j < BOARD_ROWS; j++) {
			p.dropPiece(i);
		}
	}

	ASSERT_EQ(p.gameState(), Blank);
}

TEST(PiezasTest, game2) {
	// - - - -
	// X X X X
	// O X O X
	// O O O O
	Piezas p;
	int turns[] = {0, 0, 1, 0, 1, 1, 2, 2, 3, 2, 3, 3};
	for (int i = 0; i < BOARD_COLS * BOARD_ROWS; i++) {
		p.dropPiece(turns[i]);
	}
	ASSERT_EQ(p.gameState(), Blank);
}

TEST(PiezasTest, game3) {
	// - - - - 
	// O X X X
	// O X O O
	// X X O O
	Piezas p;
	int turns[] = {1, 3, 1, 3, 0, 2, 1, 2, 2, 0, 3, 0};
	for (int i = 0; i < BOARD_COLS * BOARD_ROWS; i++) {
		p.dropPiece(turns[i]);
	}
	ASSERT_EQ(p.gameState(), X);
}

TEST(PiezasTest, game4) {
	// - - - - 
	// O O O O
	// O X X O
	// X X X O   
	Piezas p;
	int turns[] = {1, 3, 1, 3, 0, 0, 2, 0, 2, 3, 3, 1, 3, 2}; //14
	for (int i = 0; i < 14; i++) {
		p.dropPiece(turns[i]);
	}
	ASSERT_EQ(p.gameState(), O);
}

TEST(PiezasTest, game5) {
	// - - - - 
	// X O O O
	// X O O O
	// X O O O
	Piezas p;
	int turns[] = {0, 1, 0, 1, 0, 1, 0, 2, 0, 2, 0, 2, 0, 3, 0, 3, 0, 3}; //18
	for (int i = 0; i < 18; i++) {
		p.dropPiece(turns[i]);
	}
	ASSERT_EQ(p.gameState(), Blank);
}

TEST(PiezasTest, game6) {
	// - - - - 
	// O O X O
	// X X X X
	// X O O O
	Piezas p;
	int turns[] = {0, 1, 0, 2, 1, 3, 2, 0, 3, 1, 2, 3};
	for (int i = 0; i < BOARD_COLS * BOARD_ROWS; i++) {
		p.dropPiece(turns[i]);
	}
	ASSERT_EQ(p.gameState(), X);
}

TEST(PiezasTest, game7) {
	// - - - - 
	// O X X X
	// O O O O
	// X X O X
	Piezas p;
	int turns[] = {3, 2, 1, 2, 0, 3, 3, 1, 2, 0, 1, 0};
	for (int i = 0; i < BOARD_COLS * BOARD_ROWS; i++) {
		p.dropPiece(turns[i]);
	}
	ASSERT_EQ(p.gameState(), O);
}

TEST(PiezasTest, game8) {
	// - - - - 
	// O O X O
	// O O X O
	// O O O O
	Piezas p;
	int turns[] = {-1, 0, -1, 0, -1, 0, -1, 1, -1, 1, -1, 1, -1, 2, 2, 3, 2, 3, 3};
	for (int i = 0; i < 19; i++) {
		p.dropPiece(turns[i]);
	}
	ASSERT_EQ(p.gameState(), O);
}

TEST(PiezasTest, game9) {
	// - - - - 
	// O X X O
	// X O X O
	// X O X X
	Piezas p;
	int turns[] = {0, 1, 0, 1, 1, 0, 2, -1, 3, 3, 2, 3, 2}; //13
	for (int i = 0; i < 13; i++) {
		p.dropPiece(turns[i]);
	}
	ASSERT_EQ(p.gameState(), X);
}

TEST(PiezasTest, game10) {
	// - - - - 
	// - - - -
	// - - - -
	// - - - -
	Piezas p;
	int turns[] = {-1, -1, -6, -14, 14, 9999, -9999, -1, -1, -1, -1, -1, -1, -1};
	for (int i = 0; i < 14; i++) {
		p.dropPiece(turns[i]);
	}
	ASSERT_EQ(p.gameState(), Invalid);
}

TEST(PiezasTest, game11) {
	// - - - -
	// X O X O
	// X O X O
	// X O X O
	Piezas p;
	int turns[] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
	for (int i = 0; i < 12; i++) {
		p.dropPiece(turns[i]);
	}
	ASSERT_EQ(p.gameState(), Blank);
}

