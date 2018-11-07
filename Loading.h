//
// Created by xiro on 9/14/18.
//

#ifndef A1_LOADING_H
#define A1_LOADING_H

#include "Utilities.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <chrono>
#include <regex>

class Loading {
public:
	bool
	LoadBinary(std::vector <std::vector<cell>> &maze, int &height, int &width,
			   std::string binaryFile);

	bool LoadMaze(std::vector <std::vector<cell>> &maze,
				  std::vector <std::string> fileData, int &width, int &height);

	bool MapMaze(std::vector <std::vector<cell>> &maze,
				 std::vector <std::string> fileData, int &width, int &height);
};

#endif //A1_LOADING_H
