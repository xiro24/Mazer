//
// Created by xiro on 9/28/18.
//

#ifndef A2_CUSTOMSET_H
#define A2_CUSTOMSET_H

#include "cell.h"
#include <stack>
#include <set>

class CustomSet {//set and check with a stack
public:
	//replace this with a stack
	std::stack <cell> stack;
	std::set<cell *> seen;
	std::set<cell *>::iterator it;
	std::pair<std::set<cell *>::iterator, bool> ret;

	void insert(cell &Coords) {
		//I don't really need to check for duplicates as i already have value in the cell
		//define or equal to check if it already exists in c++
		ret = seen.insert(&Coords);
		if (ret.second != false) {
			stack.push(Coords);
		} else {
			std::cout << "Duplicated coords" << std::endl;
		}
	}

	void remove(cell &Coords) {

		if (seen.erase(&Coords) == true) {
			stack.pop();
		}
	}

	bool empty() {
		if (seen.empty()) {
			return true;
		}
		return false;
	}

	//returns the top
	cell top() {
		return stack.top();
	}

	int size() {
		return stack.size();
	}
};

#endif //A2_CUSTOMSET_H
