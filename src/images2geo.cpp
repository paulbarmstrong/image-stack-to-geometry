#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <math.h>
#include <string.h>

#include "ImageStack.h"
#include "Geometry.h"
#include "IntVector3.h"
#include "SetList.h"

using namespace std;

/*
	Author: Paul Armstrong
	Date: August 2018
	
	Description:
		Main file for the image-stack-to-geometry project
*/

int main(int argc, char * argv[]) {
	
	// Return if the input is invalid
	if (argc < 3) {
		cerr << "Error: Insufficient file arguments provided.\n";
		return 1;
	}	
	string input_file_name = argv[1];
	string input_file_ext = input_file_name.substr(input_file_name.find('.'));
	if (input_file_ext.compare(".fits") != 0) {
		cerr << "Error: Invalid input file format provided.\n";
		return 1;
	}
	string output_file_name = argv[2];
	string output_file_ext = output_file_name.substr(output_file_name.find('.'));
	if (output_file_ext.compare(".obj") != 0) {
		cerr << "Error: Invalid output file format provided.\n";
		return 1;
	}
	
	// Get a matrix of the images' bytes
	ImageStack image_stack(input_file_name);

	// Create a new Geometry from the image stack
	Geometry geometry;

	// Go through each pixel in the image stack
	for (size_t i = 0; i < image_stack.get_depth(); i++) {
		for (size_t j = 0; j < image_stack.get_width(); j++) {
			for (size_t k = 0; k < image_stack.get_height(); k++) {

				// If the pixel is turned on, add it to the geometry as a voxel
				if (image_stack.get_pixel(i, j, k) != 0) {
					IntVector3 voxel_coords(i, j, k);
					geometry.add_voxel(voxel_coords);
				}
			}
		}
	}
	
	// Save the geometry to a file
	geometry.save_to_file(output_file_name);

	return 0;
}


