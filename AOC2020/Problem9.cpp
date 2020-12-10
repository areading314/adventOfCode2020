#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

#include "FileUtil.h"
#include "Problems.h"

const std::uint8_t PREAMBLE_LENGTH = 25;
typedef std::uint64_t number_t;
typedef std::vector<number_t>::size_type index_t;

namespace AOC2020 {
	bool isSumOfLastNumbers(number_t lastNumber, const std::list<number_t> lastNumbers) {
		for (auto qi = lastNumbers.begin(); qi != lastNumbers.end(); ++qi) {
			for (auto qj = std::next(qi); qj != lastNumbers.end(); ++qj) {
				if (*qi + *qj == lastNumber) return true;
			}
		}
		return false;
	}

	int Problem9() {
		std::string filename("inputs/Problem9Input.txt");
		std::ifstream inputFile = AOCUtils::GetFile(filename);
		std::string line;
		std::list<number_t> lastNumbers;
		std::vector<number_t> allNumbers;
		for (std::uint8_t i = 0; i < PREAMBLE_LENGTH; i++) {
			std::getline(inputFile, line);
			lastNumbers.push_back(std::stol(line));
			allNumbers.push_back(std::stol(line));
		}
		number_t lastNumber, specialNumber;
		while (std::getline(inputFile, line)) {
			lastNumber = std::stol(line);
			if (!isSumOfLastNumbers(lastNumber, lastNumbers)) {
				specialNumber = lastNumber;
				std::cout << "First number thats not a sum is: " << specialNumber << std::endl;
			}
			lastNumbers.push_back(lastNumber);
			lastNumbers.pop_front();
			allNumbers.push_back(lastNumber);
		}

		index_t i, j;
		bool found = false;
		for (i = 0; !found && (i < allNumbers.size()); i++) {
			number_t currentSum = 0;
			for (j = i; !found && (j < allNumbers.size()); j++) {
				currentSum += allNumbers[j];
				if (currentSum == specialNumber) {
					found = true;
				}
			}
		}
		i -= 1, j -= 1;
		std::cout << "i = " << i << std::endl;
		std::cout << "j = " << j << std::endl;

		number_t minElement = *std::min_element(allNumbers.begin() + i, allNumbers.begin() + j + 1);
		number_t maxElement = *std::max_element(allNumbers.begin() + i, allNumbers.begin() + j + 1);

		std::cout << "Max is: " << maxElement << std::endl;
		std::cout << "Min is: " << minElement << std::endl;
		std::cout << "Sum is : " << maxElement + minElement << std::endl;
		std::cout << std::endl;
		return EXIT_SUCCESS;
	}
}

