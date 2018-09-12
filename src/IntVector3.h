/*
	Author: Paul Armstrong
	Date: August 2018
	
	Description:
		Header file for the IntVector3 class

		IntVector3 is a class which represents a three-dimensional vector of ints
*/

#ifndef INTVECTOR3_H
#define INTVECTOR3_H

#include <sstream>
#include <string>
#include <vector>

using namespace std;

class IntVector3 {
	public:
		int x, y, z;

		// Empty constructor leaves x,y,z as garbage values
		IntVector3();

		// Constructor with 3 ints
		IntVector3(int newX, int newY, int newZ);

		// Copy constructor
		IntVector3(const IntVector3& other);

		// Set from another IntVector3
		IntVector3& set(IntVector3& other);
		
		// Set from 3 ints
		IntVector3& set(int newX, int newY, int newZ);
	
		// Add another IntVector3 to this one
		IntVector3& add(IntVector3& other);

		// Subtract another IntVector3 from this one
		IntVector3& sub(IntVector3& other);

		// Get a std::vector version of this IntVector3
		vector<int> to_std_vector();

		// Get a std::string version of the IntVector3
		string to_string();

		// Sort the x,y,z of the IntVector3
		IntVector3& sort();

		// Define behavior for the < operator
		bool operator<(const IntVector3&) const;

		// Overload the << operator with the x,y,z of the IntVector3
		friend ostream& operator<<(ostream& os, IntVector3& v);
};

#endif


