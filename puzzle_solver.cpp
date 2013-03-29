#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "puzzle_solver.h"


using namespace std;

PuzzleSolver::PuzzleSolver(const Board &b)
{
	b_ = b;
	expansions_ = 0;
}
PuzzleSolver::~PuzzleSolver()
{
	// deallocate mylist and boardset
	//for(BoardSet::iterator it=BoardSet.begin();it!=slist_.end();++it)
  	std::cout << "puzzlesolver destructor" << std::endl;
  	// deallocating Boardset which has data of dynamically allocated Boards
  	
	//cout << "closeList size: " << closeList.size() << endl;
	//for(BoardSet::iterator it=closeList.begin();it!=closeList.end();++it){
 	//	delete (*it);
	//}

	//cout << "openList size: " << openList.size() << endl;
	//cout << "closeList size: " << closeList.size() << endl;

  	
  	int size = garbage.size();
  	//cout << "garbage size: " << size << endl;
	for(int i=0;i<size;++i){
  		delete garbage[0];
  		garbage.pop(0);
  	}

  	//cout << "garvage size: " << garbage.size() << endl;
}

int PuzzleSolver::run(PuzzleHeuristic *ph)
//int PuzzleSolver::run()
{
	PMMinList openList;  
   BoardSet closeList;
	
	map<int,Board*> BoardMap;
		
	int num_moves = 0;

	openList.push(new PuzzleMove(b_));
//	closeList.insert(new Board(b_.getTiles(),b_.getSize()));
	
	while(openList.empty() != true){
		PuzzleMove *move = openList.top();
		openList.pop();
		closeList.insert(move->b_); // save board to closeList
		garbage.push_back(move);	// save Puzzlemove to garbage list
		if(move->b_->solved() == true){
			// Trace path back to start
			PuzzleMove *temp = move;
			while(temp->prev_ != NULL){
			//	cout << "g_ : " << temp->g_ << endl;
				trace.push_back(temp->tileMove_);
				temp = temp->prev_;
			//	cout << "1" << endl;
			}

			cout << "openList size: " << openList.size() << endl;
			cout << "closeList size: " << closeList.size() << endl;
			cout << "garbage size: " << garbage.size() << endl;

			cout << "num_moves: " << num_moves << endl;
			return num_moves;
			//break;
		}

		BoardMap = move->b_->potentialMoves(); // Dynamically allocated Boards will be deleted in the closeList
		for(std::map<int,Board*>::iterator it=BoardMap.begin();it!=BoardMap.end();++it){
			if(closeList.find(it->second) == closeList.end()){
				closeList.insert(it->second);
				PuzzleMove *temp = new PuzzleMove(it->first,it->second,move); // this will be deleted in the openList
				temp->h_ = ph->compute(it->second->getTiles(), it->second->getSize()); // computing h score
				//garbage.push_back(temp);
				openList.push(temp);
				expansions_ ++;
			}		
			//cout << "2" << endl;
		}
		//BoardMap.clear();
		
		num_moves ++;
		//cout << "3" << endl;
	}
	
	return -1;
}

deque<int> PuzzleSolver::get_solution()
{
	return trace;
}

int PuzzleSolver::getNumExpansions()
{
  return expansions_;
}
