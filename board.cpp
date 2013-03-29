#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include "board.h"
using namespace std;

/** Default constructor. provide documentation here */
Board::Board()
{
  //size_ = 9;
  //tiles_ = new int[size_];
}

/**  
 *  @param size Number of tiles for the game.  \
 *      Should be a perfect square (4, 16, 25)
 *  @param numInitMoves Number of tile moves to attempt to scramble the board
 *  @param seed Use to seed the random number generator (srand) 
 */
Board::Board(int size, int numInitMoves, int seed)
{
	size_ = size;
	tiles_ = new int[size_];
	int dim = static_cast<int>(sqrt(size_));
	srand(seed);
	// Filling puzzle with numbers
	for(int i=0; i < size_; i++){
		tiles_[i] = i;
	}
	int blankLoc = 0;
	// Scrambling puzzle by random variable. 0:N, 1:W, 2:S, 3:E
	for(int i=0; i < numInitMoves; i++){
		int r = rand()%4;
		int randNeighbor = -1;
		if(r == 0){
			int n = blankLoc - dim;
			if(n >= 0){
				randNeighbor = n;
			}
		}
		else if(r == 1){
			int w = blankLoc - 1;
			if(blankLoc % dim != 0){
				randNeighbor = w;
			}
		}
		else if(r == 2){
			int s = blankLoc + dim;
			if(s  < size_){
				randNeighbor = s;
			}
		}
		else {
			int e = blankLoc + 1;
			if(blankLoc % dim != dim-1){
				randNeighbor = e;
			}
		}
		if(randNeighbor > -1){
			tiles_[blankLoc] = tiles_[randNeighbor];
			tiles_[randNeighbor] = 0;
			blankLoc = randNeighbor;
		}
	}
}

/** Using deep copy for copying game board
 *	@param b Right hand side board class
 */
Board::Board(const Board &b)
{
	tiles_ = new int[size_];
	size_ = b.size_;
	for(int i=0;i<size_;i++){
		tiles_[i] = b.tiles_[i];
	}	
}

/** Using deep copy for copying game board
 *	@param tiles Tiles of right hand side board class
 *	@param size Size of right hand side board class
 */
Board::Board(int *tiles, int size)
{
	tiles_ = new int[size];
	size_ = size;
	for(int i=0;i<size;i++){
		tiles_[i] = tiles[i];
	}
}

/** Delete dynamically allocated board tiles */
Board::~Board()
{
  /*
   * IMPLEMENT ME
  */
  	cout << "board.h destructor" << endl;
	//delete [] tiles_;
}

/** @param tile Value of one tile for moving to blank location	
 *	 @return Nothing
 */
void Board::move(int tile){
	int blankloc = -1;
	int tileloc = -1;
	int dim = static_cast<int>(sqrt(size_));
	
	for(int i=0;i<size_;i++){
		if(tiles_[i] == 0){
			blankloc = i;
		}
	}
	
	for(int i=0;i<size_;i++){
		if(tiles_[i] == tile){
			tileloc = i;
		}
	}

	if(blankloc+1==tileloc || blankloc-1==tileloc || blankloc-dim==tileloc || blankloc+dim==tileloc){
		tiles_[blankloc] = tiles_[tileloc];
		tiles_[tileloc] = 0;
	}
	else
		cout << "Improper tile value" << endl;
}

