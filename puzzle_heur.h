#ifndef PUZZLE_HEUR_H
#define PUZZLE_HEUR_H
#include <iostream>
#include <cstdlib>
#include <cmath>

class PuzzleHeuristic
{
 public:
	/**  Compute h score either by manhattan heuristic or out-of-place heuristic \n
	 * Virtual function for the compute
	 *	@param tiles Tiles of right hand side board class
	 *	@param size Size of right hand side board class
	 *	@return Computed h score
	 */
  virtual int compute(int *tiles, int size) = 0;
};


// Define actual Heuristic Classes here
class ManhattanHeuristic : public PuzzleHeuristic
{
	public:
	  /**  Compute h score by using manhattan heuristic 
	   *	@param tiles Tiles of right hand side board class
		*	@param size Size of right hand side board class
		*	@return Computed h score
		*/
		int compute(int *tiles, int size);
};

class OutOfPlaceHeuristic : public PuzzleHeuristic
{
	public:
		/**  Compute h score by using out-of-place heuristic
	   *	@param tiles Tiles of right hand side board class
		*	@param size Size of right hand side board class
		*	@return Computed h score
		*/
		int compute(int *tiles, int size);
};

#endif
