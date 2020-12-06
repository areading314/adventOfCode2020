#include <fstream>

#include "FileUtil.h"
#include "TreeMap.h"

namespace AOC2020 {
	TreeMap::TreeMap(const std::string& filename) {
		std::ifstream inputFile = AOCUtils::GetFile(filename);
		std::string inputString;
		while (std::getline(inputFile, inputString)) {
			std::vector<MapTile> nextLine;
			_parseLine(inputString, nextLine);
			if (nextLine.size() > 0) {
				_tiles.push_back(nextLine);
			}
		}
	}

	void TreeMap::_parseLine(const std::string& line, std::vector<MapTile>& target) {
		for (char c : line) {
			if (c == '#') {
				target.push_back(MapTile::TREE);
			}
			else if (c == '.') {
				target.push_back(MapTile::EMPTY);
			}
		}
	}

	unsigned int TreeMap::countTreesAtAngle(unsigned int down, unsigned int right) {
		unsigned int numTrees = 0;
		for (unsigned int i = 0, j = 0; i < GetMaxY(); i += down, j += right) {
			MapTile m = GetMapTile(i, j);
			if (m == MapTile::TREE) {
				numTrees++;
			}
		}
		return numTrees;
	}

	unsigned int TreeMap::GetMaxY() {
		return (unsigned int) _tiles.size();
	}

	MapTile TreeMap::GetMapTile(unsigned int y, unsigned int x) {
		unsigned int rows = GetMaxY();
		if (y > rows) {
			throw std::invalid_argument("y too large, max is "
				+ std::to_string(rows)
				+ " got "
				+ std::to_string(y));
		}
		std::vector<MapTile>::size_type cols = _tiles[0].size();
		return _tiles[y][x % cols];
	}
}