std::map<int, Board*> Board::potentialMoves()
{
	int blankloc = -1;
	int dim = static_cast<int>(sqrt(size_));
	map<int, Board*> BoardList;
	
	for(int i=0;i<size_;i++){
		if(tiles_[i] == 0){
			blankloc = i;
		}
	}
	
	// Q : When and how should I delete heap memory?
	// If north tile exists
	if(blankloc - dim >= 0){
		int temp_tiles[size_];
		for(int i=0;i<size_;i++){
			temp_tiles[i] = tiles_[i];
		}		
		temp_tiles[blankloc] = temp_tiles[blankloc-dim];
		temp_tiles[blankloc-dim] = 0;
		Board* potential_Board = new Board(temp_tiles, size_);
		BoardList[temp_tiles[blankloc]] = potential_Board;
	}
	// If west tile exists
	if(blankloc % dim != 0){
		int temp_tiles[size_];
		for(int i=0;i<size_;i++){
			temp_tiles[i] = tiles_[i];
		}		
		temp_tiles[blankloc] = temp_tiles[blankloc-1];
		temp_tiles[blankloc-1] = 0;
		Board* potential_Board = new Board(temp_tiles, size_);
		BoardList[temp_tiles[blankloc]] = potential_Board;
	}
	// If south tile exists
	if(blankloc + dim <= size_){
		int temp_tiles[size_];
		for(int i=0;i<size_;i++){
			temp_tiles[i] = tiles_[i];
		}		
		temp_tiles[blankloc] = temp_tiles[blankloc+dim];
		temp_tiles[blankloc+dim] = 0;
		Board* potential_Board = new Board(temp_tiles, size_);
		BoardList[temp_tiles[blankloc]] = potential_Board;
	}
	// If east tile exists
	if(blankloc % dim != dim-1){
		int temp_tiles[size_];
		for(int i=0;i<size_;i++){
			temp_tiles[i] = tiles_[i];
		}		
		temp_tiles[blankloc] = temp_tiles[blankloc+1];
		temp_tiles[blankloc+1] = 0;
		Board* potential_Board = new Board(temp_tiles, size_);
		BoardList[temp_tiles[blankloc]] = potential_Board;
	}
	
	return BoardList;			
}

bool Board::solved()
{
	int flag = 0;
	for(int i=0;i<size_;i++){
		if(tiles_[i] != i)
			flag = 1;
	}
	
	if(flag == 1)
		return false;
	else
		return true;
}

// Operators
std::ostream& operator<<(std::ostream &os, const Board &b)
{
	int line = 0;
//	int size = b.getSize();
	int dim = static_cast<int>(sqrt(b.size_));
//	int *tiles = b.getTiles();

	for(int i=0;i<b.size_;i++){
		if(b.size_ < 10)
			os << setw(2);
		else if(b.size_ >= 10 && b.size_ <= 100)
			os << setw(3);
		else if(b.size_ > 100)
			os << setw(4);
	
		if(b.tiles_[i] == 0)
			os << " ";
		else
			os << b.tiles_[i];
		
		line ++;
		if(line == dim){
			os << endl;
			line = 0;
		}
	}
	
	return os;
}

bool Board::operator==(const Board& rhs) const
{
	int flag = 0;
	for(int i=0;i<size_;i++){
		if(tiles_[i] != rhs.tiles_[i])
			flag = 1;
	}
	
	if(flag == 0)
		return true;
	else
		return false;		
}

bool Board::operator<(const Board& rhs) const
{
	if(size_ < rhs.size_){
		return true;
	}
	bool val = false;
	for(int i=0; i < size_; i++){
		if(tiles_[i] < rhs.tiles_[i]){
			//val = true;
			//break;
			return true;
		}
		else if(tiles_[i] > rhs.tiles_[i]){
			//break;
			return false;
		}
	}
	return val;
}

bool Board::operator!=(const Board& rhs) const
{
	int flag = 0;
	for(int i=0;i<size_;i++){
		if(tiles_[i] != rhs.tiles_[i])
			flag = 1;
	}
	
	if(flag == 0)
		return false;
	else
		return true;			
}

void Board::operator=(const Board& rhs)
{
	size_ = rhs.size_;
	tiles_ = new int[size_];
	
	for(int i=0;i<size_;i++){
		tiles_[i] = rhs.tiles_[i];
	}
}

// Accessors
int* Board::getTiles()
{
	return tiles_;
}

int Board::getSize()
{
	return size_;
}


