#include "puzzle_move.h"

// First constructor
PuzzleMove::PuzzleMove(Board &b)
{
//	ManhattanHeuristic Man_Heur;
	OutOfPlaceHeuristic Out_Heur;
		
	tileMove_ = 0;
	b_ = &b;
//	b_ = new Board(b);
	g_ = 0;
//	h_ = Man_Heur.compute(b.getTiles(), b.getSize());
	h_ = Out_Heur.compute(b.getTiles(), b.getSize());
	f_ = g_ + h_;
	prev_ = NULL;
}

// Constructor for subsequent search boards 
// (i.e. those returned by Board::potentialMoves() )
PuzzleMove::PuzzleMove(int tile, Board *b, PuzzleMove *parent)
{

//	ManhattanHeuristic Man_Heur;
	OutOfPlaceHeuristic Out_Heur;

	tileMove_ = tile;
	b_ = b;
//	b_ = new Board(*b);
	g_ = parent->g_ + 1;
//	h_ = Man_Heur.compute(b->getTiles(), b->getSize());
	h_ = Out_Heur.compute(b->getTiles(), b->getSize());
	f_ = g_ + h_;
	prev_ = parent;
}

PuzzleMove::~PuzzleMove()
{
//	delete b_;
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

