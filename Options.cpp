//
// Created by xiro on 9/14/18.
//

#include "Options.h"

//generate prims algorithm maze
bool Options::Generate(GrowingTree *M, char *argv[], int argc,
					   std::mt19937 &timeSeed, int &height, int &width,
					   std::vector <std::vector<cell>> &maze,
					   bool &generated, std::string &seed) {
	std::hash <std::string> hasher;
	auto hashSeed = hasher(seed);
	std::string seedStore;
	std::regex words("^[a-zA-Z0-9]+$");
	std::stringstream s1;
	std::vector <std::string> arguments;
	time_t seconds = time(NULL);
	sClock::time_point beginning = sClock::now();
	int ender;
	std::string sv = "--sv";
	std::string sb = "--sb";
	std::string lb = "--lb";
	std::string pm = "--pm";
	//replace this with new generate arguments
	//std::string g = "--g";
	//Mazer obj;

	Utilities util;

	for (int j = 1; j < argc; j++) {
		arguments.push_back(argv[j]);
	}

	for (int p = 0; p < argc - 1; p++) {
		if (arguments[p] == sv) {
			ender = p - 1;
			break;
		} else if (arguments[p] == sb) {
			ender = p - 1;
			break;
		} else if (arguments[p] == pm) {
			ender = p - 1;
			break;
		} else {
			ender = p;
		}
	}

	if (ender == 0) {
		/*Generate seed and dimensions*/
		generated = true;
		Options::GenerateDimensions(timeSeed, height, width);
		if (width != height) {
			std::cout
					<< "sorry this does not support width != height dimensions"
					<< std::endl;
			return 0;
		}

		maze = util.MazeResize(maze, height, width);
		InitGen(M, maze, timeSeed);
		std::cout << "seed: " << seed << std::endl;
		return 1;
	} else if (ender == 1) {
		seed = arguments[1];
		generated = true;
		hashSeed = hasher(seed); //returns std::size_t
		std::mt19937 mtSeed(hashSeed);

//		timeSeed = ConvertSeed(mtSeed);

		Options::GenerateDimensions(mtSeed, height, width);
		if (width != height) {
			std::cout
					<< "sorry this does not support width != height dimensions"
					<< std::endl;
			return 0;
		}
		maze = util.MazeResize(maze, height, width);
		InitGen(M, maze, mtSeed);
		std::cout << "seed: " << seed << std::endl;
		return 1;
	} else if (ender == 2) {
		/*auto Generate seed but given dimensions*/
		while (!regex_match(seed.begin(), seed.end(), words)) {
			sClock::duration d = sClock::now() - beginning;
			seconds = d.count();
			seed = seconds;
		}
		hashSeed = hasher(seed); //returns std::size_t
		std::mt19937 mtSeed(hashSeed);
//		timeSeed = ConvertSeed(mtSeed);

		/*try to make dimensions in symmeterical*/
		std::string sWidth = arguments[1];
		std::string sHeight = arguments[2];

		if (atoi(sWidth.c_str()) && atoi(sHeight.c_str())) {
			width = atoi(sWidth.c_str());
			height = atoi(sHeight.c_str());
			/*Generate maze here*/
			if (width != height) {
				std::cout
						<< "sorry this does not support width != height dimensions"
						<< std::endl;
				return 0;
			}

			maze = util.MazeResize(maze, height, width);
			InitGen(M, maze, mtSeed);
		} else {
			return 0;
		}
		std::cout << "seed: " << seed << std::endl;
		if (argc == 4) {
			std::cout << "completed" << std::endl;
			return 1;
		}
		return 1;
	} else if (ender == 3) {
		/*user inputted dimensions*/
		seed = arguments[1];
		generated = true;
		hashSeed = hasher(seed); //returns std::size_t
		std::mt19937 mtSeed(hashSeed);

//		timeSeed = ConvertSeed(mtSeed);

		std::string sWidth = arguments[2];
		std::string sHeight = arguments[3];

		if (atoi(sWidth.c_str()) && atoi(sHeight.c_str())) {
			width = atoi(sWidth.c_str());
			height = atoi(sHeight.c_str());
			if (width != height) {
				std::cout
						<< "sorry this does not support width != height dimensions"
						<< std::endl;
				return 0;
			}
			/*Generate maze here*/
			/*the problem is probably involcved in mt seed*/
			maze = util.MazeResize(maze, height, width);
			InitGen(M, maze, mtSeed);
			std::cout << "seed: " << seed << std::endl;
			return 1;
		} else {
			/*this is making it's own seed*/
			while (!regex_match(seed.begin(), seed.end(), words)) {
				sClock::duration d = sClock::now() - beginning;
				seconds = d.count();
				seed = seconds;
			}
			/*get dimensions*/
			Options::GenerateDimensions(timeSeed, height, width);
			/*Generate maze*/
			if (width != height) {
				std::cout
						<< "sorry this does not support width != height dimensions"
						<< std::endl;
				return 0;
			}
			maze = util.MazeResize(maze, height, width);
			InitGen(M, maze, timeSeed);
			std::cout << "seed: " << seed << std::endl;
			return 1;
		}
	} else {
		/*this is making it's own seed*/
		while (!regex_match(seed.begin(), seed.end(), words)) {
			sClock::duration d = sClock::now() - beginning;
			seconds = d.count();
			seed = seconds;
		}
		/*get dimensions*/
		Options::GenerateDimensions(timeSeed, height, width);
		if (width != height) {
			std::cout
					<< "sorry this does not support width != height dimensions"
					<< std::endl;
			return 0;
		}
		/*Generate the maze*/
		maze = util.MazeResize(maze, height, width);
		InitGen(M, maze, timeSeed);
		std::cout << "seed: " << seed << std::endl;
		return 1;
	}
}

void Options::InitGen(GrowingTree *M, std::vector <std::vector<cell>> &maze,
					  std::mt19937 &timeSeed) {

	Utilities util;
	std::cout << "xcords" << (int) maze[0].size() << std::endl;
	std::cout << "ycords" << (int) maze.size() << std::endl;
		int xCords = (int) maze[0].size();
		int yCords = (int) maze.size();
		if (xCords < 2 || yCords < 2) {
			xCords += 2;
			yCords += 2;
			util.MazeResize(maze, yCords, xCords);
		}
		std::uniform_int_distribution<> distrWidth(0,
												   yCords -
												   1); // define the range
		std::uniform_int_distribution<> distrHeight(0,
													xCords -
													1); // define the range
		/*we're minusing width and height as we count 0*/
	xCords = distrWidth(timeSeed);
	yCords = distrHeight(timeSeed);
	maze[xCords][yCords].value = 1;
	M->Generator(maze, xCords, yCords, timeSeed);
}

void
Options::GenerateDimensions(std::mt19937 &mtSeed, int &height, int &width) {
	std::stringstream s1;
	std::string seedStore;

	s1 << mtSeed();
	seedStore = s1.str();
	seedStore = seedStore.substr(0, 5);
	auto seedNumber = std::stoi(seedStore);
	height = (int) (seedNumber) % 20;
	width = (int) (seedNumber) % 20;
}

//
//bool Options::SolveRouting(char *argv[], int argc, std::mt19937 &mtSeed, int &height, int &width,
//                                std::vector <std::vector<cell>> &maze,
//                                bool &generated, std::string &seed) {
//    //do i need to generate a new maze for this?
//    return false;
//}