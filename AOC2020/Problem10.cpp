#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "FileUtil.h"
#include "Problems.h"

typedef std::uint64_t number_t;
typedef std::vector<number_t>::size_type index_t;
typedef std::vector<number_t>::const_iterator iterator_t;


namespace AOC2020 {
	number_t countNumberOfArrangements(iterator_t begin, iterator_t last, iterator_t end) {
		static std::unordered_map<number_t, number_t> cache;
		auto result = cache.find(*begin);
		if (result != cache.end()) return result->second;
		// std::cout << "called with: " << *begin << " " << *last << std::endl;
		if (std::next(begin) == last && (*last - *begin <= 3)) {
			cache[*begin] = 1;
		}
		else if (std::next(begin) == last && (*last - *begin > 3)) {
			cache[*begin] = 0;
		}
		else {
			number_t retval = 0;
			for (index_t i = 1; i <= 3; i++) {
				auto possibleNext = std::next(begin, i);
				if (possibleNext != end && (*possibleNext - *begin <= 3)) retval += countNumberOfArrangements(std::next(begin, i), last, end);
				else break;
			}
			cache[*begin] = retval;
		}
		return cache[*begin];
	}

	int Problem10() {
		std::string filename("inputs/Problem10Input.txt");
		std::ifstream inputFile = AOCUtils::GetFile(filename);
		std::string line;
		std::vector<number_t> adapters;
		number_t maxAdapter = 0;
		adapters.push_back(0);
		while (std::getline(inputFile, line)) {
			number_t newAdapter = std::stol(line);
			adapters.push_back(newAdapter);
			if (newAdapter > maxAdapter) {
				maxAdapter = newAdapter;
			}
		}
		adapters.push_back(maxAdapter + 3);
		std::sort(adapters.begin(), adapters.end());
		number_t lastAdapter = 0;
		auto start = adapters.begin();
		auto next = start + 1;
		number_t oneCount = 0, threeCount = 0;
		while(next != adapters.end()) {
			if (*next - *start == 1) {
				oneCount++;
			}
			else if (*next - *start == 3) {
				threeCount++;
			}
			next++; start++;
		}
		for (auto i : adapters) std::cout << i << " ";
		std::cout << std::endl;
		std::cout << "Ones: " << oneCount << std::endl;
		std::cout << "Threes: " << threeCount << std::endl;
		std::cout << "Product: " << oneCount * threeCount << std::endl;

		std::cout << "Length of input: " << adapters.size() << std::endl;
		std::cout << "adapters: ";
		for (auto i : adapters) std::cout << i << " ";
		std::cout << std::endl;
		std::cout << "Number of arrangements: " << countNumberOfArrangements(adapters.begin(), std::next(adapters.begin(), adapters.size() - 1), adapters.end()) << std::endl;

		return EXIT_SUCCESS;
	}
}