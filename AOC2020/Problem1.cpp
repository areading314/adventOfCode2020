#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "FileUtil.h"
#include "Problems.h"

int AOC2020::Problem1() {
	const std::string& filename("inputs/Problem1Input.txt");
	std::vector<int> integers;
	std::string line;

	std::ifstream inputFile = AOCUtils::GetFile(filename);

	while (std::getline(inputFile, line)) {
		integers.push_back(std::stoi(line));
	}

	for (unsigned int i = 0; i < integers.size(); i++) {
		for (unsigned int j = i; j < integers.size(); j++) {
			for (unsigned int k = j; k < integers.size(); k++) {
				if (integers[i] + integers[j] + integers[k] == 2020) {
					std::cout << "Solution is: " << integers[i] * integers[j] * integers[k] << std::endl;
				}
			}
		}
	}

	return EXIT_SUCCESS;
}