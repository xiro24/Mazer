//
// Created by xiro on 10/3/18.
//

#include "MazeRouting.h"

void MazeRouting::Generator(std::vector <std::vector<cell>> &maze) {
	CustomSet Set;
	int xCords = 0;
	int yCords = 0;
	maze[xCords][yCords].value = 0;
	auto start = std::chrono::steady_clock::now();
	Set.insert(maze[xCords][yCords]);
	maze[xCords][yCords].color = "blue";
	//this is here because the maze only accpets even length for dimensions
	if ((int) maze.size() % 2 != 0 || (int) maze[0].size() % 2 != 0) {
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::steady_clock::now() - start);
		std::cout << "Unfortunately this maze is not solvable" << std::endl;
		std::cout << "path is not reachable from 0,0 to :"
				  << (int) maze[0].size() - 1 << "," << (int) maze.size() - 1
				  << std::endl;
		return;
	}

	while (true) {
		if (FindNeighbour(maze, xCords, yCords)) {
			Set.insert(maze[xCords][yCords]);
			maze[xCords][yCords].color = "red";
		} else {
			Set.remove(maze[xCords][yCords]);
			maze[xCords][yCords].color = "white";
		}
		if (xCords == (int) maze[0].size() - 1 &&
			yCords == (int) maze.size() - 1) {
			maze[(int) maze[0].size() - 1][(int) maze.size() -
										   1].color = "blue";
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
					std::chrono::steady_clock::now() - start);
			std::cout << "milliseconds since start: " << elapsed.count()
					  << '\n';
			std::cout << "path reachable from 0,0 to :"
					  << (int) maze[0].size() - 1 << ","
					  << (int) maze.size() - 1 << std::endl;
			break;
		}
		if (Set.empty()) {
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
					std::chrono::steady_clock::now() - start);
			std::cout << "milliseconds since start: " << elapsed.count()
					  << '\n';
			std::cout << "path is not reachable from 0,0 to :"
					  << (int) maze[0].size() - 1 << ","
					  << (int) maze.size() - 1 << std::endl;
			break;
		}
		xCords = Set.top().xPos;
		yCords = Set.top().yPos;
		//std::cout << "xcords: " << xCords << "ycords: "<< yCords << std::endl;
	}
}

bool
MazeRouting::FindNeighbour(std::vector <std::vector<cell>> &maze, int &xCords,
						   int &yCords) {
	std::vector <std::string> potential;
	if (maze[xCords][yCords].value == 0) {
		checkNeighbours(maze, potential, &xCords, &yCords);
		if (!potential.empty()) {
			//randomize potential
			SelectPath(maze, xCords, yCords, potential);
			return true;
		}
	}
	//remove the current cell as a 1 if no unvisited members found
	//it never hits this, because it always sees it's previous self
	maze[xCords][yCords].value = 1;
	//std::cout << "x and y false" << xCords << " " << yCords << std::endl;
	return false;
}

void MazeRouting::checkNeighbours(std::vector <std::vector<cell>> &maze,
								  std::vector <std::string> &potential,
								  int *xCords, int *yCords) {
	//it's zero as there is already a path avaliable
	/*north*/
	if (*xCords > 0) {
		if (maze[*xCords - 1][*yCords].south == 0 &&
			maze[*xCords - 1][*yCords].value == 2) {
			potential.push_back("N");
		}
	}
	/*south*/
	if (*xCords + 1 < (int) maze[0].size()) {
//		std::cout << "before S" << std::endl;
//		std::cout << "south value :: " << maze[xCords + 1][yCords].north
// < std::endl;
		if (maze[*xCords + 1][*yCords].north == 0 &&
			maze[*xCords + 1][*yCords].value == 2) {
//			std::cout << "inside S" << std::endl;
			potential.push_back("S");
		}
	}

	/*east*/
	if (*yCords + 1 < (int) maze.size()) {
//		std::cout << "before e" << std::endl;
		if (maze[*xCords][*yCords + 1].west == 0 &&
			maze[*xCords][*yCords + 1].value == 2) {
//			std::cout << "inside E" << std::endl;
			potential.push_back("E");
		}
	}
//	std::cout << "before west" << std::endl;
	/*west*/
	if (*yCords > 0) {
		if (*yCords - 1 < (int) maze.size()) {
			if (maze[*xCords][*yCords - 1].east == 0 &&
				maze[*xCords][*yCords - 1].value == 2) {
				potential.push_back("W");
			}
		}
	}
}

void MazeRouting::SelectPath(std::vector <std::vector<cell>> &maze, int &xCords,
							 int &yCords, std::vector <std::string> potential) {
	//std::cout << "potential " << potential[0] << std::endl;

	if (potential.back() == "N") {
		xCords -= 1;
		maze[xCords][yCords].value = 0;
	} else if (potential.back() == "S") {
		xCords += 1;
		maze[xCords][yCords].value = 0;
	} else if (potential.back() == "E") {
		yCords += 1;
		maze[xCords][yCords].value = 0;
	} else if (potential.back() == "W") {
		yCords -= 1;
		maze[xCords][yCords].value = 0;
	}
}


