#include <bitset>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "FileUtil.h"
#include "Problems.h"
#include "StringUtil.h"


namespace AOC2020 {

	static const std::array<std::array<std::uint8_t, 8>, 8> rotationMatrix{ {
		{0, 1, 2, 3, 4, 5, 6, 7},
		{3, 0, 1, 2, 7, 4, 5, 6},
		{2, 3, 0, 1, 6, 7, 4, 5},
		{1, 2, 3, 0, 5, 6, 7, 4},
		{4, 5, 6, 7, 0, 1, 2, 3},
		{7, 4, 5, 6, 3, 0, 1, 2},
		{6, 7, 4, 5, 2, 3, 0, 1},
		{5, 6, 7, 4, 1, 2, 3, 0}
	}};

	void flip(std::array<std::bitset<96>, 96>& input) {
		std::array<std::bitset<96>, 96> tmp;
		for (int ii = 0; ii < input.size(); ii++) {
			for (int jj = 0; jj < input[ii].size(); jj++) {
				tmp[ii][95 - jj] = input[ii][jj];
			}
		}
		for (int ii = 0; ii < input.size(); ii++) {
			for (int jj = 0; jj < input[ii].size(); jj++) {
				input[ii][jj] = tmp[ii][jj];
			}
		}
	}

	void rotate90(std::array<std::bitset<96>, 96>& input) {
		std::array<std::bitset<96>, 96> tmp;
		for (int ii = 0; ii < input.size(); ii++) {
			for (int jj = 0; jj < input[ii].size(); jj++) {
				tmp[jj][95 - ii] = input[ii][jj];
			}
		}
		for (int ii = 0; ii < input.size(); ii++) {
			for (int jj = 0; jj < input[ii].size(); jj++) {
				input[ii][jj] = tmp[ii][jj];
			}
		}
	}

	int seaRoughness(const std::array<std::bitset<20>, 3>& seaMonster,
		const std::array<std::bitset<96>, 96> sea) {
		std::array<std::bitset<96>, 96> sightings;
		std::array<std::bitset<96>, 96> roughness;
		bool foundMonsters = false;
		for (int ii = 0; ii < 96; ii++) {
			for (int jj = 0; jj < 96; jj++) {
				if (ii >= 3 && jj >= 20) {
					bool matching = true;
					for (int mm = 0; mm < 3 && matching; mm++) {
						for (int nn = 0; nn < 20 && matching; nn++) {
							if (!seaMonster[mm][nn]) {
								continue;
							} else if (sea[ii - 3 + mm][jj - 20 + nn]) {
								continue;
							}
							else {
								matching = false;
							}
						}
					}
					if (matching) {
						std::cout << "Found sea monster at: " << ii << ", " << jj << std::endl;
						foundMonsters = true;
						for (int mm = 0; mm < 3; mm++) {
							for (int nn = 0; nn < 20; nn++) {
								sightings[ii - 3 + mm][jj - 20 + nn] = sightings[ii - 3 + mm][jj - 20 + nn] || seaMonster[mm][nn];
							}
						}
					}
				}
			}
		}
		for (int ii = 0; ii < 96; ii++) {
			for (int jj = 0; jj < 96; jj++) {
				roughness[ii][jj] = (sea[ii][jj] && !sightings[ii][jj]);
			}
		}
		if (foundMonsters) {
			for (int ii = 0; ii < 96; ii++) {
				for (int jj = 0; jj < 96; jj++) {
					std::cout << (sightings[ii][jj] ? 'O' : (sea[ii][jj] ? '#' : '.'));
				}
				std::cout << std::endl;
			}
		}
		int sum = 0;
		for (int ii = 0; ii < 96; ii++) {
			for (int jj = 0; jj < 96; jj++) {
				if (roughness[ii][jj]) sum++;
			}
		}
		return sum;
	}

	struct PuzzlePiece {
		std::uint16_t number;
		std::vector<std::bitset<10>> sides;
		std::array<std::bitset<10>, 10> elements;
		std::uint8_t orientation = 0;
		std::uint8_t positionX = 0;
		std::uint8_t positionY = 0;
		bool fixed = false;

