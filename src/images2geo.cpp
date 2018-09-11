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

void print_images(vector<vector<vector<char> > >);
inline int positive_mod(int, int);

int main(int argc, char * argv[]) {
	
	// Return if the input is invalid
	if (argc < 3) {
		cerr << "Error: Insufficient file arguments provided.\n";
		return 1;
	}	
	string input_file_name = argv[1];
	if (input_file_name.substr(input_file_name.find('.')).compare(".fits") != 0) {
		cerr << "Error: Invalid input file format provided.\n";
		return 1;
	}
	string output_file_name = argv[2];
	if (output_file_name.substr(output_file_name.find('.')).compare(".obj") != 0) {
		cerr << "Error: Invalid output file format provided.\n";
		return 1;
	}
	
	// Get a matrix of the images' bytes
	ImageStack image_stack(input_file_name);

	// Create a new Geometry from the image stack
	Geometry geometry;
	geometry.add_image_stack(image_stack);
	
	// Save the geometry to a file
	geometry.save_to_file(output_file_name);

	return 0;
}

// Print the contents of the images
void print_images(vector<vector<vector<char> > > &images) {
	cout << "images:\n";
	for (size_t i = 0; i < images.size(); i++) {
		for (size_t j = 0; j < images.at(i).size(); j++) {
			for (size_t k = 0; k < images.at(i).at(j).size(); k++) {
				cout << (images.at(i).at(j).at(k) == 0 ? "0" : "1");
			}
			cout << "\n";
		}
		cout << "\n";
	}
	cout << "\n";
}

// Get the (a mod b) between 0 and b-1
inline int positive_mod(int a, int b) {
	return ((a % b + b) % b);
}

