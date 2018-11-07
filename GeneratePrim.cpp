////
//// Created by xiro on 9/28/18.
////
#include "GeneratePrim.h"

void GeneratePrim::Generator(std::vector <std::vector<cell>> &maze, int &xCords,
							 int &yCords, std::mt19937 &mtSeed) {
	CustomTemplateSet<cell> Set;
	auto start = std::chrono::steady_clock::now();
	Set.insert(maze[xCords][yCords]);

	while (true) {
		if (GrowingTree::FindNeighbour(maze, xCords, yCords, mtSeed)) {
//			std::cout << "x: " << xCords << "y: " << yCords << std::endl;
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
		Set.SetRandom(mtSeed);
		cell *cell1 = Set.randomCell();
		xCords = cell1->xPos;
		yCords = cell1->yPos;
	}
}