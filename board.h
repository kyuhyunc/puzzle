#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <functional>
#include <cmath>

class Board
{
 public:
  /**  Default constructor */
  Board();

  /** Initialize a board of given size and scramble it with numInitMoves 
   * by moving the space tile with a randomly chosen direction N, W, S, E
   * some of which may be invalid, in which case we skip that move */
  Board(int size, int numInitMoves, int seed);

  /** Copy constructor */
  Board(const Board &b);

  /** Another kind of "copy" constructor */
  Board(int *tiles, int size); 

  /** Destructor */
  ~Board();

  /** Swaps the blank with the specified tile */
  void move(int tile);

  /** Generate potential moves and returns new boards \n
   * (Key=tile, Value=Ptr to corresponding Board)
   *	@return Return a set of map that has a key and board data
   */
  std::map<int, Board*> potentialMoves(); 

  /** Returns true if the board is solved, false otherwise
   * @return True or False
   */
  bool solved();

  // Operators
  friend std::ostream& operator<<(std::ostream &os, const Board &b);
  bool operator==(const Board& rhs) const;
  bool operator<(const Board& rhs) const;
  bool operator!=(const Board& rhs) const;
  void operator=(const Board& rhs);
  
  // Accessors
  /** @return Tiles of a board */
  int* getTiles();
  /** @return Size of a board */
  int getSize();
  // Add any accessors

 private:
  int *tiles_;
  int size_;
  // Add Data members

};

// Leave this alone and don't touch it!
struct BoardLessThan : 
  public std::binary_function<const Board*, const Board*,bool>
{
  bool operator()(const Board *b1, const Board *b2) const
  {
    return *b1 < *b2;
  }
};

#endif
