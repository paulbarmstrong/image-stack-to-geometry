/*
	Author: Paul Armstrong
	Date: December 2018
	
	Description:
		Implementation file for the ImageStack class.

		ImageStack is a class which represents a stack of 2D binary images.
		ImageStacks are immutable.
*/

#include "ImageStack.h"

using namespace std;

// This constructor initializes an ImageStack from an image stack file
ImageStack::ImageStack(string file_name) {

	ifstream file;
	file.open(file_name);
	string file_extension = file_name.substr(file_name.find('.'));
	
	// If it is a fits file, parse the metadata and store the images' pixels
	if (file_extension.compare(".fits") == 0) {
		
		// Read 80 characters at a time to get each phrase of header text
		string temp_text;
		while (file.peek() != EOF && temp_text.substr(0, 3) != "END") {

			// Read the 80 character phrase
			temp_text = "";
			for (size_t i = 0; i < 80 && file.peek() != EOF; i++) {
				temp_text.push_back(file.get());
			}
			
			for (int i = 0; i < 3; i++) {
				if (temp_text.substr(0, 5) == "NAXIS" && temp_text.at(5) - 48 == i + 1) {
					dimensions.at(i) = stoi(temp_text.substr(temp_text.find('=') + 1));
				}
			}
		}

		// Skip to the end of the current 2880 byte block (end of metadata)
		file.ignore((-file.tellg() % 2880 + 2880) % 2880);

		// Add each byte of data to the images vector
		size_t num_pixels = dimensions.at(0)*dimensions.at(1)*dimensions.at(2);
		image_bytes.reserve(num_pixels);
		for (size_t i = 0; i < num_pixels; i++) {
			image_bytes.push_back(file.get());
		}
	} else if (file_extension.compare(".tif") == 0) {

		// The first two bytes give the endian-ness (MM for big endian, II for little endian)
		string endian_str = "";
		endian_str.push_back(file.get()); endian_str.push_back(file.get());
		bool is_big_endian = (endian_str == "MM");

		// The next two bytes should be 42 (This will verify the endianness is correct)
		bool correct42 = get_size_t_from_bytes(file, 2, is_big_endian) == 42;

		if (correct42) {

			// Get the location of the first image file directory
			size_t ifd_pos = get_size_t_from_bytes(file, 4, is_big_endian);
			
			// Process the image file directories
			while (ifd_pos != 0) {
				ifd_pos = process_tif_ifd(file, ifd_pos, is_big_endian);
			}
		}
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

// Function to save the ImageStack to a file
void ImageStack::save_to_file(string file_name) {
	ofstream file;
	file.open(file_name);
	string file_extension = file_name.substr(file_name.find('.'));
	
	if (file_extension.compare(".fits") == 0) {

		// Provide the header metadata
		file << pad_string("SIMPLE = T / file conforms to the FITS standard", ' ', 80);
		file << pad_string("BITPIX = 8 / 8 bits per value", ' ', 80);
		file << pad_string("NAXIS = 3 / number of axes", ' ', 80);
		stringstream stream;
		stream << "NAXIS1 = " << dimensions.at(0) << " / number of images";
		file << pad_string(stream.str(), ' ', 80);
		stream.str("");
		stream << "NAXIS2 = " << dimensions.at(1) << " / number of images";
		file << pad_string(stream.str(), ' ', 80);
		stream.str("");
		stream << "NAXIS3 = " << dimensions.at(2) << " / number of images";
		file << pad_string(stream.str(), ' ', 80);
		file << pad_string("EXTEND  = T / extensions are permitted", ' ', 80);
		file << pad_string("END", ' ', 80);
		file.seekp(2880);
		
		// Provide the data
		for (size_t i = 0; i < image_bytes.size(); i++) {
			file << image_bytes.at(i);
		}
	}
	file.close();
}

// Helper function to process a tif file's image file directory and return the position of the next ifd
size_t ImageStack::process_tif_ifd(ifstream &file, size_t ifd_pos, bool is_big_endian) {

	file.seekg(ifd_pos);
	size_t num_entries = get_size_t_from_bytes(file, 2, is_big_endian);
	dimensions.at(0)++;

	// Record all of the entries
	vector<TIF_IFD_Entry> entries;
	for (size_t i = 0; i < num_entries; i++) {
		TIF_IFD_Entry new_entry(file, is_big_endian);
		entries.push_back(new_entry);
	}

	size_t end_pos = file.tellg();

	//size_t rows_per_strip;
	vector<size_t> strip_offsets;
	vector<size_t> strip_byte_counts;
	
	// Extract image width, height, and strip information
	for (size_t i = 0; i < num_entries; i++) {
		if (entries.at(i).tag == 256 && entries.at(i).data.size() == 1) {
			dimensions.at(1) = entries.at(i).data.at(0);
		} else if (entries.at(i).tag == 257 && entries.at(i).data.size() == 1) {
			dimensions.at(2) = entries.at(i).data.at(0);
		} else if (entries.at(i).tag == 278 && entries.at(i).data.size() == 1) {
		//	rows_per_strip = entries.at(i).data.at(0);
		} else if (entries.at(i).tag == 273) {
			strip_offsets = entries.at(i).data;
		} else if (entries.at(i).tag == 279) {
			strip_byte_counts = entries.at(i).data;
		}
	}

	// Process the strips
	for (size_t i = 0; i < strip_offsets.size(); i++) {
		file.seekg(strip_offsets.at(i));
		for (size_t j = 0; j < strip_byte_counts.at(i) && image_bytes.size() < dimensions.at(0) * dimensions.at(1) * dimensions.at(2); j++) {
			image_bytes.push_back(file.get());
		}
	}
	while (image_bytes.size() < dimensions.at(0) * dimensions.at(1) * dimensions.at(2)) {
		image_bytes.push_back(0);
	}

	// Move back to the position of the end of the IFD, and return the pointer to the next IFD
	file.seekg(end_pos);
	return get_size_t_from_bytes(file, 4, true);
}

// Helper function to get a size_t from bytes in a file
size_t ImageStack::get_size_t_from_bytes(ifstream &file, size_t num_bytes, bool is_big_endian) {
	size_t sum = 0;
	for (size_t i = 0; i < num_bytes && file.peek() != EOF; i++) {
		sum = sum | (file.get() << (is_big_endian ? (num_bytes - i - 1) : i)*8);
	}
	return sum;
}

// Helper function to pad a string
string ImageStack::pad_string(string str, char ch, size_t target_len) {
	while (str.size() < target_len) {
		str.push_back(ch);
	}
	return str;
}


