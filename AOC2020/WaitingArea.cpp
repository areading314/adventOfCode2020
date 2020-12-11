#include <iostream>

#include "FileUtil.h"
#include "WaitingArea.h"

namespace AOC2020 {
	WaitingArea::WaitingArea(const std::string& filename) {
		std::ifstream input = AOCUtils::GetFile(filename);
		std::string line;
		while (std::getline(input, line)) {
			std::vector<WaitingAreaTile> currentVector;
			for (char i : line) {
				if (i == '#') {
					currentVector.push_back(WaitingAreaTile::OCCUPIED);
				}
				else if (i == 'L') {
					currentVector.push_back(WaitingAreaTile::SEAT);
				}
				else if (i == '.') {
					currentVector.push_back(WaitingAreaTile::FLOOR);
				}
				else {
					std::cout << "ERROR: Invalid tile: " << i << std::endl;
				}
			}
			_seats.push_back(currentVector);
		}
	}

	bool WaitingArea::update(bool lineOfSight) {
		bool changed = false;
		std::vector<std::vector<std::uint8_t>> adjacency;
		for (std::size_t i = 0; i < getHeight(); i++) {
			std::vector<std::uint8_t> newValues;
			for (std::size_t j = 0; j < getWidth(); j++) {
				if (lineOfSight)
					newValues.push_back(countAdjacencyLOS(i, j));
				else
					newValues.push_back(countAdjacency(i, j));
			}
			adjacency.push_back(newValues);
		}

		/*
		for (auto r : adjacency) {
			for (char c : r) std::cout << std::to_string(c);
			std::cout << std::endl;
		}
		std::cout << std::endl;
		*/

		for (std::size_t i = 0; i < getHeight(); i++) {
			for (std::size_t j = 0; j < getWidth(); j++) {
				if (adjacency[i][j] >= (lineOfSight ? 5 : 4) && _seats[i][j] == WaitingAreaTile::OCCUPIED) {
					_seats[i][j] = WaitingAreaTile::SEAT, changed = true;
				}
				else if (adjacency[i][j] == 0 && _seats[i][j] == WaitingAreaTile::SEAT) {
					_seats[i][j] = WaitingAreaTile::OCCUPIED, changed = true;
				}
			}
		}
		return changed;
	}

    std::size_t WaitingArea::getHeight() const {
		return _seats.size();
	}

	std::size_t WaitingArea::getWidth() const {
		return _seats[0].size();
	}

	std::uint8_t WaitingArea::countAdjacency(std::size_t row, std::size_t col) const {
		std::uint8_t count = 0;
		std::size_t h = getHeight(), w = getWidth();
		if (row > 0 && col > 0) {
			if (_seats[row - 1][col - 1] == WaitingAreaTile::OCCUPIED) count++;
		}
		if (col > 0) {
			if (_seats[row][col - 1] == WaitingAreaTile::OCCUPIED) count++;
		}
		if (row > 0) {
			if (_seats[row - 1][col] == WaitingAreaTile::OCCUPIED) count++;
		}
		if (col > 0 && row + 1 < h) {
			if (_seats[row + 1][col - 1] == WaitingAreaTile::OCCUPIED) count++;
		}
		if (row > 0 && col + 1 < w) {
			if (_seats[row - 1][col + 1] == WaitingAreaTile::OCCUPIED) count++;
		}
		if (row + 1 < h) {
			if (_seats[row + 1][col] == WaitingAreaTile::OCCUPIED) count++;
		}
		if (col + 1 < w) {
			if (_seats[row][col + 1] == WaitingAreaTile::OCCUPIED) count++;
		}
		if (row + 1 < h && col + 1 < w) {
			if (_seats[row + 1][col + 1] == WaitingAreaTile::OCCUPIED) count++;
		}
		return count;
	}



	void WaitingArea::print(std::uint32_t iteration) const {
		std::cout << "## Iteration " << iteration << " ##" << std::endl;
		for (auto row : _seats) {
			for (WaitingAreaTile c : row) {
				if (c == WaitingAreaTile::FLOOR) std::cout << ".";
				else if (c == WaitingAreaTile::SEAT) std::cout << "L";
				else if (c == WaitingAreaTile::OCCUPIED) std::cout << "#";
				else std::cout << "?" << std::endl;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	std::uint8_t WaitingArea::countAdjacencyLOS(std::size_t row, std::size_t col) const {
		std::uint8_t count = 0;
		std::size_t h = getHeight(), w = getWidth();
		std::size_t r, c;
		if (row > 0 && col > 0) {
			r = row - 1, c = col - 1;
			while (r < h && c < w) {
				if (_seats[r][c] == WaitingAreaTile::OCCUPIED) {
					count++;
					break;
				}
				if (_seats[r][c] == WaitingAreaTile::SEAT) break;
				r--, c--;
			}
		}
		if (col > 0) {
			r = row, c = col - 1;
			while (c < w) {
				if (_seats[r][c] == WaitingAreaTile::OCCUPIED) {
					count++;
					break;
				}
				if (_seats[r][c] == WaitingAreaTile::SEAT) break;
				c--;
			}
		}
		if (row > 0) {
			r = row - 1, c = col;
			while (r < h) {
				if (_seats[r][c] == WaitingAreaTile::OCCUPIED) {
					count++;
					break;
				}
				if (_seats[r][c] == WaitingAreaTile::SEAT) break;
				r--;
			}
		}
		if (col > 0 && row + 1 < h) {
			r = row + 1, c = col - 1;
			while (c < w && r < h) {
				if (_seats[r][c] == WaitingAreaTile::OCCUPIED) {
					count++;
					break;
				}
				if (_seats[r][c] == WaitingAreaTile::SEAT) break;
				r++, c--;
			}
		}
		if (row > 0 && col + 1 < w) {
			r = row - 1, c = col + 1;
			while (c < w && r < h) {
				if (_seats[r][c] == WaitingAreaTile::OCCUPIED) {
					count++;
					break;
				}
				if (_seats[r][c] == WaitingAreaTile::SEAT) break;
				r--, c++;
			}
		}
		if (row + 1 < h) {
			r = row + 1, c = col;
			while (r < h) {
				if (_seats[r][c] == WaitingAreaTile::OCCUPIED) {
					count++;
					break;
				}
				if (_seats[r][c] == WaitingAreaTile::SEAT) break;
				r++;
			}
		}
		if (col + 1 < w) {
			r = row, c = col + 1;
			while (c < w) {
				if (_seats[r][c] == WaitingAreaTile::OCCUPIED) {
					count++;
					break;
				}
				if (_seats[r][c] == WaitingAreaTile::SEAT) break;
				c++;
			}
		}
		if (row + 1 < h && col + 1 < w) {
			r = row + 1, c = col + 1;
			while (c < w && r < h) {
				if (_seats[r][c] == WaitingAreaTile::OCCUPIED) {
					count++;
					break;
				}
				if (_seats[r][c] == WaitingAreaTile::SEAT) break;
				r++, c++;
			}
		}
		return count;
	}

	std::uint32_t WaitingArea::countOccupied() const {
		std::uint32_t count = 0;
		for (auto row : _seats)
			for (WaitingAreaTile wat : row)
				if (wat == WaitingAreaTile::OCCUPIED) count++;
		return count;
	}
}