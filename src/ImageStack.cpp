/*
	Author: Paul Armstrong
	Date: September 2018
	
	Description:
		Implementation file for the ImageStack class.

		ImageStack is a class which represents a stack of 2D binary images.
		ImageStacks are immutable.
*/

#include "ImageStack.h"

using namespace std;

// This constructor initializes an ImageStack from an image stack file
ImageStack::ImageStack(string file_name) {

	// Open the fits file and prepare to capture header info and image data
	ifstream file;
	file.open(file_name);
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
				dimensions.at(i) = stoi(temp_text.substr(temp_text.find('=') + 1));
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
	int num_pixels = dimensions.at(0)*dimensions.at(1)*dimensions.at(2);
	image_bytes.reserve(num_pixels);
	for (int i = 0; i < num_pixels; i++) {
		image_bytes.push_back(file.get());
		byte_count++;
	}

	// Close the ifstream
	file.close();
}

// Getter for the number of images in the ImageStack
size_t ImageStack::get_depth() const {
	return dimensions.at(0);
}

// Getter for the width of images in the ImageStack
size_t ImageStack::get_width() const {
	return dimensions.at(1);
}

// Getter for the height of images in the ImageStack
size_t ImageStack::get_height() const {
	return dimensions.at(2);
}

// Getter for the state of the pixel at the depth, width, and height provided
const char& ImageStack::get_pixel(size_t depth, size_t width, size_t height) const {
	return image_bytes.at(dimensions.at(2)*(dimensions.at(1)*depth + width) + height);
}


