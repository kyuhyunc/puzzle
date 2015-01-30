#include "puzzle_move.h"
#include "pmminlist.h"
#include <iostream>

/**
 * Default Constructor
 */
PMMinList::PMMinList() : slist_()
{

}

/**
 * Destructor
 */
PMMinList::~PMMinList()
{
  	//std::cout << "pmminlist destructor" <<   	std::endl;
  	
  	//std::cout << "openList size: " << slist_.size() << std::endl;
  	for(std::list<PuzzleMove*>::iterator it = slist_.begin();it!=slist_.end();++it){
		delete *it;
	}

	slist_.clear();
	
	//std::cout << "openList size: " << slist_.size() << std::endl;
}

/**
 * Adds the value val to the internal list in sorted
 * order from smallest to largest (if 
 * @param val Value to add to the sorted PuzzleMove list
 * @return nothing
 */
void PMMinList::push(PuzzleMove* pm)
{
	std::list<PuzzleMove*>::iterator it = slist_.begin();

	//---- Add your implementation to iterate through the list
	//---- to find the correct location to insert pm and then
	//---- use the insert() method of std::List to insert it
	//---- See http://www.cplusplus.com/reference/list/list/insert/

	for(it=slist_.begin();it!=slist_.end();){
		pm->f_ = (pm->g_) + (pm->h_);
		(*it)->f_ = ((*it)->g_) + ((*it)->h_);
		if(pm->f_ >= (*it)->f_){
			++it;
		}
		else{
			slist_.insert(it,pm);
			break;
		}		
	}

	if(it == slist_.end())
		slist_.push_back(pm);	
}

/**
 * Removes the top (minimum) item
 * @return nothing
 */
void PMMinList::pop()
{
  slist_.pop_front();
}

/**
 * Returns the top (minimum) item
 * @return pointer to the minimum-scored PuzzleMove
 */
PuzzleMove* PMMinList::top()
{
  return slist_.front();
}

