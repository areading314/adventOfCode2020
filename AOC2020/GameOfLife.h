#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

namespace AOC2020 {
	typedef bool BOOL;
	typedef std::vector<BOOL> BoolVector1D;
	typedef std::vector<BoolVector1D> BoolVector2D;
	typedef std::vector<BoolVector2D> BoolVector3D;
	typedef std::vector<BoolVector3D> BoolVector4D;

	class GameOfLife {
	private:
		BoolVector4D currentState;
		BoolVector4D nextState;

		void _initializeStates();
		std::size_t wDim;
		std::size_t xDim;
		std::size_t yDim;
		std::size_t zDim;
	public:
		GameOfLife(std::size_t xDim, std::size_t yDim, std::size_t zDim, std::size_t wDim = 1);
		std::uint8_t countNeighbors(std::size_t xPos, std::size_t yPos, std::size_t zPos, std::size_t wPos = 0) const;
		void step();
		void setState(const BoolVector3D& startingState, std::size_t xOffset, std::size_t yOffset, std::size_t zOffset, std::size_t wOffset = 0);
		std::uint32_t activeCount() const;
		std::size_t getWDim() const { return wDim; };
		std::size_t getXDim() const { return xDim; };
		std::size_t getYDim() const { return yDim; };
		std::size_t getZDim() const { return zDim; };


		friend std::ostream& operator<<(std::ostream& out, const GameOfLife& v);
	};
}