		std::bitset<10> getSide(std::uint8_t sideNumber) const;
		std::uint16_t getMatchingPieceAtSide(int sideNumber, 
			const std::unordered_map<std::bitset<10>, std::vector<std::uint16_t>>& edgeMap) const;
		bool getValue(std::uint8_t x, std::uint8_t y, bool removeEdge = false) const;
	};

	bool PuzzlePiece::getValue(std::uint8_t x, std::uint8_t y, bool removeEdge) const {
		if (removeEdge) {
			switch (orientation) {
			case(0): return elements[y + 1][x + 1];
			case(1): return elements[8 - x][y + 1];
			case(2): return elements[8 - y][8 - x];
			case(3): return elements[x + 1][8 - y];
			case(4): return elements[y + 1][8 - x];
			case(5): return elements[8 - x][8 - y];
			case(6): return elements[8 - y][x + 1];
			case(8): return elements[x + 1][y + 1];
			default: std::cout << "Invalid orientation: " << orientation << std::endl;
				return false;
			}

		}
		switch (orientation) {
		case(0): return elements[y][x];
		case(1): return elements[9 - x][y];
		case(2): return elements[9 - y][9 - x];
		case(3): return elements[x][9 - y];
		case(4): return elements[y][9 - x];
		case(5): return elements[9 - x][9 - y];
		case(6): return elements[9 - y][x];
		case(7): return elements[x][y];
		default: std::cout << "Invalid orientation: " << orientation << std::endl;
			return false;
		}
	}

	std::ostream& operator<<(std::ostream& out, const PuzzlePiece& p) {
		out << "PuzzlePiece(";
		out << p.number << ")" << std::endl;
		for (int ii = 0; ii < 10; ii++) {
			for (int jj = 0; jj < 10; jj++) {
				out << p.getValue(jj, ii) ? '#' : '.';
			}
			out << std::endl;
		}
		std::cout << std::endl;
		return out;
	}

	std::bitset<10> PuzzlePiece::getSide(std::uint8_t sideNumber) const {
		if (orientation >= 8 || sideNumber >= 8 || orientation < 0 || sideNumber < 0) std::cout << "Invalid inputs: " << (int) orientation << " " << (int) sideNumber << std::endl;
		std::uint8_t sideIndex = rotationMatrix[orientation][sideNumber];
		return sides[sideIndex];
	}

	std::uint16_t PuzzlePiece::getMatchingPieceAtSide(int sideNumber, 
		const std::unordered_map<std::bitset<10>, std::vector<std::uint16_t>>& edgeMap) const {
		std::bitset<10> sideData = getSide(sideNumber);
		auto others = edgeMap.find(sideData);
		if (others == edgeMap.end()) return 0;
		else {
			for (auto o : others->second) {
				if (o != number) return o;
			}
		}
		return 0;
	}

