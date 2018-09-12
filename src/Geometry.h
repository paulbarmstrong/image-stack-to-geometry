/*
	Author: Paul Armstrong
	Date: August 2018
	
	Description:
		Header file for the Geometry class.

		Geometry is a class which represents a 3D geometry (includes vertices and faces)
*/

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <string>
#include <vector>
#include <array>
#include <map>
#include <fstream>

#include "SetList.h"
#include "IntVector3.h"

using namespace std;

class Geometry {
	private:
		SetList<IntVector3> vertices; // keeps track of coordinates of all vertices
		map<IntVector3, IntVector3> faces; // maps alphabetical face to the actual face
		array<int, 8> vert_indices; // filled with indices of all 8 vertices during add_voxel

		array<IntVector3, 8> LOCAL_VERT_POSITIONS = {{
			IntVector3(0,0,0), IntVector3(0,0,1),
			IntVector3(0,1,0), IntVector3(0,1,1),
			IntVector3(1,0,0), IntVector3(1,0,1),
			IntVector3(1,1,0), IntVector3(1,1,1)
		}};
		array<int, 36> FACE_PLANS = {{
			2,1,0, 1,2,3,
			0,1,4, 1,5,4,
			0,4,2, 2,4,6,
			1,3,5, 3,7,5,
			4,5,6, 5,7,6,
			2,6,3, 6,7,3
		}};

	public:

		// Empty constructor creates an empty Geometry
		Geometry();

		// Add a voxel to the geometry
		void add_voxel(IntVector3 &coordinates);

		// Save the geometry to a file
		void save_to_file(string file_name);
};

#endif

