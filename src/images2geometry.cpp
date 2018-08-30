#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <string.h>

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

vector<vector<vector<char> > > parse_fits(string);
void print_images(vector<vector<vector<char> > >);
inline int positive_mod(int, int);
int parse_int(string);

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
	vector<vector<vector<char> > > images = parse_fits(input_file_name);

	// Create a new Geometry and add any pixel which isn't 0 as a voxel
	Geometry geometry;
	for (size_t i = 0; i < images.size(); i++) {
		for (size_t j = 0; j < images.at(i).size(); j++) {
			for (size_t k = 0; k < images.at(i).at(j).size(); k++) {
				if (images.at(i).at(j).at(k) != 0) {
					geometry.add_voxel(IntVector3(i, j, k));
				}
			}
		}
	}
	
	// Save the geometry to a file
	geometry.save_to_file(output_file_name);

	return 0;
}

// Fetch the 3D image stack data from the first HDU of the given fits file location
vector<vector<vector<char> > > parse_fits(string file_name) {

	// Open the fits file and prepare to capture header info and image data
	ifstream file;
	file.open(file_name);
	vector<vector<vector<char> > > images;
	int dimensions[3] = {1, 1, 1};
	int byte_count = 0;
	
	// Read 80 characters at a time to get each phrase of header text
	string temp_text;
	while (file.peek() != EOF && temp_text.substr(0, 3) != "END") {

		// Read the 80 character phrase
		temp_text = "";
		for (int i = 0; i < 80 && file.peek() != EOF; i++) {
			temp_text.push_back(file.get());
			byte_count++;
		}
		
		for (int i = 0; i < 3; i++) {
			if (temp_text.substr(0, 5) == "NAXIS" && temp_text.at(5) - 48 == i + 1) {
				dimensions[i] = parse_int(temp_text.substr(temp_text.find('=') + 1));
			}
		}
	}

	// Skip to the end of the current 2880 byte block (end of metadata)
	int dist_from = positive_mod(-byte_count, 2880);
	for (int i = 0; i < dist_from; i++) {
		file.get();
		byte_count++;
	}

	// Add each byte of data to the images vector
	for (int i = 0; i < dimensions[0]; i++) {
		vector<vector<char> > temp_image;
		for (int j = 0; j < dimensions[1]; j++) {
			vector<char> temp_row;
			for (int k = 0; k < dimensions[2]; k++) {
				temp_row.push_back(file.get());
				byte_count++;
			}
			temp_image.push_back(temp_row);
		}
		images.push_back(temp_image);
	}

	// Close the file and return the data
	file.close();
	return images;

}

// Print the contents of the images
void print_images(vector<vector<vector<char> > > images) {
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

// Parse an int to a string
int parse_int(string str) {
	int num;
	sscanf(str.c_str(), "%d", &num);
	return num;
}

