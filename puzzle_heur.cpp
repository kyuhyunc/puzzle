#include "puzzle_heur.h"

int ManhattanHeuristic::compute(int *tiles, int size)
{
	int h = 0;
	int temp = 0;
	int dim = static_cast<int>(sqrt(size));
	
	for(int i=0;i<size;i++){
		temp = 0;
		if(tiles[i] != i){
			if(tiles[i] != 0){
				temp = abs(tiles[i]-i)/dim;
				temp += abs(tiles[i]-i)%dim;
			}
		}
		h += temp;
	}
	
	return h;
}

int OutOfPlaceHeuristic::compute(int *tiles, int size)
{
	int h = 0;
	
	for(int i=0;i<size;i++){
		if(tiles[i] != i)	h++;
	}
	
	return h;
}
