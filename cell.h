//
// Created by xiro on 9/14/18.
//

#ifndef A1_CELL_H
#define A1_CELL_H

#include <iostream>

class cell {

public:
	int xPos;
	int yPos;
	double north = 0.05;
	double south = 0.05;
	double east = 0.05;
	double west = 0.05;
	cell *top;
	cell *down;
	cell *left;
	cell *right;
	short value = 0;
	int numEdges = 0;
	std::string color = "white";
};

#endif //A1_CELL_H
