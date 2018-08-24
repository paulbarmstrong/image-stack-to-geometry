#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

inline int positive_mod(int, int);
int parse_int(string);

int main() {

	// Open the fits file and prepare to capture the header and data contents
	ifstream file;
	file.open("input.fits");
	vector<string> header_phrases;
	vector<vector<vector<int> > > data_bytes;
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
			if (temp_text.substr(0, 6) == "NAXIS"+i) {
				dimensions[i] = parse_int(temp_text.substr(temp_text.find('=') + 1));
			}
		}
		header_phrases.push_back(temp_text);
	}

	// Skip to the end of the current 2880 byte block (end of metadata)
	int dist_from = positive_mod(-byte_count, 2880);
	for (int i = 0; i < dist_from; i++) {
		file.get();
		byte_count++;
	}

	// Add each byte of data to the data_bytes vector
	for (int i = 0; i < dimensions[0]; i++) {
		vector<vector<int> > temp_vector_i;
		for (int j = 0; j < dimensions[1]; j++) {
			vector<int> temp_vector_j;
			for (int k = 0; k < dimensions[2]; k++) {
				temp_vector_j.push_back(file.get());
				byte_count++;
			}
			temp_vector_i.push_back(temp_vector_j);
		}
		data_bytes.push_back(temp_vector_i);
	}
	
	// Print out the collected data
	cout << "header phrases:\n";
	for (int i = 0; i < header_phrases.size(); i++) {
		cout << header_phrases.at(i) << "\n";
	}
	cout << "data bytes:\n";
	for (int i = 0; i < data_bytes.size(); i++) {
		for (int j = 0; j < data_bytes.at(i).size(); j++) {
			for (int k = 0; k < data_bytes.at(i).at(j).size(); k++) {
				cout << data_bytes.at(i).at(j).at(k) << ", ";
			}
			cout << "\n";
		}
		cout << "\n";
	}
	cout << "\n";

	return 0;
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

