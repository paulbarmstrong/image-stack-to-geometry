/*
	Author: Paul Armstrong
	Date: August 2018
	
	Description:
		SetList is a list-like structure which can have no duplicate entries.
*/

using namespace std;

// Adds data to the list if not already in the list.
// Returns the index of the data in the list.
template<typename T>
int SetList<T>::add(T data) {
	if (!index_map.count(data)) {
		index_map.insert(pair<T,int>(data, list.size()));
		list.push_back(data);
		return list.size()-1;
	} else {
		return index_map.at(data);
	}
}

// Removes the data at this given index.
template<typename T>
void SetList<T>::remove_at(int index) {
	index_map.erase(list.at(index));
	list.erase(index);
	for (int i = index; i < list.size(); i++) {
		index_map.insert(pair<T,int>(list.at(i), i));
	}
}

// Gets the data at the given index.
template<typename T>
T& SetList<T>::at(int index) {
	return list.at(index);
}

// Check whether or not the given data is in the SetList.
template<typename T>
bool SetList<T>::contains(T &data) {
	return index_map.count(data);
}

// Checks the index of the data in the list.
template<typename T>
int SetList<T>::index_of(T &data) {
	return index_map.at(data);
}

// Returns the size of the SetList
template<typename T>
int SetList<T>::size() {
	return list.size();
}