	void arrangePieces(
		const std::unordered_map<std::uint16_t, std::unordered_set<std::uint16_t>>& adjacency,
		std::unordered_map<std::uint16_t, PuzzlePiece>& pieceLookup,
		std::vector<std::vector<std::uint16_t>>& pieceArray,
		std::unordered_map<std::bitset<10>, std::vector<std::uint16_t>>& edgeMap) {

		// find top left piece
		std::uint16_t topLeftPiece;
		for (auto p : adjacency) {
			if (p.second.size() == 2) {
				topLeftPiece = p.first;
				break;
			}
		}
		auto topLeftPieceP = pieceLookup.find(topLeftPiece);
		if (topLeftPieceP == pieceLookup.end()) {
			std::cout << "Couldn't find top left piece: " << topLeftPiece << std::endl;
		}

		// arrange first piece
		bool done = false;
		while (!done) {
			std::bitset<10> northSide = topLeftPieceP->second.getSide(0);
			std::bitset<10> westSide = topLeftPieceP->second.getSide(3);
			if (edgeMap.find(northSide) == edgeMap.end() || edgeMap.find(westSide) == edgeMap.end()) {
				std::cout << "Couldn't find edges: " << northSide << ", " << westSide << std::endl;
			}
			auto northCount = edgeMap.find(northSide)->second.size();
			auto westCount = edgeMap.find(westSide)->second.size();
			if (northCount != 1 || westCount != 1) {
				topLeftPieceP->second.orientation++;
			}
			else {
				done = true;
				topLeftPieceP->second.positionX = 0;
				topLeftPieceP->second.positionY = 0;
				topLeftPieceP->second.fixed = true;
			}
		}

		bool doneRow = false;
		bool doneAll = false;
		auto currentPiece = topLeftPieceP;
		auto lastPiece = currentPiece;
		auto lastRowFirstPiece = currentPiece;
		while (!doneAll) {
			doneRow = false;
			lastRowFirstPiece = currentPiece;
			while (!doneRow) {
				lastPiece = currentPiece;
				std::uint16_t currentPieceNumber = currentPiece->second.getMatchingPieceAtSide(1, edgeMap);
				currentPiece = pieceLookup.find(currentPieceNumber);
				if (currentPiece == pieceLookup.end()) std::cout << "Couldnt find: " << currentPieceNumber << std::endl;
				while (currentPiece->second.getMatchingPieceAtSide(3, edgeMap) != lastPiece->second.number) {
					currentPiece->second.orientation++;
				}
				currentPiece->second.positionX = lastPiece->second.positionX + 1u;
				currentPiece->second.positionY = lastPiece->second.positionY;
				currentPiece->second.fixed = true;
				if (currentPiece->second.getMatchingPieceAtSide(1, edgeMap) == 0) {
					doneRow = true;
				}
			}
			std::uint16_t newRowPieceNumber = lastRowFirstPiece->second.getMatchingPieceAtSide(2, edgeMap);
			if (newRowPieceNumber == (std::uint16_t) 0) {
				doneAll = true;
			}
			else {
				currentPiece = pieceLookup.find(newRowPieceNumber);
				while (currentPiece->second.getMatchingPieceAtSide(0, edgeMap) != lastRowFirstPiece->second.number) {
					currentPiece->second.orientation++;
				}
				currentPiece->second.positionX = lastRowFirstPiece->second.positionX;
				currentPiece->second.positionY = lastRowFirstPiece->second.positionY + 1;
				currentPiece->second.fixed = true;
			}
		}
	}

	bool isEdge(int x, int y, int xSize, int ySize) {
		return ((x == xSize - 1) || (x == 0) || (y == ySize - 1) || (y == 0));
	}

	bool isCorner(int x, int y, int xSize, int ySize) {
		return ((x == 0 || x == xSize - 1) && (y == 0 || y == ySize - 1));
	}

	void printFullArray(const std::array<std::bitset<120>, 120> data) {
		for (int jj = 0; jj < data.size(); jj++) {
			for (int ii = 0; ii < data[jj].size(); ii++) {
				std::cout << (data[jj][ii] ? "#" : "."); // << " ";
				if (ii % 10 == 9) std::cout << "|";
			}
			std::cout << std::endl;
			if (jj % 10 == 9) {
				for (int ii = 0; ii < 120; ii++) {
					std::cout << '-';
					if (ii % 10 == 9) std::cout << '+';
				}
				std::cout << std::endl;
			}
		}
	}

	void printSea(const std::array<std::bitset<96>, 96> data) {
		for (int jj = 0; jj < data.size(); jj++) {
			for (int ii = 0; ii < data[jj].size(); ii++) {
				std::cout << (data[jj][ii] ? "#" : "."); // << " ";
				if (ii % 8 == 7) std::cout << "|";
			}
			std::cout << std::endl;
			if (jj % 8 == 7) {
				for (int ii = 0; ii < 96; ii++) {
					std::cout << '-';
					if (ii % 8 == 7) std::cout << '+';
				}
				std::cout << std::endl;
			}
		}
	}

