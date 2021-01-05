#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "FileUtil.h"
#include "Problems.h"
#include "StringUtil.h"


namespace AOC2020 {

	struct Rule;

	typedef std::vector<Rule>::size_type RuleIndex;
	typedef std::string::size_type StringIndex;

	struct Rule {
		std::vector<std::vector<RuleIndex>> rulelist;
		char expectedChar;
		unsigned int ruleNumber;
	};
	
	std::ostream& operator<<(std::ostream& out, const Rule& r) {
		out << "Rule(";
		if (r.expectedChar != '\0') {
			std::cout << "\"" << r.expectedChar << "\"";
		}
		else {
			for (const auto& rl : r.rulelist) {
				for (const auto& r : rl) {
					std::cout << r << "/";
				}
				std::cout << ":::";
			}
		}
		std::cout << ")";
		return out;
	}

	Rule* makeRule(const std::string& input) {
		/* if rulelist has zero length, its a terminal rule and must have an expectedChar. */
		Rule* r = new Rule();
		r->expectedChar = '\0';
		std::vector<std::string> bits;
		AOCUtils::splitString(input, bits, ':');
		r->ruleNumber = std::stoi(bits[0]);
		if (bits.size() < 2) std::cout << "invalid bits: " << input << std::endl;
		std::vector<std::string> rulebits;
		if (bits[1].substr(0, 2) == " \"") {
			r->expectedChar = bits[1][2];
			return r;
		}

		AOCUtils::splitString(bits[1], rulebits, '|');
		for (const auto& s : rulebits) {
			std::vector<std::string> otherrules;
			AOCUtils::splitString(s, otherrules, ' ');
			std::vector<RuleIndex> finalOtherRules;
			for (const auto& sr : otherrules) {
				if (sr.size() > 0 && sr[0] != ' ') finalOtherRules.push_back(std::stoull(sr));
			}
			r->rulelist.push_back(finalOtherRules);
		}
		return r;
	}

	void matchRule(
		RuleIndex r,
		const std::unordered_map<int, Rule*>& rules,
		std::unordered_set<StringIndex>& matches,
		const std::string& input) {
		if (r >= rules.size()) {
			std::cout << "Invalid Rule Index: " << r << " ,max is " << rules.size() << std::endl;
		}
		Rule* rule = rules.find(r)->second;
		// std::cout << "Matching rule: " << r << ": " << *rule << " input=" << input << std::endl;

		if (rule->expectedChar != '\0') {
			if (input.size() >= 1 && input[0] == rule->expectedChar) {
				matches.insert(1);
			}
			return;
		}
		else {
			int counter = 0;
			for (const auto& ruleSequence : rule->rulelist) {
				std::string currentInput = input;
				std::unordered_set<StringIndex> currentOffsets;
				for (std::vector<Rule>::size_type ii = 0; ii < ruleSequence.size(); ii++) {
					if (ii == 0) {
						matchRule(ruleSequence[ii], rules, currentOffsets, currentInput);
					}
					else {
						std::unordered_set<StringIndex> lastOffsets;
						for (auto o : currentOffsets) {
							lastOffsets.insert(o);
						}
						currentOffsets.clear();
						for (const auto& offset : lastOffsets) {
							std::string::size_type strlength = currentInput.size() - offset;
							std::unordered_set<StringIndex> newOffsets;
							matchRule(ruleSequence[ii], rules, newOffsets, currentInput.substr(offset, strlength));
							for (auto newOffset : newOffsets) {
								currentOffsets.insert(offset + newOffset);
							}
						}
					}
				}
				for (const auto si : currentOffsets) {
					matches.insert(si);
				}
				currentOffsets.clear();
			}
		}
	}

	int Problem19() {
		std::ifstream infile = AOCUtils::GetFile("inputs/Problem19Input.txt");
		std::string line;
		std::vector<std::string> lines;
		std::unordered_map<int, Rule*> rules;

		while (std::getline(infile, line) && line.size() > 0) {
			Rule* r = makeRule(line);
			rules.emplace(r->ruleNumber, r);
		}

		RuleIndex rii = 0;

		unsigned long matchcount = 0;
		std::vector<std::string> inputs;
		while (std::getline(infile, line) && line.size() > 0) {
			inputs.push_back(line);
		}
		for (const auto& l : inputs) {
			std::unordered_set<StringIndex> matches;
			matchRule(0, rules, matches, l);
			if (matches.find(l.size()) != matches.end()) matchcount++;
		}
		std::cout << "Total " << matchcount << " matches found." << std::endl;

		std::cout << "Updating rules 8 and 11... " << std::endl;
		delete rules[8];
		delete rules[11];
		rules[8] = makeRule("8: 42 | 42 8");
		rules[11] = makeRule("11: 42 31 | 42 11 31");

		matchcount = 0;
		for (const auto& l : inputs) {
			std::unordered_set<StringIndex> matches;
			matchRule(0, rules, matches, l);
			if (matches.find(l.size()) != matches.end()) matchcount++;
		}
		std::cout << "Total " << matchcount << " matches found." << std::endl;
		for (auto rp : rules) delete rp.second;

		return EXIT_SUCCESS;
	}
}