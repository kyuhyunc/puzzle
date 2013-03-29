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
  	std::cout << "puzzlesolver destructor" << std::endl;
}

int PuzzleSolver::run(PuzzleHeuristic *ph)
//int PuzzleSolver::run()
{
	PMMinList openList;
	BoardSet closeList;

	MyList<PuzzleMove*> garbage;
	map<int,Board*> BoardMap;
		
	int num_moves = 0;
	
	//b_.h_ = *ph(b_.getTiles(), b_.getSize());
	
	openList.push(new PuzzleMove(b_));
	closeList.insert(&(b_));
	while(openList.empty() != true){
		PuzzleMove *move = openList.top();
		openList.pop();
		closeList.insert(move->b_); // save board to closeList
		garbage.push_back(move);	// save Puzzlemove to garbage list
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
				PuzzleMove *temp = new PuzzleMove(it->first,it->second,move);
				temp->h_ = ph->compute(it->second->getTiles(), it->second->getSize());
				openList.push(temp);
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
