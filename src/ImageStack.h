/*
	Author: Paul Armstrong
	Date: September 2018
	
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
#include <fstream>

#include "IntVector3.h"

using namespace std;

class ImageStack {
	public:

		// 3D matrix holds image bytes
		vector<vector<vector<char> > > images;
		array<int, 3> dimensions = {0, 0, 0};

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

};

#endif

