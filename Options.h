//
// Created by xiro on 9/14/18.
//

#ifndef A1_OPTIONS_H
#define A1_OPTIONS_H

#include "Utilities.h"
#include "GeneratePrim.h"
#include "GenerateRecursive.h"
#include <string>
#include <vector>
#include <regex>
#include <random>
#include <chrono>
#include "cell.h"

typedef std::chrono::high_resolution_clock sClock;

class Options {
public:
	bool
	Generate(GrowingTree *M, char *argv[], int argc, std::mt19937 &timeSeed,
			 int &height, int &width, std::vector <std::vector<cell>> &maze,
			 bool &generated, std::string &seed);

	void GenerateDimensions(std::mt19937 &mtSeed, int &height, int &width);

	void InitGen(GrowingTree *M, std::vector <std::vector<cell>> &maze,
				 std::mt19937 &timeSeed);
};

#endif //A1_OPTIONS_H
