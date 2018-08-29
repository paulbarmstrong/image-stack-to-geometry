/*
	Author: Paul Armstrong
	Date: August 2018
	
	Description:
		IntVector3 is a class which represents a three-dimensional vector of ints
*/

#include "IntVector3.h"

using namespace std;

// Empty constructor leaves x,y,z as garbage values
IntVector3::IntVector3() {}

// Constructor with 3 ints
IntVector3::IntVector3(int newX, int newY, int newZ) {
	x = newX;
	y = newY;
	z = newZ;
}

// Copy constructor
IntVector3::IntVector3(const IntVector3& other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

// Set from another IntVector3
IntVector3& IntVector3::set(IntVector3& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

// Set from 3 ints
IntVector3& IntVector3::set(int newX, int newY, int newZ) {
	x = newX;
	y = newY;
	z = newZ;
	return *this;
}

// Add another IntVector3 to this one
IntVector3& IntVector3::add(IntVector3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

// Subtract another IntVector3 from this one
IntVector3& IntVector3::sub(IntVector3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

// Get a std::vector version of this IntVector3
vector<int> IntVector3::to_std_vector() {
	vector<int> v;
	v.push_back(x);
	v.push_back(y);
	v.push_back(z);
	return v;
}

// Get a std::string version of the IntVector3
string IntVector3::to_string() {
	stringstream ss;
	ss << x << " " << y << " " << z;
	return ss.str();
}

// Sort the x,y,z of the IntVector3
IntVector3& IntVector3::sort() {
	if (x > y) {
		x+=y;y=x-y;x-=y;
	}
	if (y > z) {
		y+=z;z=y-z;y-=z;
	}
	if (x > y) {
		x+=y;y=x-y;x-=y;
	}
	return *this;
}

// Define behavior for the < operator
bool IntVector3::operator<(const IntVector3& other) const {
	if (x != other.x) {
		return x < other.x;
	} else if (y != other.y) {
		return y < other.y;
	} else if (z != other.z) {
		return z < other.z;
	} else {
		return 0;
	}
}

// Overload the << operator with the x,y,z of the IntVector3
ostream& operator<<(ostream& os, IntVector3& v) {
	os << v.x << " " << v.y << " " << v.z;
	return os;
}

