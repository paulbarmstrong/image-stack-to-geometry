/*
	Author: Paul Armstrong
	Date: August 2018
	
	Description:
		Header file for the SetList class
*/

#ifndef SETLIST_H
#define SETLIST_H

#include <vector>
#include <map>

using namespace std;

template<typename T>
class SetList {
	public:
		map<T, int> index_map;
		vector<T> list;

		// Adds data to the list if not already in the list.
		// Returns the index of the data in the list.
		int add(T data);
		
		// Removes the data at this given index.
		void remove_at(int index);
		
		// Gets the data at the given index.
		T& at(int index);

		// Check whether or not the given data is in the SetList.
		bool contains(T data);

		// Checks the index of the data in the list.
		int index_of(T data);

		// Returns the size of the SetList
		int size();
};

// Include the tpp file to include the implementations
// (otherwise problem with compiling implementation separately because of the templating)
#include "SetList.tpp"

#endif

