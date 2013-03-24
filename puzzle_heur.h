#ifndef PUZZLE_HEUR_H
#define PUZZLE_HEUR_H
#include <iostream>
#include <cstdlib>
#include <cmath>

class PuzzleHeuristic
{
 public:
  virtual int compute(int *tiles, int size) = 0;
};


// Define actual Heuristic Classes here
class ManhattanHeuristic : public PuzzleHeuristic
{
	public:
		int compute(int *tiles, int size);
};

class OutOfPlaceHeuristic : public PuzzleHeuristic
{
	public:
		int compute(int *tiles, int size);
};

#endif
