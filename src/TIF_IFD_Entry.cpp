/*
	Author: Paul Armstrong
	Date: December 2018
	
	Description:
		Implementation file for the TIF_IFD_Entry class.

		TIF_IFD_Entry is a class which represents one image file directory entry from a TIF file.
*/

#include "TIF_IFD_Entry.h"

using namespace std;

size_t get_size_t_from_bytes(ifstream &file, size_t num_bytes, bool is_big_endian);

// This constructor initializes an ImageStack from an image stack file
TIF_IFD_Entry::TIF_IFD_Entry(ifstream &file, bool is_big_endian) {

	// Record the entry's tag, field size, length, and offset/value
	tag = get_size_t_from_bytes(file, 2, is_big_endian);
	field_size = TIF_FIELD_SIZES.at(get_size_t_from_bytes(file, 2, is_big_endian));
	length = get_size_t_from_bytes(file, 4, is_big_endian);
	offset_or_value = get_size_t_from_bytes(file, 4, is_big_endian);

	// Record the data of the entry
	size_t entry_pos = file.tellg();
	if (field_size * length <= 4) {

		// In this case (entry content fits into 4 bytes), the offset_value IS the data
		size_t temp = offset_or_value;
		for (size_t j = 0; j < length; j++) {
			if (is_big_endian) {
				data.push_back(temp % (8*field_size));
				//data.insert(data.begin(), temp % (8*field_size));
			} else {
				data.push_back(temp % (8*field_size));
			}
			temp /= (8*field_size);
		}
	} else {

		// In this case (entry content does not fit into 4 bytes), the offset_value points to the data
		file.seekg(offset_or_value);
		for (size_t j = 0; j < length; j++) {
			data.push_back(get_size_t_from_bytes(file, field_size, is_big_endian));
		}
	}

	file.seekg(entry_pos);
}

// Helper function to get a size_t from bytes in a file
size_t TIF_IFD_Entry::get_size_t_from_bytes(ifstream &file, size_t num_bytes, bool is_big_endian) {
	size_t sum = 0;
	for (size_t i = 0; i < num_bytes && file.peek() != EOF; i++) {
		sum = sum | (file.get() << (is_big_endian ? (num_bytes - i - 1) : i)*8);
	}
	return sum;
}




