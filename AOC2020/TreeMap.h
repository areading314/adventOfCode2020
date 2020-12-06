#pragma once

#include <string>
#include <vector>

namespace AOC2020 {

	enum class MapTile {
		EMPTY,
		TREE
	};

	class TreeMap {
	private:
		std::vector<std::vector<MapTile>> _tiles;
		void _parseLine(const std::string& line, std::vector<MapTile>& target);
	public:
		TreeMap(const std::string& filename);
		unsigned int countTreesAtAngle(unsigned int down, unsigned int right);
		MapTile GetMapTile(unsigned int y, unsigned int x);
		unsigned int GetMaxY();
	};
}
