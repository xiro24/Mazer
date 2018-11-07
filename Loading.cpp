//
// Created by xiro on 9/14/18.
//

#include "Loading.h"

bool Loading::LoadBinary(std::vector <std::vector<cell>> &maze, int &height,
						 int &width, std::string binaryFile) {
	std::ifstream InFile;
	std::vector <std::string> fileData;
	std::regex sive("^[a-zA-Z0-9]+$");
	auto start = std::chrono::steady_clock::now();
	int read;
	try {
		InFile.open(binaryFile, std::ios::in | std::ios::binary);
		if (!InFile.good()) {
			std::cout << "file does not exist" << std::endl;
			return false;
		}
		std::string coords;
		while (InFile.read((char *) &read, sizeof(int))) {
			coords = std::to_string(read);
			if (!regex_match(coords.begin(), coords.end(), sive)) {
				std::cout << "This file is rejected" << std::endl;
				return false;
			}
			fileData.push_back(coords);
		}
		InFile.close();
		Loading obj;
		obj.LoadMaze(maze, fileData, width, height);
	} catch (const char* msg) {
		std::cerr << "could not load maze " << std::endl;
	}
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::steady_clock::now() - start);
	std::cout << "milliseconds since start: " << elapsed.count() << '\n';
	return true;
}

bool
Loading::LoadMaze(std::vector <std::vector<cell>> &maze,
				  std::vector <std::string> fileData, int &width, int &height) {
	std::string strHolder = fileData[0];
	width = atoi(strHolder.c_str());
	strHolder = fileData[1];
	height = atoi(strHolder.c_str());
	/*had no real use of no of edges*/
	strHolder = fileData[2];
	//int noEdges = atoi(strHolder.c_str());
	strHolder = fileData[3];
	//int edges = atoi(strHolder.c_str());

	fileData.erase(fileData.begin(), fileData.begin() + 3);
	Utilities util;
	Loading load;
	util.MazeResize(maze, height, width);
	/*seeing after laod content*/

	load.MapMaze(maze, fileData, width, height);
	return true;
}

bool Loading::MapMaze(std::vector <std::vector<cell>> &maze,
					  std::vector <std::string> fileData, int &width,
					  int &height) {
	int x1;
	int y1;
	int x2;
	int y2;

	for (int k = 0; k < (int) fileData.size(); k++) {
		x1 = atoi(fileData[k].c_str());
		k++;
		y1 = atoi(fileData[k].c_str());
		k++;
		x2 = atoi(fileData[k].c_str());
		k++;
		y2 = atoi(fileData[k].c_str());
		/*south*/
		if (x1 + 1 < height) {
			if (maze[x1 + 1][y1].xPos == maze[x2][y2].xPos) {
				if (maze[x1 + 1][y1].yPos == maze[x2][y2].yPos) {
					maze[x1][y1].south = 0;
					maze[x2][y2].north = 0;
				}
			}
		}
		/*north*/
		if (x1 - 1 >= 0) {
			if (maze[x1 - 1][y1].xPos == maze[x2][y2].xPos) {
				if (maze[x1 - 1][y1].yPos == maze[x2][y2].yPos) {
					maze[x1][y1].north = 0;
					maze[x2][y2].south = 0;
				}
			}
		}
		/*east*/
		if (y1 + 1 < width) {
			if (maze[x1][y1 + 1].xPos == maze[x2][y2].xPos) {
				if (maze[x1][y1 + 1].yPos == maze[x2][y2].yPos) {
					maze[x1][y1].east = 0;
					maze[x2][y2].west = 0;
				}
			}
		}
		/*west*/
		if (y1 - 1 >= 0) {
			if (maze[x1][y1 - 1].xPos == maze[x2][y2].xPos) {
				if (maze[x1][y1 - 1].yPos == maze[x2][y2].yPos) {
					maze[x1][y1].west = 0;
					maze[x2][y2].east = 0;
				}
			}
		}
		if (k > (int) fileData.size()) {
			std::cout << "error out of bounds" << std::endl;
			return false;
		}
	}
	return false;
}
