#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Problems.h"
#include "FileUtil.h"
#include "StringUtil.h"


namespace AOC2020 {

	struct Range {
		unsigned long low;
		unsigned long high;
		unsigned long low2;
		unsigned long high2;
	};

	int Problem16() {
		std::ifstream infile("inputs/Problem16Input.txt");
		std::string line;
		std::vector<Range*> ranges;
		while (std::getline(infile, line) && line.size() > 0) {
			std::vector<std::string> bits;
			AOCUtils::splitString(line, bits, ' ');
			std::vector<std::string> rangeBits;
			unsigned long bitsSize = bits.size();
			Range* r = new Range();
			AOCUtils::splitString(bits[bitsSize - 1], rangeBits, '-');
			r->low = std::stol(rangeBits[0]);
			r->high = std::stol(rangeBits[1]);
			rangeBits.clear();
			AOCUtils::splitString(bits[bitsSize - 3], rangeBits, '-');
			r->low2 = std::stol(rangeBits[0]);
			r->high2 = std::stol(rangeBits[1]);
			ranges.push_back(r);
			rangeBits.clear();
		}

		std::vector<unsigned> myTicket;
		while (std::getline(infile, line) && line.size() > 0) {
			if (line == "your ticket:") continue;
			std::vector<std::string> ticketBits;
			AOCUtils::splitString(line, ticketBits, ',');
			for (auto s : ticketBits) myTicket.push_back(std::stol(s));
		}

		std::vector<std::vector<unsigned>> nearbyTickets;
		while (std::getline(infile, line) && line.size() > 0) {
			if (line == "nearby tickets:") continue;
			std::vector<std::string> ticketBits;
			AOCUtils::splitString(line, ticketBits, ',');
			std::vector<unsigned> nearbyTicket;
			for (std::string s : ticketBits) nearbyTicket.push_back(std::stol(s));
			nearbyTickets.push_back(nearbyTicket);
		}
		std::cout << "Found " << nearbyTickets.size() << " nearby tickets." << std::endl;

		std::vector<unsigned> matchNone;
		std::unordered_set<unsigned> matchNoneIndexes;
		unsigned count = 0;
		for (std::vector<unsigned> nbt : nearbyTickets) {
			for (auto v : nbt) {
				bool matchesNone = true;
				for (auto r : ranges) {
					if ((r->low <= v && r->high >= v) || (r->low2 <= v && r->high2 >= v)) {
						matchesNone = false;
						break;
					}
				}
				if (matchesNone) {
					matchNone.push_back(v);
					matchNoneIndexes.insert(count);
				}
			}
			count++;
		}
		std::vector<std::vector<unsigned>> nearbyTicketsFiltered;
		for (unsigned i = 0; i < nearbyTickets.size(); i++) {
			if (matchNoneIndexes.find(i) == matchNoneIndexes.end()) {
				/* not found */
				nearbyTicketsFiltered.push_back(nearbyTickets[i]);
			}
		}


		unsigned long long product = 0;
		for (auto m : matchNone) product += m;
		std::cout << "Product of totally invalid ticket values: " << product << std::endl;
		std::cout << "Possible valid tickets: " << nearbyTicketsFiltered.size() << std::endl;

		std::vector<std::unordered_set<unsigned>> possibleFields;
		for (auto i : myTicket) {
			std::unordered_set<unsigned> possible;
			for (unsigned j = 0; j < myTicket.size(); j++) {
				possible.insert(j);
			}
			possibleFields.push_back(possible);
		}

		for (std::vector<unsigned> nbd : nearbyTicketsFiltered) {
			for (unsigned i = 0; i < nbd.size(); i++) {
				for (unsigned j = 0; j < ranges.size(); j++) {
					if (possibleFields[i].find(j) != possibleFields[i].end()) {
						Range* r = ranges[j];
						unsigned v = nbd[i];
						if ((r->low > v || r->high < v) && (r->low2 > v || r->high2 < v)) {
							possibleFields[i].erase(j);
						}
					}
				}
			}
		}
		std::unordered_set<unsigned> seen;
		bool looping = true;
		while (looping) {
			bool allOne = true;
			for (std::unordered_set<unsigned>& s : possibleFields) {
				if (s.size() == 1) {
					seen.insert(*s.begin());
				}
				else {
					for (auto i : seen) s.erase(i);
					allOne = false;
				}
			}
			if (allOne) looping = false;
		}

		std::cout << "Possible order: " << std::endl;
		std::unordered_map<unsigned, unsigned> actualOrder;
		for (unsigned i = 0; i < possibleFields.size(); i++) {
			actualOrder[i] = *possibleFields[i].begin();
		}
		for (auto tkt : nearbyTicketsFiltered) {
			for (unsigned i = 0; i < tkt.size(); i++) {
				unsigned v = tkt[i];
				Range* r = ranges[actualOrder[i]];
				if ((r->low > v || r->high < v) && (r->low2 > v || r->high2 < v)) {
					std::cout << "Error: invalid ticket unexpected" << i << " " << v << " " << r->low << "-" << r->high << "," << r->low2 << "-" << r->high2 << std::endl;
				}
			}
		}
		product = 1;
		for (unsigned c : myTicket) std::cout << c << "/";
		std::cout << std::endl;
		for (unsigned i = 0; i < actualOrder.size(); i++) std::cout << i << "->" << actualOrder[i] << std::endl;
		for (unsigned i = 0; i < myTicket.size(); i++) {
			if (actualOrder[i] < 6) product *= myTicket[i];
		}

		std::cout << "Product of departure fields on my ticket: " << product << std::endl;

		for (auto r : ranges) delete r;
		return EXIT_SUCCESS;
	}
}