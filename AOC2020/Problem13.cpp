#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

#include "FileUtil.h"
#include "StringUtil.h"
#include "Problems.h"



namespace AOC2020 {

	std::uint64_t _findNext(
		std::uint64_t& v,
		std::uint64_t n1,
		std::uint64_t n2,
		std::uint64_t a1,
		std::uint64_t a2,
		std::uint64_t lastScale
	) {
		std::cout << "Finding congruence for n1, n2, a1, a2 = " << n1 << ", " << n2 
			<< ", " << a1 << ", " << a2 << std::endl;
		while (((v + a2) % n2) != 0) {
			v += lastScale;
		}
		lastScale *= n2;
		std::cout << "Found congruence: " << v << std::endl;
		return lastScale;
	}

	std::uint64_t solveCongruencies(std::vector<std::pair<std::uint64_t, std::uint64_t>> coeffs) {
		std::uint64_t value = 0;
		std::uint64_t scale = 1;
		for (auto it = coeffs.begin(); it != coeffs.end(); it++) {
			auto p1 = *it;
			scale = _findNext(value, scale, p1.first, value, p1.second, scale);
		}
		return value;
	}

	int Problem13() {
		std::ifstream input = AOCUtils::GetFile("inputs/Problem13Input.txt");
		std::vector<std::string> lines; 
		std::string line;
		std::vector<int> values;
		std::vector<std::string> tmpValues;
		while (std::getline(input, line)) {
			lines.push_back(line);
		}
		std::uint64_t departureTime = std::stol(lines[0]);
		std::string buses = lines[1];
		std::vector<std::string> busIds;
		AOCUtils::splitString(buses, busIds, ',');
		std::vector<std::uint64_t> busIdL;
		for (auto s : busIds) 
			if(s != "x") busIdL.push_back(std::stol(s));

		std::uint64_t minWaitTime = departureTime;
		std::uint64_t minBusId;
		for (auto b : busIdL) {
			std::uint64_t waitTime = (b - departureTime % b);
			if (waitTime < minWaitTime) {
				minWaitTime = waitTime;
				minBusId = b;
			}
		}

		std::cout << "Min bus Id: " << minBusId << std::endl;
		std::cout << "Min wait time: " << minWaitTime << std::endl;
		std::cout << "Answer: " << minBusId * minWaitTime << std::endl;

		std::vector<std::pair<std::uint64_t, std::uint64_t>> busIdPairs;
		std::uint32_t ai = 0;
		for (auto a : busIds) {
			if (a != "x") {
				auto v = std::stoi(a);
				busIdPairs.push_back(std::make_pair(v, ai));
			}
			ai++;
		}
		std::sort(busIdPairs.begin(), busIdPairs.end(),
			[](std::pair<std::uint64_t, std::uint64_t> a, std::pair<std::uint64_t, std::uint64_t> b){
			return a.first > b.first;
		});

		std::cout << "Applying Chinese Remainder Theorem to solve system of congruencies..." << std::endl;
		std::uint64_t v = solveCongruencies(busIdPairs);
		// std::uint64_t v_smallest = _reduceDown(v, busIdPairs);
		std::cout << v << std::endl;

		return EXIT_SUCCESS;
	}

}