	bool ReadPuzzlePiece(std::ifstream& infile, PuzzlePiece& pp) {
		std::string line;
		std::getline(infile, line);
		if (line.size() < 4) return false;
		if (line.substr(0, 4) != "Tile") std::cout << "Invalid puzzle piece: " << line << std::endl;
		std::cout << "line: " << line << std::endl;
		pp.number = std::stoi(line.substr(5, 4));

		std::vector<std::string> pieces;
		while (std::getline(infile, line) && line.size() > 0) {
			pieces.push_back(line);
		}
		if (pieces.size() != 10) return false;

		for (int ii = 0; ii < 8; ii++) {
			std::bitset<10> bs;
			pp.sides.push_back(bs);
		}

		for (int ii = 0; ii < 10; ii++) {
			char c = pieces[0][ii];
			pp.sides[0][ii] = c == '#' ? 1 : 0;
		}
		for (int ii = 0; ii < 10; ii++) {
			char c = pieces[ii][9];
			pp.sides[1][ii] = c == '#' ? 1 : 0;
		}
		for (int ii = 0; ii < 10; ii++) {
			char c = pieces[9][9 - ii];
			pp.sides[2][ii] = c == '#' ? 1 : 0;
		}
		for (int ii = 0; ii < 10; ii++) {
			char c = pieces[9 - ii][0];
			pp.sides[3][ii] = c == '#' ? 1 : 0;
		}
		for (int ii = 0; ii < 10; ii++) {
			char c = pieces[0][9 - ii];
			pp.sides[4][ii] = c == '#' ? 1 : 0;
		}
		for (int ii = 0; ii < 10; ii++) {
			char c = pieces[ii][0];
			pp.sides[5][ii] = c == '#' ? 1 : 0;
		}
		for (int ii = 0; ii < 10; ii++) {
			char c = pieces[9][ii];
			pp.sides[6][ii] = c == '#' ? 1 : 0;
		}
		for (int ii = 0; ii < 10; ii++) {
			char c = pieces[9 - ii][9];
			pp.sides[7][ii] = c == '#' ? 1 : 0;
		}
		for (int ii = 0; ii < 10; ii++) {
			for (int jj = 0; jj < 10; jj++) {
				char c = pieces[ii][jj];
				pp.elements[ii][jj] = c == '#' ? true : false;
			}
		}

		return true;
	}

	int countMatchingPieces(
		const PuzzlePiece& pp,
		const std::array<std::array<std::uint16_t, 12>, 12>& piecesByPosition,
		std::unordered_map<std::bitset<10>, std::vector<std::uint16_t>>& edgeMap) {
		int foundMatches = 0;
		if (pp.positionY > 0 && (pp.getMatchingPieceAtSide(0, edgeMap) == piecesByPosition[pp.positionY - 1][pp.positionX])) {
			foundMatches++;
		}
		if (pp.positionX > 0 && (pp.getMatchingPieceAtSide(3, edgeMap) == piecesByPosition[pp.positionY][pp.positionX - 1])) {
			foundMatches++;
		}
		if (pp.positionY < 11 && (pp.getMatchingPieceAtSide(2, edgeMap) == piecesByPosition[pp.positionY + 1][pp.positionX])) {
			foundMatches++;
		}
		if (pp.positionX < 11 && (pp.getMatchingPieceAtSide(1, edgeMap) == piecesByPosition[pp.positionY][pp.positionX + 1])) {
			foundMatches++;
		}

		return foundMatches;
	}

	bool checkPiece(
		std::uint16_t piece,
		const std::unordered_map<std::uint16_t, PuzzlePiece>& pieceLookup,
		const std::array<std::array<std::uint16_t, 12>, 12>& piecesByPosition,
		std::unordered_map<std::bitset<10>, std::vector<std::uint16_t>>& edgeMap) {
		auto pp = pieceLookup.find(piece)->second;
		int expectedMatches;
		if (isCorner(pp.positionX, pp.positionY, 12, 12)) {
			expectedMatches = 2;
		}
		else if (isEdge(pp.positionX, pp.positionY, 12, 12)) {
			expectedMatches = 3;
		}
		else {
			expectedMatches = 4;
		}
		return countMatchingPieces(pp, piecesByPosition, edgeMap) == expectedMatches;
	}

