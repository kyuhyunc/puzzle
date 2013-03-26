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
	closeList.insert(&(b_));
	while(openList.empty() != true){
		PuzzleMove *move = openList.top();
		openList.pop();
		closeList.insert(move->b_);
		garbage.push_back(move);
		if(move->b_->solved() == true){
			// Trace path back to start
			PuzzleMove *temp = move;
			while(temp->prev_ != NULL){
				trace.push_back(temp->tileMove_);
				temp = temp->prev_;
			//	cout << "1" << endl;
			}
			break;
		}

		BoardMap = move->b_->potentialMoves();
		for(std::map<int,Board*>::iterator it=BoardMap.begin();it!=BoardMap.end();++it){
			if(closeList.find(it->second) == closeList.end()){
				closeList.insert(it->second);
				openList.push(new PuzzleMove(it->first,it->second,move));
				expansions_ ++;
			}		
			//cout << "2" << endl;
		}
		num_moves ++;
		//cout << "3" << endl;
	}
	
	return num_moves;
}

deque<int> PuzzleSolver::get_solution()
{
	return trace;
}

int PuzzleSolver::getNumExpansions()
{
  return expansions_;
}
