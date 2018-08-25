#include <sstream>
#include <string>

using namespace std;

/*
	Author: Paul Armstrong
	Date: August 2018
	
	Description:
		Class which represents a three-dimensional vector of ints
*/

class IntVector3 {
	public:
		int x, y, z;

		// Empty constructor leaves x,y,z as garbage values
		IntVector3() {}

		// Constructor with 3 ints
		IntVector3(int newX, int newY, int newZ) {
			x = newX;
			y = newY;
			z = newZ;
		}

		// Copy constructor
		IntVector3(const IntVector3& other) {
			x = other.x;
			y = other.y;
			z = other.z;
		}

		// Set from another IntVector3
		IntVector3& set(IntVector3& other) {
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}
		
		// Set from 3 ints
		IntVector3& set(int newX, int newY, int newZ) {
			x = newX;
			y = newY;
			z = newZ;
			return *this;
		}
	
		// Add another IntVector3 to this one
		IntVector3& add(IntVector3& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		// Subtract another IntVector3 from this one
		IntVector3& sub(IntVector3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		// Get a std::vector version of this IntVector3
		vector<int> to_std_vector() {
			vector<int> v;
			v.push_back(x);
			v.push_back(y);
			v.push_back(z);
			return v;
		}

		// Define behavior for the < operator
		bool operator <(const IntVector3& other) const {
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
		friend ostream& operator <<(ostream& os, IntVector3& v) {
			os << v.x << " " << v.y << " " << v.z;
			return os;
		}

		// Get a std::string version of the IntVector3
		string to_string() {
			stringstream ss;
			ss << x << " " << y << " " << z;
			return ss.str();
		}

		// Sort the x,y,z of the IntVector3
		IntVector3& sort() {
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
};


