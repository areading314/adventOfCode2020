#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "FileUtil.h"
#include "Problems.h"

namespace AOC2020 {

	int _countYesAnswers(std::vector<std::string> lines) {
		std::unordered_set<char> yesAnswers;
		for (int i = 0; i < lines.size(); i++) {
			std::unordered_set<char> currentSet;
			for (char c : lines[i]) {
				currentSet.insert(c);
			}
			for (char c : currentSet) {
				if (i == 0) {
					yesAnswers.insert(c);
				}
				else if (yesAnswers.find(c) == yesAnswers.end()) {
					yesAnswers.erase(c);
				}
			}
			if (yesAnswers.size() == 0) continue;
			std::vector<char> v(yesAnswers.size());
			std::copy(yesAnswers.begin(), yesAnswers.end(), v.begin());
			for (auto c = v.begin(); c != v.end(); ++c) {
				if (currentSet.find(*c) == currentSet.end() && (yesAnswers.find(*c) != yesAnswers.end())) {
					yesAnswers.erase(*c);
				}
			}
		}
		return (int) yesAnswers.size();
	}

	int Problem6() {
		std::string filename("inputs/Problem6Input.txt");
		std::ifstream inputFile = AOCUtils::GetFile(filename);
		std::string line;
		std::vector<std::string> lines;
		std::vector<bool> takenSeats(1024);
		int result = 0;
		while (std::getline(inputFile, line)) {
			if (line.size() == 0) {
				result += _countYesAnswers(lines);
				lines.clear();
			}
			else {
				lines.push_back(line);
			}
		}
		result += _countYesAnswers(lines);
		lines.clear();
		std::cout << "Answer is " << result << std::endl;
		return EXIT_SUCCESS;
	}

}