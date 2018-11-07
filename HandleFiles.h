//
// Created by xiro on 9/14/18.
//

#ifndef A1_HANDLEFILES_H
#define A1_HANDLEFILES_H


#include "cell.h"
#include <vector>
#include "boost/format.hpp"
#include <fstream>
#include <string>
#include <chrono>
#include "boost/lexical_cast.hpp"

class HandleFiles {
public:
	bool SaveSvg(std::string svgName, std::vector <std::vector<cell>> &maze,
				 int height, int width);

	bool
	SaveBinary(std::vector <std::vector<cell>> maze, int &height, int &width,
			   std::string svBinary);

	/*template is not a type*/
	template<typename T>
	void BinaryWriter(std::ofstream &outputStream, T value);
};


#endif //A1_HANDLEFILES_H
