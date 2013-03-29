#include "puzzle_move.h"
#include <iostream>

// Board parameter in constructor will get the address dynamicaly allocated.
// Thus b_ needs to be deallocated in destructor.

// First constructor
PuzzleMove::PuzzleMove(Board &b)
{
//	ManhattanHeuristic Man_Heur;
	OutOfPlaceHeuristic Out_Heur;
		
	tileMove_ = 0;
//	b_ = &b;
	b_ = new Board(b.getTiles(),b.getSize());
	g_ = 0;
//	h_ = Man_Heur.compute(b.getTiles(), b.getSize());
//	h_ = Out_Heur.compute(b.getTiles(), b.getSize());
//	f_ = g_ + h_;
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
//	b_ = new Board(b->getTiles(),b->getSize());
	g_ = parent->g_ + 1;
//	h_ = Man_Heur.compute(b->getTiles(), b->getSize());
//	h_ = Out_Heur.compute(b->getTiles(), b->getSize());
//	f_ = g_ + h_;
//	prev_ = new PuzzleMove(parent->tileMove_, parent->b_, parent->prev_);
	prev_ = parent;
}

PuzzleMove::~PuzzleMove()
{
  	std::cout << "puzzlemove destructor" << std::endl;
	delete b_;
//	delete prev_;
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

