//
// Created by xiro on 9/28/18.
//

#ifndef A2_GROWINGTREE_H
#define A2_GROWINGTREE_H

#include "cell.h"
#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include <sstream>
#include <string>
#include <chrono>


class GrowingTree {
public:
	virtual void
	Generator(std::vector <std::vector<cell>> &maze, int &xCords, int &yCords,
			  std::mt19937 &mtSeed) = 0;

	bool FindNeighbour(std::vector <std::vector<cell>> &maze, int &xCords,
					   int &yCords, std::mt19937 &mtSeed);

	void checkNeighbours(std::vector <std::vector<cell>> &maze,
						 std::vector <std::string> &potential, int *xCords,
						 int *yCords);

	void
	SelectPath(std::vector <std::vector<cell>> &maze, int &xCords, int &yCords,
			   std::vector <std::string> &potential);
};

#endif //A2_GROWINGTREE_H
