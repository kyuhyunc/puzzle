#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "puzzle_solver.h"
#include "pmminlist.h"

using namespace std;

PuzzleSolver::PuzzleSolver(const Board &b)
{
	b_ = b;
	expansions_ = 0;
}
PuzzleSolver::~PuzzleSolver()
{
	// deallocate mylist and boardset
//	for(BoardSet::iterator it=BoardSet.begin();it!=slist_.end();++it)
}

//int PuzzleSolver::run(PuzzleHeuristic *ph)
int PuzzleSolver::run()
{
	PMMinList openList;
	BoardSet closeList;

	MyList<PuzzleMove*> garbage;
	map<int,Board*> BoardMap;
		
	int num_moves = 0;
	
	openList.push(new PuzzleMove(b_));
//	closeList.insert(&(b_));
	while(openList.empty() != true){
		PuzzleMove *move = openList.top();
		closeList.insert(move->b_);
		garbage.push_back(move);
		if(move->b_->solved() == true){
			// Trace path back to start
			while(move->prev_ != NULL){
				trace.push_back(move->tileMove_);
			}
			break;
		}

		BoardMap = move->b_->potentialMoves();
		for(std::map<int,Board*>::iterator it=BoardMap.begin();it!=BoardMap.end();++it){
			if(closeList.find(it->second) != closeList.end()){
				closeList.insert(it->second);
				openList.push(new PuzzleMove(it->first,it->second,move));
				expansions_ ++;
			}		
		}
		num_moves ++;
	}
	
	return num_moves;
}


int PuzzleSolver::getNumExpansions()
{
  return expansions_;
}
