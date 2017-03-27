/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
#include <cstdio>
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, place_into_invalid)
{
  Piezas piezas;
  Piece check=piezas.dropPiece(4);

  ASSERT_EQ(check,Invalid);
}

TEST(PiezasTest, place_into_overflow)
{
  Piezas piezas;
  piezas.dropPiece(0);
  piezas.dropPiece(0);
  piezas.dropPiece(0);

  Piece check=piezas.dropPiece(0);
  ASSERT_EQ(check,Blank);
}

TEST(PiezasTest, place_stacking_piece)
{
  Piezas piezas;
  piezas.dropPiece(0);
  Piece check=piezas.dropPiece(0);

  ASSERT_EQ(check,O);
}

TEST(PiezasTest, place_first_piece)
{
  Piezas piezas;
  Piece check=piezas.dropPiece(0);
  
  ASSERT_EQ(check,X);
}

TEST(PiezasTest, construct_empty_board)
{
  Piezas piezas;
  int flag=0;
  for (int col=0; col<4; col++)
  {
    for (int row=0; row<3; row++)
    {
      if ((piezas.pieceAt(row,col))!=Blank)
      {
        flag++;
      }
    }
  }
  ASSERT_EQ(flag,0);
}

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}
