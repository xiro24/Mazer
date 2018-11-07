//
// Created by xiro on 9/14/18.
//

#ifndef A1_UTILITIES_H
#define A1_UTILITIES_H


#include "cell.h"
#include <vector>

typedef std::vector <std::vector<cell>> VecType;

class Utilities {
public:
	VecType
	MazeResize(std::vector <std::vector<cell>> &maze, int height, int width);

	VecType InitializeRoute(std::vector <std::vector<cell>> &maze, int height,
							int width);
};

#endif //A1_UTILITIES_H
