//
// Created by xiro on 9/28/18.
//

#ifndef A2_GENERATEPRIM_H
#define A2_GENERATEPRIM_H

#include "MazeRouting.h"
#include "CustomTemplateSet.h"

class GeneratePrim : public GrowingTree {
public:
	void
	Generator(std::vector <std::vector<cell>> &maze, int &xCords, int &yCords,
			  std::mt19937 &mtSeed);
};

#endif //A2_GENERATEPRIM_H
