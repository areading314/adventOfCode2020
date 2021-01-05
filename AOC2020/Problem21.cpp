#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "FileUtil.h"
#include "Problems.h"
#include "StringUtil.h"

namespace AOC2020 {

	typedef std::unordered_map<std::string, std::unordered_set<std::string>> ConstraintsType;
	typedef std::pair<std::vector<std::string>, std::vector<std::string>> PairType;
	typedef std::vector <PairType> VecPair;

	void printConstraints(const ConstraintsType& constraints) {
		for (const auto& p : constraints) {
			std::cout << p.first << " -> ";
			for (const auto& i : p.second) {
				std::cout << i << " ";
			}
			std::cout << std::endl;
		}

	}

	void parseLine(std::string line, VecPair& outputs) {
		std::vector<std::string> bits;
		std::vector<std::string> cleanBits;
		AOCUtils::splitString(line, bits, ' ');
		for (auto word : bits) {
			int startLetters = -1;
			int endLetters = -1;
			for (int i = 0; i < word.size(); i++) {
				if (word[i] >= 'a' && word[i] <= 'z' && startLetters == -1) startLetters = i;
				if ((word[i] < 'a' || word[i] > 'z') && startLetters != -1 && endLetters == -1) endLetters = i;
			}
			if (endLetters == -1) endLetters = word.size();
			word.erase(word.begin() + endLetters, word.end());
			word.erase(word.begin(), word.begin() + startLetters);
			cleanBits.push_back(word);
		}
		bool firstBit = true;
		PairType pt;
		for (auto w : cleanBits) {
			if (w == "contains") {
				firstBit = false;
				continue;
			}
			if (firstBit) {
				pt.first.push_back(w);
			}
			else {
				pt.second.push_back(w);
			}
		}
		outputs.push_back(pt);
	}

	int Problem21() {
		std::ifstream infile = AOCUtils::GetFile("inputs/Problem21Input.txt");
		std::string line;
		VecPair data;
		while (std::getline(infile, line)) {
			parseLine(line, data);
		}
		ConstraintsType constraints;
		std::unordered_set<std::string> allIngredients;
		std::unordered_set<std::string> allAllergens;

		for (const auto& p : data) {
			for (const auto& i : p.first) {
				allIngredients.insert(i);
			}
			for (const auto& a : p.second) {
				allAllergens.insert(a);
			}
		}

		for (const auto& a : allAllergens) {
			for (const auto& i : allIngredients) {
				constraints[a].insert(i);
			}
		}

		for (const auto& d : data) {
			for (const auto& a : d.second) {
				for (const auto& i : allIngredients) {
					if (std::find(d.first.begin(), d.first.end(), i) == d.first.end()) {
						constraints[a].erase(i);
					}
				}
			}
		}

		bool changed = true;
		int iteration = 0;
		while (changed) {
			changed = false;
			for (const auto& p : constraints) {
				if (p.second.size() == 1) {
					/* remove  */
					std::string ingredient = *(p.second.begin());
					for (auto& i : constraints) {
						if (i.second.size() > 1 && i.second.find(ingredient) != i.second.end()) {
							i.second.erase(ingredient);
							changed = true;
						}
					}
				}
			}
			std::cout << "Iteration: " << iteration++ << std::endl;
			printConstraints(constraints);
		}

		printConstraints(constraints);

		std::unordered_map<std::string, std::string> ingredientsContainingAllergens;
		for (const auto& p : constraints) {
			if (p.second.size() == 1) ingredientsContainingAllergens.emplace(*p.second.begin(), p.first);
		}

		int finalCount = 0;
		for (const auto& d : data) {
			for (const auto& i : d.first) {
				if (ingredientsContainingAllergens.find(i) == ingredientsContainingAllergens.end()) {
					finalCount++;
				}
			}
		}
		
		std::vector<std::string> ingredientsV;
		for (const auto& i : ingredientsContainingAllergens) ingredientsV.push_back(i.first);
		for (const auto& i : ingredientsV) std::cout << i << ",";

		std::sort(ingredientsV.begin(), ingredientsV.end(),
			[&](const std::string& i1, const std::string& i2) {
				std::string a1 = ingredientsContainingAllergens.find(i1)->second;
				std::string a2 = ingredientsContainingAllergens.find(i2)->second;
				std::cout << "a1=" << a1 << " a2=" << a2 << " returning " << a2.compare(a1) << std::endl;
				return a2.compare(a1) > 0;
			});

		std::cout << "Final Count of ingredients not containing allergens: " << finalCount << std::endl;
		for (const auto& i : ingredientsV) std::cout << i << ",";
		std::cout << std::endl;


		return EXIT_SUCCESS;
	}
}