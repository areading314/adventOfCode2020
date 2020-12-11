#pragma once

#include <string>
#include <vector>

namespace AOC2020 {

	enum class WaitingAreaTile {
		FLOOR,
		SEAT,
		OCCUPIED
	};

	class WaitingArea {
	private:
		std::vector<std::vector<WaitingAreaTile>> _seats;
	public:
		WaitingArea(const std::string& filename);
		bool update(bool lineOfSight);
		std::size_t getHeight() const;
		std::size_t getWidth() const;
		std::uint8_t countAdjacency(std::size_t row, std::size_t col) const;
		std::uint8_t countAdjacencyLOS(std::size_t row, std::size_t col) const;
		void print(std::uint32_t iteration) const;
		std::uint32_t countOccupied() const;
	};
}
