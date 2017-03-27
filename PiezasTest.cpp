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

TEST(PiezasTest, tied)
{
  Piezas piezas;
  /*
   *OOXX
   *OXOX
   *XXOO
   */
  piezas.dropPiece(0); //X
  piezas.dropPiece(3);
  piezas.dropPiece(1); //X
  piezas.dropPiece(2);
  piezas.dropPiece(3); //X
  piezas.dropPiece(0);
  piezas.dropPiece(1); //X
  piezas.dropPiece(2);
  piezas.dropPiece(2); //X
  piezas.dropPiece(1);
  piezas.dropPiece(3); //X
  piezas.dropPiece(0);

  Piece check=piezas.gameState();
  ASSERT_EQ(check,Blank);
}

TEST(PiezasTest, not_done)
{
  Piezas piezas;
  /*
   *X
   *X
   *XOO
   */
  piezas.dropPiece(0);
  piezas.dropPiece(1);
  piezas.dropPiece(0);
  piezas.dropPiece(2);
  piezas.dropPiece(0);

  Piece check=piezas.gameState();
  ASSERT_EQ(check,Invalid);
}

TEST(PiezasTest, O_win)
{
  Piezas piezas;
  /*
   *OOOO
   *XOXX
   *XOXX
   */

  piezas.dropPiece(0); //X
  piezas.dropPiece(1);
  piezas.dropPiece(0); //X
  piezas.dropPiece(1);
  piezas.dropPiece(2); //X
  piezas.dropPiece(1);
  piezas.dropPiece(3); //X
  piezas.dropPiece(0);
  piezas.dropPiece(2); //X
  piezas.dropPiece(2); 
  piezas.dropPiece(3); //X
  piezas.dropPiece(3);

  Piece check=piezas.gameState();

  ASSERT_EQ(O,check);
}

TEST(PiezasTest, X_win)
{
  Piezas piezas;
  /*
   *OOOX
   *OOOX
   *XXXX
   */
  piezas.dropPiece(0); //X
  piezas.dropPiece(0);
  piezas.dropPiece(1); //X
  piezas.dropPiece(0); 
  piezas.dropPiece(2); //X
  piezas.dropPiece(1);
  piezas.dropPiece(3); //X
  piezas.dropPiece(1);
  piezas.dropPiece(3); //X
  piezas.dropPiece(2); 
  piezas.dropPiece(3); //X
  piezas.dropPiece(2);

  Piece check=piezas.gameState();

  ASSERT_EQ(X,check);
}

TEST(PiezasTest, standared_reset)
{
  Piezas piezas;
  piezas.dropPiece(0);
  piezas.dropPiece(3);
  piezas.dropPiece(0);
  piezas.dropPiece(2);
  piezas.dropPiece(0);
  piezas.dropPiece(2);
  piezas.dropPiece(3);

  piezas.reset();

  int flag=0;
  for (int i=0; i<4; i++)
  {
    for (int j=0; j<3; j++)
    {
      if (piezas.pieceAt(j,i)!=Blank)
      {
        flag++;
      }
    }
  }

  ASSERT_EQ(0,flag);
}

TEST(PiezasTest, reset_when_blank)
{
  Piezas piezas;
  piezas.reset();

  int flag=0;
  for (int i=0; i<4; i++)
  {
    for (int j=0; j<3; j++)
    {
      if (piezas.pieceAt(j,i)!=Blank)
      {
        flag++;
      }
    }
  }

  ASSERT_EQ(0,flag);
}

TEST(PiezasTest, check_blank)
{
  Piezas piezas;
  Piece check=piezas.pieceAt(0,0);

  ASSERT_EQ(check,Blank);
}

TEST(PiezasTest, check_out_of_bounds_neg_row)
{
  Piezas piezas;
  Piece check=piezas.pieceAt(-1,3);

  ASSERT_EQ(check,Invalid);
}

TEST(PiezasTest, check_out_of_bounds_neg_col)
{
  Piezas piezas;
  Piece check=piezas.pieceAt(0,-2);

  ASSERT_EQ(check,Invalid);
}

TEST(PiezasTest, check_out_of_bounds_neg_both)
{
  Piezas piezas;
  Piece check=piezas.pieceAt(-1,-4);

  ASSERT_EQ(check,Invalid);
}

TEST(PiezasTest, check_out_of_bounds_pos_row)
{
  Piezas piezas;
  Piece check=piezas.pieceAt(6,2);

  ASSERT_EQ(check,Invalid);
}

TEST(PiezasTest, check_out_of_bounds_pos_col)
{
  Piezas piezas;
  Piece check=piezas.pieceAt(0,4);

  ASSERT_EQ(check,Invalid);
}

TEST(PiezasTest, check_stacked_piece)
{
  Piezas piezas;
  piezas.dropPiece(2);
  piezas.dropPiece(2);
  Piece check=piezas.pieceAt(1,2);

  ASSERT_EQ(check,O);
}

TEST(PiezasTest, check_stacked_piece_elsewhere)
{
  Piezas piezas;
  piezas.dropPiece(0);
  piezas.dropPiece(2);
  piezas.dropPiece(0);
  piezas.dropPiece(3);

  Piece check=piezas.pieceAt(1,0);

  ASSERT_EQ(check,X);
}

TEST(PiezasTest, check_first_placed)
{
  Piezas piezas;
  piezas.dropPiece(3);
  Piece check=piezas.pieceAt(0,3);

  ASSERT_EQ(check,X);
}

TEST(PiezasTest, place_into_invalid_pos)
{
  Piezas piezas;
  Piece check=piezas.dropPiece(4);

  ASSERT_EQ(check,Invalid);
}

TEST(PiezasTest, place_into_invalid_neg)
{
  Piezas piezas;
  Piece check=piezas.dropPiece(-1);

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
