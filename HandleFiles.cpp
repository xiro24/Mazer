//
// Created by xiro on 9/14/18.
//

#include "HandleFiles.h"


bool HandleFiles::SaveSvg(std::string filename,
						  std::vector <std::vector<cell>> &maze, int height,
						  int width) {
	std::ofstream outputStream;
	double sum;
	double row;
	auto start = std::chrono::steady_clock::now();
	outputStream.open(filename);
	int viewBoxW = (int) maze[0].size() / 2;
	int viewBoxH = (int) maze.size() / 2;

	if (!outputStream.good()) {
		std::cout << "file does not exist" << std::endl;
		return false;
	}
	outputStream << boost::format(
			"<svg viewBox='0 0 %1d %1d' width='%1i' height='%1i' xmlns='http://www.w3.org/2000/svg'>\n") %
					viewBoxW % viewBoxH % width % height;
	outputStream << boost::format(
			"<rect width='%1i' height='%1i' style='fill: white'/>\n") % width %
					height;
	std::string base = "<line stroke='black' stroke-width='%f' x1='%f' y1='%f' x2='%f' y2='%f'/>\n";

	std::string solve = "<line stroke='red' stroke-width='%f' x1='%f' y1='%f' x2='%f' y2='%f'/>\n";

	std::string dest = "<line stroke='blue' stroke-width='%f' x1='%f' y1='%f' x2='%f' y2='%f'/>\n";

	for (double j = 0; j < viewBoxH; j += 0.5) {
		for (double i = 0; i < viewBoxW; i += 0.5) {
			row = i;
			sum = j;

			outputStream
					<< boost::format(base) % maze[i + i][j + j].north % sum %
					   row % (sum + 0.5) % row;
			outputStream
					<< boost::format(base) % maze[i + i][j + j].east %
					   (sum + 0.5) % row % (sum + 0.5) % (row + 0.5);
			outputStream
					<< boost::format(base) % maze[i + i][j + j].south %
					   (sum + 0.5) % (row + 0.5) % sum % (row + 0.5);
			outputStream
					<< boost::format(base) % maze[i + i][j + j].west % sum %
					   row % sum % (row + 0.5);
			if (maze[i + i][j + j].color == "red") {
				outputStream
						<< boost::format(solve) % 0.5 % (sum + 0.25) % row %
						   (sum + 0.25) % (row + 0.5);
			} else if (maze[i + i][j + j].color == "blue") {
				outputStream << boost::format(dest) % 0.5 % (sum + 0.25) % row %
								(sum + 0.25) % (row + 0.5);
			}
		}
	}
	outputStream << "</svg>";
	outputStream.close();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::steady_clock::now() - start);
	std::cout << "milliseconds since start: " << elapsed.count() << '\n';
	std::cout << "saving successful" << std::endl;
	return true;
}

template<typename T>

void HandleFiles::BinaryWriter(std::ofstream &outputStream, T value) {
	std::string coords;
	int store;

	store = value;
	coords = std::to_string(store);
	outputStream.write((char *) &store, sizeof(int));
	//std::cout << store;
}

bool HandleFiles::SaveBinary(std::vector <std::vector<cell>> maze, int &height,
							 int &width, std::string svBinary) {
	std::ofstream outputStream;
	HandleFiles handleF;
	std::cout << "saving to binary...." << std::endl;
	auto start = std::chrono::steady_clock::now();
	outputStream.open(svBinary, std::ios::out | std::ios::binary);
	int storeEdges = 0;
//    std::string coords;
	std::string vWidth = std::to_string(width);
	std::string vHeight = std::to_string(height);
//    std::string noEdges = std::to_string(storeEdges);
	for (int i = 0; i < (int) maze[0].size(); i++) {
		for (int j = 0; j < (int) maze.size(); j++) {
			storeEdges += maze[i][j].numEdges;
		}
	}
	handleF.BinaryWriter(outputStream, width);
	handleF.BinaryWriter(outputStream, height);
	handleF.BinaryWriter(outputStream, storeEdges);

	for (int i = 0; i < (int) maze[0].size(); i++) {
		for (int j = 0; j < (int) maze.size(); j++) {
			/*get all paths that are linked*/
			if (maze[i][j].top) {
				/*xPosition of current*/
				handleF.BinaryWriter(outputStream, maze[i][j].xPos);
				/*yPosition of current*/
				handleF.BinaryWriter(outputStream, maze[i][j].yPos);
				/*xPosition of top*/
				handleF.BinaryWriter(outputStream, maze[i][j].top->xPos);
				/*yPosition of top*/
				handleF.BinaryWriter(outputStream, maze[i][j].top->yPos);
			}
			if (maze[i][j].down) {
				/*xPosition of current*/
				handleF.BinaryWriter(outputStream, maze[i][j].xPos);
				/*yPosition of current*/
				handleF.BinaryWriter(outputStream, maze[i][j].yPos);
				/*xPosition of down*/
				handleF.BinaryWriter(outputStream, maze[i][j].down->xPos);
				/*yPosition of down*/
				handleF.BinaryWriter(outputStream, maze[i][j].down->yPos);
			}
			if (maze[i][j].left) {
				/*xPosition of current*/
				handleF.BinaryWriter(outputStream, maze[i][j].xPos);
				/*yPosition of current*/
				handleF.BinaryWriter(outputStream, maze[i][j].yPos);
				/*xPosition of left*/
				handleF.BinaryWriter(outputStream, maze[i][j].left->xPos);
				/*yPosition of left*/
				handleF.BinaryWriter(outputStream, maze[i][j].left->yPos);
			}
			if (maze[i][j].right) {
				/*xPosition of current*/
				handleF.BinaryWriter(outputStream, maze[i][j].xPos);
				/*yPosition of current*/
				handleF.BinaryWriter(outputStream, maze[i][j].yPos);
				/*xPosition of right*/
				handleF.BinaryWriter(outputStream, maze[i][j].right->xPos);
				/*yPosition of right*/
				handleF.BinaryWriter(outputStream, maze[i][j].right->yPos);
			}
		}
	}
	outputStream.close();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::steady_clock::now() - start);
	std::cout << "milliseconds since start: " << elapsed.count() << '\n';
	std::cout << "save to binary complete" << std::endl;
	return true;
}
