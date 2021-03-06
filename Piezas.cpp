#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
 **/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
 **/
Piezas::Piezas()
{
  std::vector<Piece> row0(4,Blank);
  std::vector<Piece> row1(4,Blank);
  std::vector<Piece> row2(4,Blank);

  board.push_back(row0);
  board.push_back(row1);
  board.push_back(row2);

  turn=X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
 **/
void Piezas::reset()
{
  for (int col=0; col<4; col++)
  {
    for (int row=0; row<3; row++)
    {
      board[row][col]=Blank;
    }
  }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
 **/ 
Piece Piezas::dropPiece(int column)
{
  Piece returnvalue=Invalid;
  if (column<4 && column>=0)
  {
    int i;
    for (i=0; i<3; i++)
    {
      if (board[i][column]==Blank) //row not empty
      {
        board[i][column]=turn;
        returnvalue=turn;
        break;
      }
    }
    if (i>=3) //row is full
    {
      returnvalue=Blank;
    }
  }
  if (turn==X) //toggle turn
    turn=O;
  else
    turn=X;
  return returnvalue;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
 **/
Piece Piezas::pieceAt(int row, int column)
{
  Piece at_cord=Invalid;
  if (row<3 && row>=0 && column<4 && column>=0)
  {
    at_cord=board[row][column];
  }
  return at_cord;
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
 **/
Piece Piezas::gameState()
{
  Piece winner=Blank;
  int x_cnt=0;
  int o_cnt=0;

  for (int col=0; col<4; col++)
  {
    for (int row=0; row<3; row++)
    {
      if(board[row][col]==Blank)
      {
        winner=Invalid; //game not done
        return winner;
      }
    }
  }

  //only progress if game if finished
  //calculate totals
  //column check
  for (int i=0; i<4; i++)
  {
    if (board[0][i]==board[1][i] && board[0][i]==board[2][i]) //column has matching piece
    {
      if (board[0][i]==X) //increase score for who is matching
        x_cnt++;
      else
        o_cnt++;
    }
  }
  //row check
  for (int i=0; i<3; i++)
  {
    if (board[i][0]==board[i][1] && board[i][2]==board[i][3] && board[i][0]==board[i][2]) //row has matching piece
    {
      if (board[i][0]==X) //increase score
        x_cnt++;
      else
        o_cnt++;
    }
  }

  if (x_cnt==o_cnt)
  {
    winner=Blank;
  }
  else if (x_cnt>o_cnt)
  {
    winner=X;
  }
  else
  {
    winner=O;
  }
  return winner;
}
