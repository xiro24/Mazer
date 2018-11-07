//
// Created by xiro on 9/16/18.
//

#include "Main.h"

int main(int argc, char *argv[]) {
	Main obj;
	if (obj.Menu(argc, argv) == 0) {
		std::cout << "fail" << std::endl;
		return 0;
	} else {
		std::cout << "success" << std::endl;
		return 1;
	}
}

bool Main::Menu(int argc, char *argv[]) {
	int width = 0;
	int height = 0;
	bool generated = false;
	bool loaded = false;
	std::string seed;
	time_t seconds;
	std::hash <std::string> hasher;
	sClock::time_point beginning = sClock::now();
	std::string sv = "--sv";
	std::string sb = "--sb";
	std::string lb = "--lb";
	std::string gp = "--gp";
	std::string gr = "--gr";
	std::string pm = "--pm";
	std::regex words("^[a-zA-Z0-9]+$");
	std::vector <std::vector<cell>> maze;
	//Mazer obj;
	HandleFiles handleF;
	Loading load;
	Options pick;
	MazeRouting solve;
	Utilities util;

	seconds = time(NULL);
	seed = seconds;
	auto hashSeed = hasher(seed);
	std::mt19937 mtSeed(hashSeed);

	/*inital loading/generating arguments*/
	if (argv[1] == gp || argv[1] == gr || argv[1] == lb) {
		/*a cheeky way to do this backtracking is to edit the value from 1 to 2,
		 * the value 2 being that it has already back tracked so you only need
		 * to look for cells with a value of 1
		 *
		 * ok, maybe you might need a list if the spec says you have to
		 * */

		//you should be using polymorphism to generate these
		if (argv[1] == gp) { //generate a maze using prim's algorithm
			std::cout << "generating prim's algorithm" << std::endl;
			GeneratePrim pm;
			if (!pick.Generate(&pm, argv, argc, mtSeed, height, width, maze,
							   generated, seed)) {
				std::cout << "incorrect arguments - did not: save or load"
						  << std::endl;
				return 0;
			}
		}
		if (argv[1] == gr) { //generate a maze using
			// recursive backtracking
			// algorithm
			std::cout << "generating recursive backtracking" << std::endl;
			GenerateRecursive rc;
			//pass it by pointer
			if (!pick.Generate(&rc, argv, argc, mtSeed, height, width, maze,
							   generated, seed)) {
				std::cout << "incorrect arguments - did not: save or load"
						  << std::endl;
				return 0;
			}
		}
		//made redundant for A2
//        if (argv[1] == g) {
//            if (!pick.Generate(argv, argc, mtSeed, height, width,
// maze, generated, seed)) {
//                std::cout << "incorrect arguments - did not: save or load"
// << std::endl;
//                return 0;
//            }
//        }
		if (argv[1] == lb) {
			std::string binaryfile = argv[2];
			loaded = true;
			if (binaryfile.find("maze") != std::string::npos) {

				if (!load.LoadBinary(maze, height, width, binaryfile)) {
					return 0;
				}
				if (argc - 1 == 2) {
					std::cout << "end of program..." << std::endl;
					return 1;
				}
			} else {
				std::cout << "incorrect file type" << std::endl;
				return 0;
			}
		}
	} else {
		std::cout << "incorrect order of arguments" << std::endl;
		return 0;
	}

	/*random generated seed*/
	while (!regex_match(seed.begin(), seed.end(), words)) {
		sClock::duration d = sClock::now() - beginning;
		seconds = d.count();
		seed = seconds;
	}
	/*command prompt options*/
	for (int i = 1; i < argc; i++) {
		if (argv[i] == sv) {
			/*pick::SaveBinaryOption(argv,generated,mtSeed,loaded,argc)*/
			std::string svgName = argv[i + 1];
			if (generated == true) {
				if (handleF.SaveSvg(svgName, maze, height, width)) {
					std::cout << "saving svg sucessful" << std::endl;
				} else {
					std::cout << "save svg failed" << std::endl;
					std::cout << "incorrect file type" << std::endl;
					return 0;
				}
			} else if (loaded == true) {
				if (handleF.SaveSvg(svgName, maze, height, width)) {
					std::cout << "saving svg sucessful" << std::endl;
				} else {
					std::cout << "saving svg failed" << std::endl;
					std::cout << "incorrect file type" << std::endl;
					return 0;
				}
			} else {
				/*randomly generated*/
				if (handleF.SaveSvg(svgName, maze, height, width)) {
					std::cout << "saving svg sucessful" << std::endl;
				} else {
					std::cout << "saving svg failed" << std::endl;
					std::cout << "incorrect file type" << std::endl;
					return 0;
				}
			}
			if (argc - 1 == i + 1) {
				std::cout << "end of program..." << std::endl;
				return 1;
			}
		}
		if (argv[i] == sb) {
			std::string svBinary = argv[i + 1];
//            if (generated == true) {
//                std::mt19937 mtSeed(hashSeed);
//            }
			handleF.SaveBinary(maze, height, width, svBinary);
			if (argc - 1 == i + 1) {
				std::cout << "end of program..." << std::endl;
				return 1;
			}
		}
		if (argv[i] == pm) {
			if (argv[1] == lb) {
				util.InitializeRoute(maze, height, width);
			}
			std::cout << "commencing maze solving..." << std::endl;
			solve.Generator(maze);
			std::cout << "Maze solving complete" << std::endl;
			if (argc - 1 == i + 1) {
				std::cout << "end of program..." << std::endl;
				return 1;
			}
		}
	}
	std::cout << "incorrect arguments - did not: save or load" << std::endl;
	return 1;
}