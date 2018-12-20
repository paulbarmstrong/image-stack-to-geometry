/*
	Author: Paul Armstrong
	Date: December 2018
	
	Description:
		A header file for the TIF_IFD_Entry class.

		TIF_IFD_Entry is a class which represents one image file directory entry from a TIF file.
*/

#ifndef TIF_IFD_ENTRY_H
#define TIF_IFD_ENTRY_H

#include <string>
#include <vector>
#include <array>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

class TIF_IFD_Entry {
	public:

		// Array maps the tif field type number to its size in bytes
		array<size_t, 6> TIF_FIELD_SIZES = {{0, 1, 1, 2, 4, 8}};

		// The tag, field_size, length, offset/value, and data of the TIF_IFD_Entry
		size_t tag;
		size_t field_size;
		size_t length;
		size_t offset_or_value;
		vector<size_t> data;

		// This constructor initializes a TIF_IFD_Entry.
		// It is provided an ifstream parsing a TIF file, and the endianness
		TIF_IFD_Entry(ifstream &file, bool is_big_endian);

		// Helper function to get a size_t from bytes in a file
		size_t get_size_t_from_bytes(ifstream &file, size_t num_bytes, bool is_big_endian);
};

#endif
