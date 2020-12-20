#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "FileUtil.h"
#include "Problems.h"
#include "StringUtil.h"


namespace AOC2020 {

	typedef std::unordered_map<
		unsigned long,
		std::pair<unsigned long, unsigned long>
	> mapType;

	void _updateNumber(unsigned long number, unsigned long turn, mapType& seenNumbers) {
		auto fnd = seenNumbers.find(number);
		if (fnd == seenNumbers.end()) seenNumbers[number] = std::make_pair(turn, -1);
		else {
			unsigned long lastTurn = fnd->second.first;
			fnd->second.second = lastTurn;
			fnd->second.first = turn;
		}
	}

	unsigned long _getNumber(unsigned long number, const mapType& seenNumbers) {
		auto fnd = seenNumbers.find(number);
		if (fnd == seenNumbers.end()) return 0;
		else {
			if (fnd->second.second < fnd->second.first) return fnd->second.first - fnd->second.second;
			else return 0;
		}
	}

	int Problem15() {
		std::ifstream infile = AOCUtils::GetFile("inputs/Problem15Input.txt");
		std::string line;
		std::getline(infile, line);
		std::vector<std::string> startingNumbersS;
		AOCUtils::splitString(line, startingNumbersS, ',');
		std::vector<unsigned long> startingNumbers;
		for (auto s : startingNumbersS) startingNumbers.push_back(std::stol(s));
		unsigned long turn = 0;
		std::unordered_map<unsigned long, std::pair<unsigned long, unsigned long>> seenNumbers;
		unsigned long lastNumber = 0;
		while (turn < 2020) {
			unsigned long number;
			if (turn < startingNumbers.size()) number = startingNumbers[turn];
			else {
				number = _getNumber(lastNumber, seenNumbers);
			}
			lastNumber = number;
			_updateNumber(number, turn, seenNumbers);
			turn++;
		}
		std::cout << "Turn: " << turn << " Got number: " << lastNumber << std::endl;
		seenNumbers.clear();
		turn = 0;
		lastNumber = 0;
		while (turn < 30000000) {
			unsigned long number;
			if (turn < startingNumbers.size()) number = startingNumbers[turn];
			else {
				number = _getNumber(lastNumber, seenNumbers);
			}
			lastNumber = number;
			_updateNumber(number, turn, seenNumbers);
			turn++;
		}
		std::cout << "Turn: " << turn << " Got number: " << lastNumber << std::endl;
	}
}
