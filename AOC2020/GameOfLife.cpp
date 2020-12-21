#include "GameOfLife.h"

namespace AOC2020 {

	GameOfLife::GameOfLife(std::size_t xDim_, std::size_t yDim_, std::size_t zDim_, std::size_t wDim_) : wDim(wDim_), xDim(xDim_), yDim(yDim_), zDim(zDim_) {
		_initializeStates();
	}

	void GameOfLife::_initializeStates() {
		for (std::size_t h = 0; h < wDim; h++) {
			BoolVector3D currentSpace;
			BoolVector3D nextSpace;
			for (std::size_t i = 0; i < xDim; i++) {
				BoolVector2D currentPlane;
				BoolVector2D nextPlane;
				for (std::size_t j = 0; j < yDim; j++) {
					BoolVector1D currentRow;
					BoolVector1D nextRow;
					for (std::size_t k = 0; k < zDim; k++) {
						currentRow.push_back(false);
						nextRow.push_back(false);
					}
					currentPlane.push_back(currentRow);
					nextPlane.push_back(nextRow);
				}
				currentSpace.push_back(currentPlane);
				nextSpace.push_back(nextPlane);
			}
			currentState.push_back(currentSpace);
			nextState.push_back(nextSpace);
		}
	}

	std::uint32_t GameOfLife::activeCount() const {
		std::uint32_t retval = 0;
		for (const auto& wspace : currentState) {
			for (const auto& xplane : wspace) {
				for (const auto& yrow : xplane) {
					for (const auto& zcell : yrow) {
						if (zcell) retval++;
					}
				}
			}
		}
		return retval;
	}

	void GameOfLife::setState(const BoolVector3D& inputs, std::size_t xOffset, std::size_t yOffset, std::size_t zOffset, std::size_t wOffset) {
		for (std::size_t x = xOffset, xInput = 0; x < xDim && xInput < inputs.size(); x++, xInput++) {
			for (std::size_t y = yOffset, yInput = 0; y < yDim && yInput < inputs[xInput].size(); y++, yInput++) {
				for (std::size_t z = zOffset, zInput = 0; z < zDim && zInput < inputs[xInput][yInput].size(); z++, zInput++) {
					currentState[wOffset][x][y][z] = inputs[xInput][yInput][zInput];
				}
			}
		}
	}

	void GameOfLife::step() {
		for (std::size_t w = 0; w < wDim; w++) {
			for (std::size_t x = 0; x < xDim; x++) {
				for (std::size_t y = 0; y < yDim; y++) {
					for (std::size_t z = 0; z < zDim; z++) {
						BOOL currentValue = currentState[w][x][y][z];
						std::uint8_t currentCount = countNeighbors(x, y, z, w);
						BOOL nextValue;
						if (currentValue) {
							if (currentCount == 2 || currentCount == 3)
								nextValue = true;
							else
								nextValue = false;
						}
						else {
							if (currentCount == 3) nextValue = true;
							else nextValue = false;
						}
						nextState[w][x][y][z] = nextValue;
					}
				}
			}
		}
		for (std::size_t w = 0; w < wDim; w++) {
			for (std::size_t x = 0; x < xDim; x++) {
				for (std::size_t y = 0; y < yDim; y++) {
					for (std::size_t z = 0; z < zDim; z++) {
						currentState[w][x][y][z] = nextState[w][x][y][z];
					}
				}
			}
		}
	}

	std::uint8_t GameOfLife::countNeighbors(std::size_t xPos, std::size_t yPos, std::size_t zPos, std::size_t wPos) const {
		std::size_t xLow = xPos == 0 ? 0 : xPos - 1;
		std::size_t xHigh = xPos == xDim - 1 ? xDim : xPos + 2;
		std::size_t yLow = yPos == 0 ? 0 : yPos - 1;
		std::size_t yHigh = yPos == yDim - 1 ? yDim : yPos + 2;
		std::size_t zLow = zPos == 0 ? 0 : zPos - 1;
		std::size_t zHigh = zPos == zDim - 1 ? zDim : zPos + 2;
		std::size_t wLow = wPos == 0 ? 0 : wPos - 1;
		std::size_t wHigh = wPos == wDim - 1 ? wDim : wPos + 2;
		std::uint8_t count = 0;
		for (std::size_t w = wLow; w < wHigh; w++) {
			for (std::size_t x = xLow; x < xHigh; x++) {
				for (std::size_t y = yLow; y < yHigh; y++) {
					for (std::size_t z = zLow; z < zHigh; z++) {
						if (currentState[w][x][y][z] && (x != xPos || y != yPos || z != zPos || w != wPos)) count++;
					}
				}
			}
		}
		return count;
	}

	std::ostream& operator<<(std::ostream& out, const GameOfLife& gol) {
		for (std::size_t w = 0; w < gol.wDim; w++) {
			for (std::size_t x = 0; x < gol.xDim; x++) {
				std::cout << "Space " << w << " Level " << x << ":" << std::endl;
				for (std::size_t y = 0; y < gol.yDim; y++) {
					for (std::size_t z = 0; z < gol.zDim; z++) {
						std::cout << (gol.currentState[w][x][y][z] ? "# " : ". ");
					}
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
		return out;
	}
}