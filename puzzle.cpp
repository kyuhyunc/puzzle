#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "pmminlist.h"

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


// Milestone 3C test	
	Board temp;
//	temp = b;
	
	PuzzleSolver cheat(b);
	
	while(b.solved() != true){
		cout << b;
		cout << "Enter tile number to move or -1 for a cheat: ";
		int tile = -1;
		cin >> tile;
		if(tile == -1){
			cheat.run();
		}
		else
			b.move(tile);
	}


/*
// Milestone 3B test
	PuzzleMove *a1 = new PuzzleMove(b); // very first time
	PuzzleMove *a2 = new PuzzleMove(2,a1->b_,a1);
	PuzzleMove *a3 = new PuzzleMove(3,a1->b_,a1);
	PuzzleMove *a4 = new PuzzleMove(4,a2->b_,a2);
	PuzzleMove *a5 = new PuzzleMove(5,a2->b_,a2);
	PuzzleMove *a6 = new PuzzleMove(6,a5->b_,a5);
	
	PMMinList OpenList;
	
	OpenList.push(a1);
	OpenList.push(a2);
	OpenList.push(a3);
	OpenList.push(a4);
	OpenList.push(a5);
	OpenList.push(a6);

	int listSize = OpenList.size();
	
	for(int i=0;i<listSize;i++){
		PuzzleMove *temp = OpenList.top();
		cout << temp->f_ << endl;
		OpenList.pop();
	}	
*/
	
/*
// Milestone 3A test
//	map<int,Board*> BoardMap = b.potentialMoves();
	
	while(b.solved() != true){
		cout << b;
		cout << "Enter tile number to move or -1 for a cheat: ";
		int tile = -1;
		cin >> tile;
//		Board temp = *BoardMap[tile];
//		cout << temp;
		b.move(tile);
	}
*/
	

	return 0;
}
