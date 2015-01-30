#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

const int DEFAULT_LIST_SIZE = 100;

template <typename T>
class MyList {
	public :
		MyList();
		MyList(int capacity);
		~MyList();
		void push_back(T newval);
		T& at(int loc);		// Q : difference between T& at() and T &at().
		int size() const;		
		bool remove(T val); // If "val" occurs in the list, remove the first
							// occurence of "val" and return true. Return false
							// otherwise
		T pop(int loc);		// remove and return the value at location "loc"
		T& operator[](int loc);
		T max() const; // return maximum valuse
		T min() const; // return minimum valuse
		void pop_back();
	private :
		T *data;
		int size_;
		int capacity_;
};

/** Default constructor 
 * Initialize capacity, size, and date
 */
template <typename T>
MyList<T>::MyList()
{
	capacity_ = DEFAULT_LIST_SIZE;
	size_ = 0;
	data = new T[capacity_];
}

/** Constructor 
 * Initialize capacity, size, and date when capacity is given
 */
template <typename T>
MyList<T>::MyList(int capacity)
{
	capacity_ = capacity;
	size_ = 0;
	data = new T[capacity_];
}

/**  Destructor */
template <typename T>
MyList<T>::~MyList()
{
	delete [] data;
}

/**  Push back new value to the list
 * @param newval New value that will be inserted at the back of list
 * @return Nothing
 */
template <typename T>
void MyList<T>::push_back(T newval)
{
	data[size_] = newval;
	size_++;
		
	// when array is full with data -> double the size of it
	if(size_ == capacity_){
		T *tempData = new T[capacity_];
		for(int i=0;i<capacity_;i++){
			tempData[i] = data[i];
		}
		capacity_ *= 2; // double the size of array
		delete [] data;
		data = new T[capacity_];
		for(int i=0;i<(capacity_/2);i++){
			data[i] = tempData[i];
		}
		delete [] tempData;
	}
}

/**  Return the value at particular location
 * @param loc Loaction number
 * @return Value at the location
 */
// exception : 1. if loc is bigger or smaller than the current size
template <typename T>
T& MyList<T>::at(int loc)
{
	if(loc > (size_-1) || loc < 0) throw out_of_range("Out of range!");
	// if I use 'try' and 'catch' statement inside of this function...
	/*
	try{
		if(loc > (size_-1) || loc < 0) throw out_of_range("Out of range!");
	}
	catch(const std::exception& err){
		cerr<< err.what() << endl;
	}
	*/
	// it won't work unless i use loop statement in order to get the proper range
	// because this function needs to return the proper valuse to the main function
	// if a funtion is void type -> it might be ok

	return data[loc];
}

/**  Return the size of mylist
 *	@return Size of mylist
 */
template <typename T>
int MyList<T>::size() const
{
	return size_;
}

/**  Remove particular value if that value is in the list. \n
 * Return true if that value exist, and false if does not exist.
 * @param val Value that will be deleted if the same value is in the list
 * @return True or False according to the result
 */
template <typename T>
bool MyList<T>::remove(T val)
{
	bool flag = false;
	
	for(int i=0;i<size_;i++){
		if(data[i] == val){
			flag = true;
			pop(i);
		}
	}
	
	return flag;				
}

/** Return the value at particular location and remove it
 * @param loc Location that will be returned and deleted
 * @return Value at entered location
 */
// exception : 1. if loc is bigger than the current size
template <typename T>					
T MyList<T>::pop(int loc)
{
	T temp;
	
	if(loc > (size_-1) || loc < 0) throw out_of_range("Out of range!");
	
	temp = data[loc];
	for(int i=loc;i<size_;i++){
		data[i] = data[i+1];
	}
	size_--;
	
	return temp;
}

/** Operater for [] */
// add "&" in return type as a reference variable -> can make a change as well, instead of just printing
template <typename T>					
T& MyList<T>::operator[](int loc)
{
	return at(loc); // it already has a throw for exception case
}

/** Return the biggest value in the list
 *	@return Maximum value
 */
template <typename T>
T MyList<T>::max() const
{
	T max = data[0];
	for(int i=0;i<size_;i++){
		if(max < data[i])	max = data[i];
	}	
	
	return max;
}

/** Return the smallest value in the list
 *	@return Smallest value
 */
template <typename T>
T MyList<T>::min() const
{
	T min = data[0];
	for(int i=0;i<size_;i++){
		if(min > data[i])	min = data[i];
	}	
	
	return min;
}

/** Delete the most back of list */
template <typename T>
void MyList<T>::pop_back()
{
	pop(size_-1);
}

#endif
