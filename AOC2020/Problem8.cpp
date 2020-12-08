#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "FileUtil.h"
#include "Gameboy.h"
#include "Problems.h"


namespace AOC2020 {
	int Problem8() {
		std::string filename("inputs/Problem8Input.txt");
		std::ifstream inputFile = AOCUtils::GetFile(filename);
		std::string line;
		std::vector<std::string> lines;
		while (std::getline(inputFile, line)) {
			lines.push_back(line);
		}
		Gameboy g(lines);
		std::cout << "Accumulator value before repeat is: " << g.findAccumulatorAtFirstRepeat() << std::endl;
		std::cout << "Accumulator after running fixed program: " << g.uncorruptAndRunProgram() << std::endl;
		return EXIT_SUCCESS;
	}
}

