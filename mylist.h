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

template <typename T>
MyList<T>::MyList()
{
	capacity_ = DEFAULT_LIST_SIZE;
	size_ = 0;
	data = new T[capacity_];
}

template <typename T>
MyList<T>::MyList(int capacity)
{
	capacity_ = capacity;
	size_ = 0;
	data = new T[capacity_];
}

template <typename T>
MyList<T>::~MyList()
{
	delete [] data;
}

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

template <typename T>
int MyList<T>::size() const
{
	return size_;
}

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

// add "&" in return type as a reference variable -> can make a change as well, instead of just printing
template <typename T>					
T& MyList<T>::operator[](int loc)
{
	return at(loc); // it already has a throw for exception case
}

template <typename T>
T MyList<T>::max() const
{
	T max = data[0];
	for(int i=0;i<size_;i++){
		if(max < data[i])	max = data[i];
	}	
	
	return max;
}

template <typename T>
T MyList<T>::min() const
{
	T min = data[0];
	for(int i=0;i<size_;i++){
		if(min > data[i])	min = data[i];
	}	
	
	return min;
}

template <typename T>
void MyList<T>::pop_back()
{
	pop(size_-1);
}

#endif
