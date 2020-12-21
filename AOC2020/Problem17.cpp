#include <iostream>

#include "GameOfLife.h"
#include "Problems.h"
#include "FileUtil.h"


namespace AOC2020 {
	int Problem17() {
		std::ifstream infile("inputs/Problem17Input.txt");
		std::string line;
		BoolVector3D inputState;
		BoolVector2D inputPlane;
		while (std::getline(infile, line)) {
			BoolVector1D inputRow;
			for (auto c : line) {
				BOOL active = c == '#';
				inputRow.push_back(active);
			}
			inputPlane.push_back(inputRow);
		}
		inputState.push_back(inputPlane);
		GameOfLife gol(17, 20, 20);
		gol.setState(inputState, 6, 6, 6);
		std::cout << gol;

		for (unsigned i = 0; i < 6; i++) {
			gol.step();
		}

		std::cout << "Active cubes after 6 steps (3 dimensions): " << gol.activeCount() << std::endl;

		GameOfLife gol4d(17, 20, 20, 20);
		gol4d.setState(inputState, 6, 6, 6, 6);
		for (unsigned i = 0; i < 6; i++) {
			gol4d.step();
		}

		std::cout << "Active cubes after 6 steps (4 dimensions): " << gol4d.activeCount() << std::endl;

		return EXIT_SUCCESS;
	}
}