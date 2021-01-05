#include <algorithm>
#include <iostream>
#include <list>
#include <unordered_map>

#include "FileUtil.h"
#include "Problems.h"

namespace AOC2020 {
	void print(const std::list<int>& circle) {
		for (auto c : circle) {
			std::cout << c << ",";
		}
		std::cout << std::endl;
	}

	void move(std::list<int>& circle, int maxi, std::unordered_map<int, std::list<int>::iterator>& positions) {
		std::list<int> lifted;
		// std::cout << "circle is: "; print(circle);
		for (auto i = std::next(circle.begin(), 1); i != std::next(circle.begin(), 4); i++) {
			lifted.push_back(*i);
			positions.erase(*i);
		}
		// std::cout << " removed: "; print(lifted);
		circle.erase(std::next(circle.begin(), 1), std::next(circle.begin(), 4));
		int current = circle.front();
		int i = current - 1;
		if (i <= 0) {
			i = maxi;
		}
		while (std::find(lifted.begin(), lifted.end(), i) != lifted.end()) {
			i--;
			if (i <= 0) {
				i = maxi;
			}
		}
		// std::cout << "i is " << i << std::endl;
		auto dest = positions.find(i);
		if (dest == positions.end()) {
			std::cout << "Couldn't find: " << i << " in positions!!" << std::endl;
		}
		auto destIter = dest->second;
		for (auto l = lifted.rbegin(); l != lifted.rend(); l++) {
			// std::cout << "destIter is: " << *destIter << std::endl;
			std::list<int>::iterator nextDest = std::next(destIter, 1);
			auto position = circle.insert(nextDest, *l);
			positions.erase(*l);
			positions.emplace(*l, position);
		}
		int frontInt = circle.front();
		circle.push_back(frontInt);
		circle.pop_front();
		positions.erase(frontInt);
		positions.emplace(frontInt, std::prev(circle.end()));
	}

	int Problem23() {
		// std::string input = "389125467";
		std::string input = "789465123";
		std::list<int> circle;
		std::unordered_map<int, std::list<int>::iterator> positions;
		for (auto c : input) {
			circle.push_back(c - '0');
		}

		for (auto c = circle.begin(); c != circle.end(); c++) {
			positions.emplace(*c, c);
		}
		print(circle);
		for (int i = 0; i < 100; i++) {
			move(circle, 9, positions);
			print(circle);
		}

		while (circle.front() != 1) {
			circle.push_back(circle.front());
			circle.pop_front();
		}

		std::cout << "Final answer: ";
		for (auto c = std::next(circle.begin(), 1); c != circle.end(); c++) {
			std::cout << *c;
		}
		std::cout << std::endl;

		circle.clear();
		positions.clear();
		for (auto c : input) {
			circle.push_back(c - '0');
		}
		for (int i = 10; i <= 1000000; i++) {
			circle.push_back(i);
		}
		for (auto c = circle.begin(); c != circle.end(); c++) {
			positions.emplace(*c, c);
		}
		for (int i = 0; i < 10000000; i++) {
			move(circle, 1000000, positions);
			if (i % 10000 == 0) std::cout << "iteration: " << i << std::endl;
		}
		positions.clear();
		while (*circle.begin() != 1) {
			circle.push_back(circle.front());
			circle.pop_front();
		}
		std::cout << "Final answer (big): " << (long long) *std::next(circle.begin(), 1) * (long long)*std::next(circle.begin(), 2) << std::endl;
		auto circle_iter = circle.begin();
		for (int i = 0; i < 4; i++) {
			std::cout << *circle_iter++ << " ";
		}
		std::cout << std::endl;

		return EXIT_SUCCESS;
	}
}