////
//// Created by xiro on 9/29/18.
////
#include "GenerateRecursive.h"

void
GenerateRecursive::Generator(std::vector <std::vector<cell>> &maze, int &xCords,
							 int &yCords, std::mt19937 &mtSeed) {
	CustomSet Set;
	auto start = std::chrono::steady_clock::now();
	Set.insert(maze[xCords][yCords]);
	while (true) {
		//try passing the seed by reference instead
		if (GrowingTree::FindNeighbour(maze, xCords, yCords, mtSeed)) {
			Set.insert(maze[xCords][yCords]);
		} else {
			Set.remove(maze[xCords][yCords]);
		}
		if (Set.empty()) {
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
					std::chrono::steady_clock::now() - start);
			std::cout << "milliseconds since start: " << elapsed.count()
					  << '\n';
			std::cout << "finished generating" << std::endl;
			break;
		}
		xCords = Set.top().xPos;
		yCords = Set.top().yPos;
	}
}

// RECURSIVE VERSION --- VV

//This method below leads to a stack overflow with large stacks
//
//void GenerateRecursive::Generator(std::vector <std::vector<cell>> &maze, int &xCords, int &yCords, float &mtSeed) {
//	CustomSet Set;
//	auto start = std::chrono::steady_clock::now();
//	Set.insert(&maze[xCords][yCords]);
//	FindNeighbour(maze,xCords,yCords,mtSeed,Set);
//	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now( ) - start );
//	std::cout << "milliseconds since start: " << elapsed.count( ) << '\n';
//	std::cout << "finished generating" << std::endl;
//}
//
//bool
//GenerateRecursive::FindNeighbour(std::vector <std::vector<cell>> &maze, int &xCords, int &yCords, float &mtSeed,CustomSet &Set) {
//	std::vector <std::string> potential;
//	if (maze[xCords][yCords].value == 1) {
//		GrowingTree::checkNeighbours(maze,potential,&xCords,&yCords);
//		if (!potential.empty()) {
//			//randomize potential
//			GrowingTree::SelectPath(maze,xCords,yCords,RandomDirection(mtSeed, (int)potential.size()),potential);
//			Set.insert(&maze[xCords][yCords]);
//			return FindNeighbour(maze,xCords,yCords,mtSeed,Set);
//		}
//	}
//	//remove the current cell as a 2 if no unvisited members found
//	maze[xCords][yCords].value = 2;
//	Set.remove(&maze[xCords][yCords]);
//	if (Set.empty()) {
//		return true;
//	}
//	xCords = Set.top();
//	yCords = Set.top();
//	return FindNeighbour(maze,xCords,yCords,mtSeed,Set);
//}