#include <iostream>
#include <queue>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "FileUtil.h"
#include "Problems.h"
#include "StringUtil.h"


const std::regex bagEntryRegex("(\\w+ \\w+) bags contain ((?:\\d+ \\w+ \\w+ bags?, )*)((?:\\d+ \\w+ \\w+|no other) bags?).");
const std::regex singleBagRegex("\\s*(\\d+ \\w+ \\w+) bags?\\s*");

namespace AOC2020 {

	struct BagQuantity {
		std::string color;
		int count;
	};

	typedef std::unordered_map<std::string, std::vector<BagQuantity>> Graph;

	BagQuantity GetQuantity(const std::string& bagdesc) {
		// std::cout << "GetQuantity(" << bagdesc << ")" << std::endl;
		BagQuantity bg;
		std::vector<std::string> v;
		AOCUtils::splitString(bagdesc, v, ' ');
		bg.color = v[1] + " " + v[2];
		bg.count = std::stoi(v[0]);
		return bg;
	}

	void _parseInput(const std::vector<std::string>& input, Graph& target) {
		for (auto line : input) {
			std::smatch s;
			std::regex_search(line, s, bagEntryRegex);
			std::string key = s[1].str();
			std::string manybags = s[2].str();
			std::string lastbag = s[3].str();
			std::vector<std::string> stringbits;
			AOCUtils::splitString(manybags, stringbits, ',');
			std::vector<BagQuantity> value;
			std::smatch res;
			for (auto i = stringbits.begin(); i != stringbits.end(); ++i) {
				if (std::regex_search(*i, res, singleBagRegex)) {
					value.push_back(GetQuantity(res[1].str()));
				}
			}
			if (std::regex_search(lastbag, res, singleBagRegex)) {
				value.push_back(GetQuantity(res[1].str()));
			}
			// std::cout << "Line: " << line << std::endl;
			target[key] = value;
			for (int i = 0; i < 15; i++) {
				// std::cout << s[i].str() << "/";
			}
			// std::cout << std::endl;
			// std::cout << "got: ";
			// std::cout << key << "|";
			// for (auto i = value.begin(); i != value.end(); ++i) {
		    //    std::cout << (*i).color << "-";
			// }
			// std::cout << std::endl;
		}
	}

	bool searchBag(const std::string& color, const Graph& bags) {
		std::queue<std::pair<std::string, int>> colors;
		int depth = 0;
		colors.push(std::make_pair(color, depth));
		bool notfirst = false;
		while (colors.size() > 0) {
			std::string current = colors.front().first;
			int currentDepth = colors.front().second;
			colors.pop();
			// for (int k = 0; k < currentDepth; k++) std::cout << ">";
			if (current == "shiny gold" && notfirst) return true;
			notfirst = true;
			auto res = *(bags.find(current));
			auto newcolors = res.second;
			for (auto i = newcolors.begin(); i != newcolors.end(); ++i) {
				colors.push(std::make_pair((*i).color, currentDepth + 1));
			}
		}
		return false;
	}

	int _recursiveCount(const Graph& g, const std::string& start) {
		int retval = 1;
		auto res = g.find(start);
		if (res == g.end()) {
			std::cout << "Error: " << start << " not found in graph. " << std::endl;
		}
		if ((*res).second.size() == 0) {
			return retval;
		}
		for (auto i = (*res).second.begin(); i != (*res).second.end(); ++i) {
			retval += _recursiveCount(g, (*i).color) * (*i).count;
		}
		return retval;
	}

	int Problem7() {
		std::string filename("inputs/Problem7InputTest.txt");
		std::ifstream inputFile = AOCUtils::GetFile(filename);
		std::string line;
		std::vector<std::string> lines;
		Graph bags;
		while (std::getline(inputFile, line)) {
			lines.push_back(line);
		}
		_parseInput(lines, bags);

		std::unordered_set<std::string> seenColors;
		for (auto i = bags.begin(); i != bags.end(); ++i) {
			if (searchBag((*i).first, bags)) {
				seenColors.insert((*i).first);
			}
		}

		/*
		for (auto i = bags.begin(); i != bags.end(); ++i) {
			std::cout << (*i).first << std::endl;
			std::cout << "  ";
			for (auto j = (*i).second.begin(); j != (*i).second.end(); ++j) {
				std::cout << (*j).count << " " << (*j).color << " | ";
			}
			std::cout << std::endl;
		}

		std::cout << "Possible colors: " << std::endl;
		for (auto i = seenColors.begin(); i != seenColors.end(); ++i) {
			std::cout << *i << std::endl;
		}
		*/
		std::cout << "Number of bags with shiny gold potential: " << seenColors.size() << std::endl;

		std::cout << "A shiny gold bag must have " << _recursiveCount(bags, "shiny gold") - 1 << " bags." << std::endl;

		return EXIT_SUCCESS;
	}
}