	int Problem20() {
		std::ifstream infile = AOCUtils::GetFile("inputs/Problem20Input.txt");
		std::vector<PuzzlePiece> pieces;
		bool done = false;
		while (!done) {
			PuzzlePiece pp;
			done = !ReadPuzzlePiece(infile, pp);
			if (!done) pieces.push_back(pp);
		}
		std::cout << "Pieces.size()" << pieces.size() << std::endl;

		std::unordered_map<std::uint16_t, PuzzlePiece> pieceLookup;
		std::unordered_map<std::bitset<10>, std::vector<std::uint16_t>> edgeMap;
		for (const auto& p : pieces) {
			pieceLookup[p.number] = p;
			for (const auto& s : p.sides) {
				if (edgeMap.find(s) == edgeMap.end()) {
					std::vector<std::uint16_t> newVec;
					edgeMap.emplace(s, newVec);
				}
				edgeMap[s].push_back(p.number);
			}
			std::cout << p << std::endl;
		}

		std::unordered_map<std::uint16_t, std::unordered_set<uint16_t>> adjacent;
		for (const auto& pm : edgeMap) {
			for (const auto u : pm.second) {
				if (adjacent.find(u) == adjacent.end()) {
					std::unordered_set<uint16_t> newset;
					adjacent.emplace(u, newset);
				}
			}
			if (pm.second.size() >= 2) {
				for (int ii = 0; ii < pm.second.size(); ii++) {
					for (int jj = 0; jj < pm.second.size(); jj++) {
						if (ii != jj) adjacent[pm.second[ii]].insert(pm.second[jj]);
					}
				}
			}
		}
		std::uint64_t prod = 1;
		for (const auto& pm : adjacent) {
			if (pm.second.size() == 2) {
				prod *= pm.first;
			}
			std::cout << pm.first << ": {";
			for (const auto a : pm.second) {
				std::cout << a << " ";
			}
			std::cout << "}" << std::endl;
		}

		std::cout << "Product of corner pieces: " << prod << std::endl;

		std::vector<std::vector<std::uint16_t>> pieceArray;

		std::cout << "Arranging pieces..." << std::endl;
		arrangePieces(adjacent, pieceLookup, pieceArray, edgeMap);

		std::array<std::array<std::uint16_t, 12>, 12> piecesByPosition;
		for (const auto& p : pieceLookup) {
			piecesByPosition[p.second.positionY][p.second.positionX] = p.second.number;
		}

		std::array<std::bitset<120>, 120> data;

		for (int row = 0; row < 120; row++) {
			for (int col = 0; col < 120; col++) {
				auto pieceX = col / 10;
				auto pieceY = row / 10;
				auto offsetX = col % 10;
				auto offsetY = row % 10;
				auto pNum = piecesByPosition[pieceY][pieceX];
				auto p = pieceLookup.find(pNum);
				data[row][col] = p->second.getValue(offsetX, offsetY);
			}
		}

		for (int jj = 0; jj < piecesByPosition.size(); jj++) {
			for (int ii = 0; ii < piecesByPosition[jj].size(); ii++) {
				std::cout << piecesByPosition[ii][jj] << "," << (int) pieceLookup.find(piecesByPosition[ii][jj])->second.orientation << "|";
			}
			std::cout << std::endl;
		}

	 	std::cout << "Final assembly before final orientation search: " << std::endl;

		std::queue<std::uint16_t> worklist;

		for (int ii = 0; ii < piecesByPosition.size(); ii++) {
			for (int jj = 0; jj < piecesByPosition[ii].size(); jj++) {
				worklist.push(piecesByPosition[ii][jj]);
			}
		}

		while (worklist.size() > 0) {
			std::uint16_t nextPiece = worklist.front();
			PuzzlePiece& pp = pieceLookup.find(nextPiece)->second;
			worklist.pop();
			if (!checkPiece(nextPiece, pieceLookup, piecesByPosition, edgeMap)) {
				int mostMatching = 0;
				int bestOrientation = 0;
				for (int orientation = 0; orientation < 8; orientation++) {
					pp.orientation = orientation;
					if (countMatchingPieces(pp, piecesByPosition, edgeMap) > mostMatching) {
						bestOrientation = orientation;
					}
				}
				pp.orientation = bestOrientation;
				worklist.push(nextPiece);
			}
		}
		for (int row = 0; row < 120; row++) {
			for (int col = 0; col < 120; col++) {
				auto pieceX = col / 10;
				auto pieceY = row / 10;
				auto offsetX = col % 10;
				auto offsetY = row % 10;
				auto pNum = piecesByPosition[pieceY][pieceX];
				auto p = pieceLookup.find(pNum);
				data[row][col] = p->second.getValue(offsetX, offsetY);
			}
		}

		for (int jj = 0; jj < piecesByPosition.size(); jj++) {
			for (int ii = 0; ii < piecesByPosition[jj].size(); ii++) {
				std::cout << piecesByPosition[ii][jj] << ","
					<< (int) pieceLookup.find(piecesByPosition[ii][jj])->second.orientation << ","
					<< countMatchingPieces(pieceLookup.find(piecesByPosition[ii][jj])->second, piecesByPosition, edgeMap) << "|";
			}
			std::cout << std::endl;
		}

		std::array<std::bitset<96>, 96> dataFinal;
		for (int row = 0; row < 96; row++) {
			for (int col = 0; col < 96; col++) {
				auto pieceX = col / 8;
				auto pieceY = row / 8;
				auto offsetX = col % 8;
				auto offsetY = row % 8;
				auto pNum = piecesByPosition[pieceY][pieceX];
				auto p = pieceLookup.find(pNum);
				dataFinal[row][col] = p->second.getValue(offsetX, offsetY, true);
			}
		}

		std::ifstream seaMonsterFile = AOCUtils::GetFile("inputs/SeaMonster.txt");
		std::array<std::bitset<20>, 3> seaMonster;
		std::string line;

		for (int i = 0; i < 3; i++) {
			std::getline(seaMonsterFile, line);
			std::cout << "read line: " << line << std::endl;
			for (int j = 0; j < 20; j++) {
				seaMonster[i][j] = line[j] == '#';
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 20; j++) {
				std::cout << (seaMonster[i][j] ? '#' : '.');
			}
			std::cout << std::endl;
		}

		std::cout << "Sea Roughness: " << seaRoughness(seaMonster, dataFinal) << std::endl;
		std::cout << "Rotating..." << std::endl;
		rotate90(dataFinal);
		std::cout << "Sea Roughness: " << seaRoughness(seaMonster, dataFinal) << std::endl;
		std::cout << "Rotating..." << std::endl;
		rotate90(dataFinal);
		std::cout << "Sea Roughness: " << seaRoughness(seaMonster, dataFinal) << std::endl;
		std::cout << "Rotating..." << std::endl;
		rotate90(dataFinal);
		std::cout << "Sea Roughness: " << seaRoughness(seaMonster, dataFinal) << std::endl;
		std::cout << "Flipping..." << std::endl;
		flip(dataFinal);
		std::cout << "Sea Roughness: " << seaRoughness(seaMonster, dataFinal) << std::endl;
		std::cout << "Rotating..." << std::endl;
		rotate90(dataFinal);
		std::cout << "Sea Roughness: " << seaRoughness(seaMonster, dataFinal) << std::endl;
		std::cout << "Rotating..." << std::endl;
		rotate90(dataFinal);
		std::cout << "Sea Roughness: " << seaRoughness(seaMonster, dataFinal) << std::endl;
		std::cout << "Rotating..." << std::endl;
		rotate90(dataFinal);
		std::cout << "Sea Roughness: " << seaRoughness(seaMonster, dataFinal) << std::endl;

		return EXIT_SUCCESS;
	}
}