//template <typename T> bool MazeRouting::FindRoute(std::vector <std::vector<cell>> &maze, T &start) {
////	//manhatten distance:
//	int xDest = (int)maze.size()-1;
//	int yDest = (int)maze[0].size()-1;
//	int MD = abs(0-xDest) + abs(0-yDest);
//	int MD_alt;
//	int PREV;
//	maze[0][0].color = "red";
//	Route route;
//	int currx=0;
//	int curry=0;
//
//////	//you would need to insert a new type of cell for the manhatten distance
//////	//make a new class.h for it
//////	//one that can store MD, cords then go through the loop to match the corresponding maze
//////	//cell coordinates so you can draw them
//
//	while (currx!=xDest && curry!=yDest) {
//		for (int i =0 ; i < (int)maze[0].size(); i++) {
//			for (int j =0 ; j < (int)maze.size() ; j++) {
//				if (maze[i][j].top != nullptr) {
//					MD_alt = abs(i-xDest) + abs(j-yDest);
//					route.top = maze[i][j].top;
//					route.MD = MD_alt;
//					path.push_back(route);
//				}
//				if (maze[i][j].down != nullptr) {
//					MD_alt = abs(i-xDest) + abs(j-yDest);
//					route.down = maze[i][j].down;
//					route.MD = MD_alt;
//					path.push_back(route);
//				}
//				if (maze[i][j].left != nullptr) {
//					MD_alt = abs(i-xDest) + abs(j-yDest);
//					route.left = maze[i][j].left;
//					route.MD = MD_alt;
//					path.push_back(route);
//				}
//				if (maze[i][j].right != nullptr) {
//					MD_alt = abs(i-xDest) + abs(j-yDest);
//					route.right = maze[i][j].right;
//					route.MD = MD_alt;
//					path.push_back(route);
//				}
//			}
//		}
//	}
//	while (currx!=xDest && curry!=yDest) {
//		for (int i =0 ; i < (int)maze[0].size(); i++) {
//			for (int j =0 ; j < (int)maze.size() ; j++) {
//				if (i-1 > 0) {
//					if (maze[i][j].north == 0) {
//						MD_alt = abs(i-xDest) + abs(j-yDest);
//						if (maze[i-1][j].south == 0 && maze[i][j].color == "red") {
//							if (PREV != MD_alt){
//								coord.xPos=i;
//								coord.yPos=j;
//								paths.push_back(coord);
//								PREV = MD_alt;
//							}
//							if (MD > MD_alt) {
//								MD = MD_alt;
//
//								coord.xPos = i - 1;
//								coord.yPos = j;
//
//							}
//							maze[i-1][j].color = "red";
//						}
//						currx=i-1;
//						curry=j;
//					}
//				}
//
//				if (i + 1 < (int)maze[0].size()) {
//					if(maze[i][j].south == 0) {
//						MD_alt = abs(i-xDest) + abs(j-yDest );
//
//						if (maze[i+1][j].north == 0 && maze[i][j].color == "red") {
//							if (PREV != MD_alt){
//								coord.xPos=i;
//								coord.yPos=j;
//								paths.push_back(coord);
//								PREV = MD_alt;
//							}
//							if (MD > MD_alt) {
//								MD = MD_alt;
//								coord.xPos= i+1;
//								coord.yPos=j;
//
//
//
//
//							}
//							maze[i+1][j].color = "red";
//						}
//						currx=i+1;
//						curry=j;
//					}
//				}
//				if (j+1 < (int)maze.size()) {
//					if (maze[i][j].east == 0) {
//						MD_alt = abs(i-xDest) + abs(j-yDest );
//						if (maze[i][j+1].west == 0 && maze[i][j].color == "red") {
//							if (PREV != MD_alt){
//								coord.xPos=i;
//								coord.yPos=j;
//								paths.push_back(coord);
//								PREV = MD_alt;
//							}
//							if (MD > MD_alt) {
//								MD = MD_alt;
//								coord.xPos = i;
//								coord.yPos = j + 1;
//
//
//
//
//							}
//							maze[i][j+1].color = "red";
//						}
//						currx=i;
//						curry=j+1;
//					}
//				}
//
//				if (j-1 > 0) {
//					if (maze[i][j].west == 0) {
//						MD_alt = abs(i-xDest) + abs(j-yDest );
//						if (maze[i][j-1].east == 0 && maze[i][j].color == "red") {
//							if (PREV != MD_alt){
//								coord.xPos=i;
//								coord.yPos=j;
//								paths.push_back(coord);
//								PREV = MD_alt;
//							}
//							if (MD > MD_alt) {
//								MD = MD_alt;
//								coord.xPos = i;
//								coord.yPos = j + 1;
//
//
//
//
//							}
//							maze[i][j-1].color = "red";
//						}
//						currx=i;
//						curry=j+1;
//					}
//				}
//				std::cout << "MD: " << MD << std::endl;
//				std::cout << "MD_ALT: " << MD_alt << std::endl;
//			}
//		}
//	}
//
//
//	//-----------------------------------------------
//	//create path
//	std::cout << "inside paths: " << (int)path.size() << std::endl;
//	for (int k = 0; k <  (int)path.size() ; k++) {
//		if (path[k].top != nullptr) {
//			path[k].top->color = "blue";
//		}
//		if (path[k].down != nullptr) {
//			path[k].down->color = "blue";
//		}
//		if (path[k].left != nullptr) {
//			path[k].left->color = "blue";
//		}
//		if (path[k].right != nullptr) {
//			path[k].right->color = "blue";
//		}
//	}
//
//	maze[(int)maze[0].size()-1 ][(int)maze.size()-1 ].color = "blue";
//	//-----------------------------------------------
//	if (MD == MD_alt) {
//		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now( ) - start );
//		std::cout << "milliseconds since start: " << elapsed.count( ) << '\n';
//		std::cout << "path reachable from 0,0 to :" <<  (int)maze[0].size()-1 << ","<<  (int)maze.size()-1 << std::endl;
//		return true;
//	}
//	return false;
//}

