#include "puzzle_move.h"

// First constructor
PuzzleMove::PuzzleMove(Board &b)
{
	tileMove_ = 0;
	b_ = &b;
	g_ = 0;
//	h_ =
//	f_ = g_ + h_;
	prev_ = NULL;
}

// Constructor for subsequent search boards 
// (i.e. those returned by Board::potentialMoves() )
PuzzleMove::PuzzleMove(int tile, Board *b, PuzzleMove *parent)
{
	tileMove_ = tile;
	b_ = b;
	g_ = parent->g_ + 1;
//	h_ = 
//	f_ = g_ + h_;
	prev_ = parent;
}

PuzzleMove::~PuzzleMove()
{
}

// Compare to PuzzleMoves based on f distance (needed for priority queue)
bool PuzzleMove::operator<(const PuzzleMove& p) const
{
  if((g_ + h_) < (p.g_ + p.h_)){
    return true;
  }
  else if((g_ + h_ == p.g_ + p.h_) && (g_ > p.g_)){
    return true;
  }
  else {
    return false;
  }
}
bool PuzzleMove::operator>(const PuzzleMove& p) const
{
  if( (g_ + h_) > (p.g_ + p.h_) ){
    return true;
  }
  else if((g_ + h_ == p.g_ + p.h_) && (g_ < p.g_) ){
    return true;
  }
  else {
     return false;
  }
  
}

