#include <string>
#include <vector>
#include <map>
#include "IntVector3.cpp"
#include "SetList.cpp"

using namespace std;

/*
	Author: Paul Armstrong
	Date: August 2018
	
	Description:
		A class which represents a geometry (includes vertices and faces)
*/

class Geometry {
	private:
		SetList<IntVector3> vertices; // keeps track of coordinates of all vertices
		map<IntVector3, IntVector3> faces; // maps alphabetical face to the actual face
		int vert_indices[8]; // filled with indices of all 8 vertices during add_voxel

		const IntVector3 LOCAL_VERT_POSITIONS[8] = {
			IntVector3(0,0,0), IntVector3(0,0,1),
			IntVector3(0,1,0), IntVector3(0,1,1),
			IntVector3(1,0,0), IntVector3(1,0,1),
			IntVector3(1,1,0), IntVector3(1,1,1)
		};
		const int FACE_PLANS[12][3] = {
			{2,1,0}, {1,2,3},
			{0,1,4}, {1,5,4},
			{0,4,2}, {2,4,6},
			{1,3,5}, {3,7,5},
			{4,5,6}, {5,7,6},
			{2,6,3}, {6,7,3}
		};

	public:
		
		void add_voxel(IntVector3 coordinates) {

			// Make sure all 8 of the new voxel's vertices are in the vertices SetList.
			// Keep an array of the indices of them to use when creating faces.
			for (int i = 0; i < 8; i++) {
				IntVector3 vertex(LOCAL_VERT_POSITIONS[i]);
				vert_indices[i] = vertices.add(vertex.add(coordinates));
			}

			// Go through the 12 faces (2 on each side of the voxel)
			for (int i = 0; i < 12; i++) {

				// Create the new face
				IntVector3 new_face(
					vert_indices[FACE_PLANS[i][0]],
					vert_indices[FACE_PLANS[i][1]],
					vert_indices[FACE_PLANS[i][2]]
				);

				// Create an alphabetical version of the face
				IntVector3 sorted_face(new_face);
				sorted_face.sort();
				
				// If the face is already in the map, remove it
				if (faces.count(sorted_face)) {
					faces.erase(sorted_face);

				// If the face isn't there, add it
				} else {
					faces.insert(pair<IntVector3,IntVector3>(sorted_face, new_face));
				}
			}
		}
		void save_to_file(string file_name) {
			ofstream file;
			file.open(file_name);
			
			// For a .obj file, just print the vertices and faces
			if (file_name.substr(file_name.find('.')).compare(".obj") == 0) {
				
				for (int i = 0; i < vertices.size(); i++) {
					file << "v " << vertices.at(i) << "\n";
				}
				for (map<IntVector3,IntVector3>::iterator it = faces.begin(); it != faces.end(); ++it) {
					file << "f " << IntVector3(1,1,1).add(it->second) << "\n";
				}
			}
			file.close();
		}
};

