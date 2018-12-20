/*
	Author: Paul Armstrong
	Date: December 2018
	
	Description:
		A header file for the ImageStack class.

		ImageStack is a class which represents a stack of 2D binary images.
		ImageStacks are immutable.
*/

#ifndef IMAGESTACK_H
#define IMAGESTACK_H

#include <string>
#include <vector>
#include <array>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>

#include "IntVector3.h"
#include "TIF_IFD_Entry.h"

using namespace std;

class ImageStack {
	public:

		// Vector of chars used to represent a 3D matrix of image bytes
		vector<char> image_bytes;
		array<size_t, 3> dimensions = {{0, 0, 0}};

		// This constructor initializes an ImageStack from an image stack file
		ImageStack(string file_name);

		// Getter for the number of images in the ImageStack
		size_t get_depth() const;

		// Getter for the width of images in the ImageStack
		size_t get_width() const;

		// Getter for the height of images in the ImageStack
		size_t get_height() const;

		// Getter for the state of the pixel at the depth, width, and height provided
		const char& get_pixel(size_t depth, size_t width, size_t height) const;

		// Function to save the ImageStack to a file
		void save_to_file(string file_name);

		// Helper function to process a tif file's image file directory and return the position of the next ifd
		size_t process_tif_ifd(ifstream &file, size_t ifd_pos, bool is_big_endian);

		// Helper function to get a size_t from bytes in a file
		size_t get_size_t_from_bytes(ifstream &file, size_t num_bytes, bool is_big_endian);

		// Helper function to pad a string
		string pad_string(string str, char ch, size_t target_len);
};

#endif

