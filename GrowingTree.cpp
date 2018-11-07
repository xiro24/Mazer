//
// Created by xiro on 9/28/18.
//
//
#include "GrowingTree.h"

//GROWING TREE COMPLETE
bool
GrowingTree::FindNeighbour(std::vector <std::vector<cell>> &maze, int &xCords,
						   int &yCords, std::mt19937 &mtSeed) {
	std::vector <std::string> potential;
	if (maze[xCords][yCords].value == 1) {
		checkNeighbours(maze, potential, &xCords, &yCords);
		if (!potential.empty()) {
			//randomize potential
			//find a way to pass a pointer function
			shuffle(potential.begin(), potential.end(),
					std::default_random_engine(mtSeed()));
			SelectPath(maze, xCords, yCords, potential);
			return true;
		}
	}
	//remove the current cell as a 2 if no unvisited members found
//	std::cout << "it dones't enter??" << std::endl;
	maze[xCords][yCords].value = 2;
	return false;
}


void GrowingTree::SelectPath(std::vector <std::vector<cell>> &maze, int &xCords,
							 int &yCords,
							 std::vector <std::string> &potential) {
	if (potential[0] == "N") {
		//std::cout << "North" << std::endl;
		maze[xCords][yCords].north = 0;
		maze[xCords - 1][yCords].south = 0;
		maze[xCords][yCords].numEdges += 1;
		maze[xCords - 1][yCords].numEdges += 1;

		maze[xCords][yCords].top = &maze[xCords - 1][yCords];
		xCords -= 1;
		maze[xCords][yCords].value = 1;
	} else if (potential[0] == "S") {
		maze[xCords][yCords].south = 0;
		maze[xCords + 1][yCords].north = 0;
		maze[xCords][yCords].numEdges += 1;
		maze[xCords + 1][yCords].numEdges += 1;

		maze[xCords][yCords].down = &maze[xCords + 1][yCords];
		xCords += 1;
		maze[xCords][yCords].value = 1;
	} else if (potential[0] == "E") {
		maze[xCords][yCords].east = 0;
		maze[xCords][yCords + 1].west = 0;
		maze[xCords][yCords].numEdges += 1;
		maze[xCords][yCords + 1].numEdges += 1;

		maze[xCords][yCords].right = &maze[xCords][yCords + 1];
		yCords += 1;
		maze[xCords][yCords].value = 1;
	} else if (potential[0] == "W") {
		maze[xCords][yCords].west = 0;
		maze[xCords][yCords - 1].east = 0;
		maze[xCords][yCords].numEdges += 1;
		maze[xCords][yCords - 1].numEdges += 1;

		maze[xCords][yCords].left = &maze[xCords][yCords - 1];
		yCords -= 1;
		maze[xCords][yCords].value = 1;
	}
	//std::cout << "path:--- " << potential[i] << std::endl;
}


void GrowingTree::checkNeighbours(std::vector <std::vector<cell>> &maze,
								  std::vector <std::string> &potential,
								  int *xCords, int *yCords) {
	/*north*/
	if (*xCords > 0) {
		if (maze[*xCords - 1][*yCords].value == 0) {
			potential.push_back("N");
		}
	}
	/*south*/
	if (*xCords + 1 < (int) maze[0].size()) {
		if (maze[*xCords + 1][*yCords].value == 0) {
			potential.push_back("S");
		}
	}
	/*east*/
	if (*yCords + 1 < (int) maze.size()) {
		if (maze[*xCords][*yCords + 1].value == 0) {
			potential.push_back("E");
		}
	}
	/*west*/
	if (*yCords > 0) {
		if (*yCords - 1 < (int) maze.size()) {
			if (maze[*xCords][*yCords - 1].value == 0) {
				potential.push_back("W");
			}
		}
	}
}
