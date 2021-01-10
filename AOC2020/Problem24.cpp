#include <sstream>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <utility>

#include "FileUtil.h"
#include "Problems.h"


namespace AOC2020 {

	template<typename T1, typename T2>
	struct HexCoord {
		T1 e;  // E
		T2 ne;  // NE
		 
		HexCoord(T1 _e, T2 _ne) {
			e = _e;
			ne = _ne;
		}

		bool operator==(const HexCoord& h) const {
			return (e == h.e) && (ne == h.ne);
		}
	};

	struct HexCoordHash {
		template<class T1, class T2>
		std::size_t operator() (const HexCoord<T1, T2>& h) const {
			std::stringstream ss;
			ss << h.e << ":" << h.ne;
			auto result = std::hash<std::string>{}(ss.str());
			return result;
		}
	};

	template<class T1, class T2>
	std::ostream& operator<<(std::ostream& out, const HexCoord<T1, T2>& h) {
		out << "HexCoord(" << h.e << "," << h.ne << ")";
		return out;
	}

	HexCoord<int, int> readHexCoord(const std::string& instring) {
		char parsing = 'x';
		HexCoord<int, int> h(0, 0);
		for (auto c : instring) {
			switch (c) {
			case 'n':
			case 's': parsing = c; break;
			case 'e':
				if (parsing == 'x') {
					h.e++;
				}
				else if (parsing == 'n') {
					h.ne++;
				}
				else if (parsing == 's') {
					h.ne--; h.e++;
				};
				parsing = 'x';
				break;
			case 'w':
				if (parsing == 'x') {
					h.e--;
				}
				else if (parsing == 'n') {
					h.ne++; h.e--;
				}
				else if (parsing == 's') {
					h.ne--;
				};
				parsing = 'x';
				break;
			}
		}
		return h;
	}

	int countBlackNeighbors(const std::unordered_map<HexCoord<int, int>, bool, HexCoordHash>& tileState, int eCoord, int neCoord) {
		int count = 0;
		HexCoord<int, int> ne(eCoord, neCoord + 1);
		HexCoord<int, int> e(eCoord + 1, neCoord);
		HexCoord<int, int> w(eCoord - 1, neCoord);
		HexCoord<int, int> se(eCoord + 1, neCoord - 1);
		HexCoord<int, int> sw(eCoord, neCoord - 1);
		HexCoord<int, int> nw(eCoord - 1, neCoord + 1);
		if (tileState.find(ne) != tileState.end() && tileState.find(ne)->second) count++;
		if (tileState.find(e) != tileState.end() && tileState.find(e)->second) count++;
		if (tileState.find(nw) != tileState.end() && tileState.find(nw)->second) count++;
		if (tileState.find(se) != tileState.end() && tileState.find(se)->second) count++;
		if (tileState.find(sw) != tileState.end() && tileState.find(sw)->second) count++;
		if (tileState.find(w) != tileState.end() && tileState.find(w)->second) count++;
		return count;
	}

	void extend(std::unordered_map<HexCoord<int, int>, bool, HexCoordHash>& tileState) {
		for (auto p : tileState) {
			if (!p.second && countBlackNeighbors(tileState, p.first.e, p.first.ne) == 0) continue;
			HexCoord<int, int> h = p.first;
			HexCoord<int, int> e(h.e + 1, h.ne);
			HexCoord<int, int> w(h.e - 1, h.ne);
			HexCoord<int, int> nw(h.e - 1, h.ne + 1);
			HexCoord<int, int> ne(h.e, h.ne + 1);
			HexCoord<int, int> se(h.e + 1, h.ne - 1);
			HexCoord<int, int> sw(h.e, h.ne - 1);
			tileState.emplace(e, false);
			tileState.emplace(w, false);
			tileState.emplace(ne, false);
			tileState.emplace(se, false);
			tileState.emplace(nw, false);
			tileState.emplace(sw, false);
		}
	}

	void iterate(std::unordered_map<HexCoord<int, int>, bool, HexCoordHash>& tileState) {
		extend(tileState);
		std::unordered_map<HexCoord<int, int>, bool, HexCoordHash> newTileState(tileState);
		for (auto p : tileState) {
			int blackCount = countBlackNeighbors(tileState, p.first.e, p.first.ne);
			if (p.second && (blackCount == 0 || blackCount > 2)) {
				newTileState.erase(p.first);
				newTileState.emplace(p.first, false);
			}
			else if ((!p.second) && (blackCount == 2)) {
				newTileState.erase(p.first);
				newTileState.emplace(p.first, true);
			}
		}
		tileState.clear();
		for (auto p : newTileState) {
			tileState.insert(p);
		}
		extend(tileState);
	}

	unsigned int countBlackTiles(const std::unordered_map<HexCoord<int, int>, bool, HexCoordHash>& tileState) {
		unsigned int count = 0;
		for (auto p : tileState) {
			if (p.second) count++;
		}
		return count;
	}

	void printTiles(const std::unordered_map < HexCoord<int, int>, bool, HexCoordHash>& tileState) {
		/* noop */
		int minX = 0, minY = 0, maxX = 0, maxY = 0;
		for (auto p : tileState) {
			if (p.first.e < minX) minX = p.first.e;
			if (p.first.e > maxX) maxX = p.first.e;
			if (p.first.ne < minY) minY = p.first.ne;
			if (p.first.ne > maxY) maxY = p.first.ne;
		}
		int offset = maxY - minY;
		for (int j = maxY; j >= minY; j--) {
			std::cout << std::setw(5) << j;
			for (int k = 0; k < offset; k++) std::cout << " ";
			for (int i = minX; i <= maxX; i++) {
				HexCoord<int ,int> h(i, j);
				if (tileState.find(h) != tileState.end()) {
					if (tileState.find(h)->second) std::cout << "#";
					else std::cout << ".";
				}
				else {
					std::cout << " ";
				}
				std::cout << " ";
			}
			std::cout << std::endl;
			offset--;
		}
	}

	int Problem24() {
		std::ifstream infile = AOCUtils::GetFile("inputs/Problem24Input.txt");
		std::string line;
		std::unordered_map<HexCoord<int, int>, bool, HexCoordHash> tileState;
		/* true = black */
		while (std::getline(infile, line)) {
			HexCoord<int, int> h = readHexCoord(line);
			if (tileState.find(h) == tileState.end()) tileState.emplace(h, false);
			bool currentValue = tileState.find(h)->second;
			tileState.erase(h);
			tileState.emplace(h, !currentValue);
		}
		unsigned int count = countBlackTiles(tileState);
		std::cout << "Total # of black tiles: " << count << std::endl;
		std::string input;
		extend(tileState);
		std::cout << "Starting position: " << std::endl;
		printTiles(tileState);
		bool run = false;
		for (int i = 1; i <= 100; i++) {
			iterate(tileState);
			count = countBlackTiles(tileState);
			std::cout << "Iteration #" << i << ": " << count << std::endl;
			printTiles(tileState);
			if (!run) {
				std::cin >> input;
				if (input == "stop") break;
				if (input == "run") {
					run = true;
				}
			}
		}
		return EXIT_SUCCESS;
	}
}