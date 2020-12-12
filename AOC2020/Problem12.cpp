#include <iostream>

#include "FileUtil.h"
#include "Problems.h"
#include "Ship.h"

namespace AOC2020 {
	int Problem12() {
		Ship s;
		std::ifstream infile = AOCUtils::GetFile("inputs/Problem12Input.txt");
		std::string line;
		while (std::getline(infile, line)) {
			s.applyInstruction(parseInstruction(line));
		}

		WaypointShip ws;
		infile.clear();
		infile.seekg(0, std::ios::beg);
		while (std::getline(infile, line)) {
			ws.applyInstruction(parseInstruction(line));
		}

		std::cout << "Ship has moved Manhattan distance: " << std::abs(s.getXLocation()) + std::abs(s.getYLocation()) << std::endl;
		std::cout << "WaypointShip has moved Manhattan distance: " << std::abs(ws.getXLocation()) + std::abs(ws.getYLocation()) << std::endl;

		return EXIT_SUCCESS;
	}
}