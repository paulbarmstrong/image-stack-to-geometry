/*
	Author: Paul Armstrong
	Date: September 2018
	
	Description:
		A header file for the ImageStack class.
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

		// Empty constructor creates an empty ImageStack
		ImageStack();

		// This constructor initializes an ImageStack from an image stack file
		ImageStack(string file_name);

};

#endif

