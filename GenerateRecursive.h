//
// Created by xiro on 9/28/18.
//

#ifndef A2_GENERATERECURSIVE_H
#define A2_GENERATERECURSIVE_H

#include "MazeRouting.h"
#include "CustomSet.h"
#include <set>

class GenerateRecursive : public GrowingTree {
public:
	void
	Generator(std::vector <std::vector<cell>> &maze, int &xCords, int &yCords,
			  std::mt19937 &mtSeed);

	bool FindNeighbour(std::vector <std::vector<cell>> &maze, int &xCords,
					   int &yCords, std::mt19937 &mtSeed, std::set <cell> &set);
};

#endif //A2_GENERATERECURSIVE_H
