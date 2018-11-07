//
// Created by xiro on 10/3/18.
//

#ifndef A2_MAZEROUTING_H
#define A2_MAZEROUTING_H

#include "GrowingTree.h"
#include "CustomSet.h"
#include <stdlib.h>

class MazeRouting {
public:
	void Generator(std::vector <std::vector<cell>> &maze);

	//template <typename T> bool FindRoute(std::vector <std::vector<cell>> &maze,
	// T &start);
	int RandomDirection(std::mt19937 mtSeed, int potentialLen);

	void
	SelectPath(std::vector <std::vector<cell>> &maze, int &xCords, int &yCords,
			   std::vector <std::string> potential);

	void checkNeighbours(std::vector <std::vector<cell>> &maze,
						 std::vector <std::string> &potential, int *xCords,
						 int *yCords);

	bool FindNeighbour(std::vector <std::vector<cell>> &maze, int &xCords,
					   int &yCords);

};

#endif //A2_MAZEROUTING_H
