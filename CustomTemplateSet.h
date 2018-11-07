//
// Created by xiro on 9/29/18.
//

#ifndef A2_CUSTOMTEMPLATESET_H
#define A2_CUSTOMTEMPLATESET_H

#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <algorithm>
#include <sstream>
#include <set>

template<class T>
class CustomTemplateSet {
private:
	//just data structure which is the heap
	std::set<T *> seen;
	typename std::set<T *>::iterator it;
	std::pair<typename std::set<T *>::iterator, bool> ret;
public:

	void insert(T &cell) {
		ret = seen.insert(&cell);
		if (ret.second != false) {
			//std::cout << "cell inserted" << std::endl;
		} else {
			std::cout << "Duplicated cell" << std::endl;
		}

	}


	//fix this pls it doesn't work with custom dimensions
	void remove(T &cell) {
		ret = seen.insert(&cell);
		if (ret.second != false) {
			std::cout << "Cell doesn not exist" << std::endl;
			seen.erase(&cell);
			return;
		} else {
			seen.erase(&cell);
			//std::cout << "Cell erased" << std::endl;
		}
	}

	bool empty() {
		if (seen.empty()) {
			return true;
		}
		return false;
	}

	void SetRandom(std::mt19937 &mtSeed) {
		std::stringstream s1;
		std::string seedStore;
		s1 << mtSeed();
		seedStore = s1.str();
		seedStore = seedStore.substr(0, 5);
		auto seedNumber = std::stoi(seedStore);
		int index = (int) (seedNumber) % (int) seen.size();
		it = seen.begin();
		std::advance(it, index);
	}

	//returns the x and y
	T *randomCell() {
//		std::cout << "random coord x: " << xHeap[index];
		return *it;
	};
};

#endif //A2_CUSTOMTEMPLATESET_H

