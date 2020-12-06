#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <stdexcept>
#include <vector>

#include "FileUtil.h"
#include "Problems.h"

const std::regex correctPasswordPattern = std::regex("(\\d+)-(\\d+) (.): (.*)");

/* Return true for a correct password, false for an incorrect password*/
bool analyzeInput(const std::string& input) {
	std::smatch matchedGroups;
	std::regex_search(input, matchedGroups, correctPasswordPattern);
	if (matchedGroups.size() == 0) {
		throw std::invalid_argument("Invalid line: " + input);
	}

	int firstPos = std::stoi(matchedGroups[1]) - 1;
	int secondPos = std::stoi(matchedGroups[2]) - 1;
	char letter = ((std::string) matchedGroups[3])[0];
	std::string password = matchedGroups[4];
	return (
		(password[firstPos] == letter && password[secondPos] != letter)
	 || (password[firstPos] != letter && password[secondPos] == letter)
	);
}


int AOC2020::Problem2() {
	const std::string& filename("inputs/Problem2Input.txt");
	std::vector <std::string> inputs;
	std::string line;

	std::ifstream inputFile = AOCUtils::GetFile(filename);

	unsigned int correctCount = 0;

	while (std::getline(inputFile, line)) {
		if (analyzeInput(line)) {
			correctCount++;
		}
	}
	std::cout << correctCount << " matching passwords found." << std::endl;
	return EXIT_SUCCESS;
}

