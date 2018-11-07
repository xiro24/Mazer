//
// Created by xiro on 9/14/18.
//

#include "Utilities.h"

// x is the height
//y is the width

VecType Utilities::MazeResize(std::vector <std::vector<cell>> &maze, int height,
							  int width) {
	std::vector <std::vector<int>> temp(height, std::vector<int>(width));

	maze.resize(temp.size());
	for (int i = 0; i < (int) temp.size(); ++i)
		//resize to height
		maze[i].resize((int) temp[0].size());
	//int n = number of rows, m = number of columns;

	/*set coords*/
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			maze[i][j].xPos = i;
			maze[i][j].yPos = j;
			maze[i][j].value = 0;
		}
	}


//	for (int i = 0; i < (int)maze[0].size(); i++) {
//		for (int j = 0; j < (int)maze.size(); j++) {
//			std::cout << maze[i][j].value;
//		}
//		std::cout << "" << std::endl;
//	}

	return maze;
}

//was for solving the maze with recursive backtrack

//
VecType
Utilities::InitializeRoute(std::vector <std::vector<cell>> &maze, int height,
						   int width) {
	std::vector <std::vector<int>> temp(height, std::vector<int>(width));
	maze.resize(temp.size());
	for (int i = 0; i < (int) temp.size(); ++i)
		//resize to height
		maze[i].resize((int) temp[0].size());
	//int n = number of rows, m = number of columns;

	/*set coords*/
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			maze[i][j].xPos = i;
			maze[i][j].yPos = j;
			maze[i][j].value = 2;
		}
	}
	return maze;
}