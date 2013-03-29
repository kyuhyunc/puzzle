#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H
#include <queue>
#include <vector>
#include <deque>
#include <set>
#include "board.h"
#include "puzzle_move.h"
#include "puzzle_heur.h"
#include "mylist.h"
#include "pmminlist.h"

class PuzzleSolver
{
 public:
  /** Typedef for the closed-list set. */
  typedef std::set<Board *, BoardLessThan> BoardSet;

  /** Constructor (makes a copy of the Board and stores it in _b */
  PuzzleSolver(const Board &b);

  /** Destructor */
  ~PuzzleSolver();

  /** Run the A* search returning -1 if no solution exists or
   *  the number of moves in the solution
   *	@param ph Method of calculating h score
   *	@return -1 if no solution, number of move otherwise
   */
  int run(PuzzleHeuristic *ph);
  //int run();

  /** Return the list of solution tile number */
  deque<int> get_solution(); 

  /** Return how many expansions were performed in the search
   * @return Number of expansions
   */
  int getNumExpansions();

 private:
  Board b_;
  int expansions_;
  //**** Declare a List to store your solutions sequence of tiles to move
  //MyList<Board> solution;
  std::deque<int> trace;

  MyList<PuzzleMove*> garbage;
  PMMinList openList;  
  BoardSet closeList;


};

#endif
