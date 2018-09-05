/*
	Author: Paul Armstrong
	Date: September 2018
	
	Description:
		ImageStack is a class which represents a stack of 2D binary images
*/

#include "ImageStack.h"

using namespace std;

// Empty constructor creates an empty ImageStack
ImageStack::ImageStack() {}

// This constructor initializes an ImageStack from an image stack file
ImageStack::ImageStack(string file_name) {

	// Open the fits file and prepare to capture header info and image data
	ifstream file;
	file.open(file_name);
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
				dimensions[i] = stoi(temp_text.substr(temp_text.find('=') + 1));
			}
		}
	}

	// Skip to the end of the current 2880 byte block (end of metadata)
	int dist_from = (-byte_count % 2880 + 2880) % 2880;
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

	// Close the ifstream
	file.close();
}

