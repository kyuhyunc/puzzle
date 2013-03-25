#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

using namespace std;

	/** @mainpage CSCI 102 Homework #3
	 *  @section purpose Purpose/Overview
	 *	  PA3 puzzle game assignment
	 *	 @section requirements Requirements
	 *	  1. STL classes may only be used where explicitly stated \n
	 *	  2. Use Doxygen style comments in all of your classes \n
	 *	  3. Although no points are dedicated to the proper use of git & GitHub, 
	 *		  submissions not following the workflow will be penalized. That includes
	 *		  proper closing of issues on your private tracker. 
	 */
	 
int main(int argc, char *argv[])
{
	if(argc < 4){
		cerr << "Usage: ./puzzle size initMoves seed" << endl;
		return 1;
	}

	int size, initMoves, seed;

	size = atoi(argv[1]);
	initMoves = atoi(argv[2]);
	seed = atoi(argv[3]);

	Board b(size,initMoves,seed);

	//**** Implement the gameplay here
// Milestone 3B test
	/*
	PuzzleMove A(b); // very first time
	
	
	int size_ = b.potentialMoves().size();
	PuzzleMove* B = new PuzzleMove[size_];
	
	for(int i=0;i<size_;i++){
		PuzzleMove B[i]
	}*/
	
// Milestone 3A test	
//	map<int,Board*> BoardMap = b.potentialMoves();
	
	while(b.solved() != true){
		cout << b;
		cout << "Enter tile number to move or -1 for a cheat: ";
		int tile = -1;
		cin >> tile;
//		Board temp = *BoardMap[tile];
//		Board temp(BoardMap[tile]->getTiles(), BoardMap[tile]->getSize());
//		cout << temp;
		b.move(tile);
	}
 
	

	return 0;
}
