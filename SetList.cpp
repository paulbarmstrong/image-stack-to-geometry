#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

/*
	Author: Paul Armstrong
	Date: August 2018
	
	Description:
		A list-like structure which can have no duplicate entries.
*/

template<typename T>
class SetList {
	public:
		map<T, int> index_map;
		vector<T> list;
		
		// Adds data to the list if not already in the list.
		// Returns the index of the data in the list.
		int add(T data) {
			if (!index_map.count(data)) {
				index_map.insert(pair<T,int>(data, list.size()));
				list.push_back(data);
				return list.size()-1;
			} else {
				return index_map.at(data);
			}
		}
		
		// Removes the data at this given index.
		void remove_at(int index) {
			index_map.erase(list.at(index));
			list.erase(index);
			for (int i = index; i < list.size(); i++) {
				index_map.insert(pair<T,int>(list.at(i), i));
			}
		}
		
		// Gets the data at the given index.
		T at(int index) {
			return list.at(index);
		}

		// Check whether or not the given data is in the SetList.
		bool contains(T data) {
			return index_map.count(data);
		}

		// Checks the index of the data in the list.
		int index_of(T data) {
			return index_map.at(data);
		}

		// Returns the size of the SetList
		int size() {
			return list.size();
		}
};


