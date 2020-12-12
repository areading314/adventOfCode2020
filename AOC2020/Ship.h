#pragma once


namespace AOC2020 {
	enum class InstructionDirection {
		NORTH,
		EAST,
		SOUTH,
		WEST,
		LEFT,
		FORWARD,
		RIGHT
	};

	struct Instruction {
		InstructionDirection dir;
		int amount;
	};

	Instruction parseInstruction(const std::string& inst);

	class Ship {
	private:
		int xLocation;
		int yLocation;
		unsigned int heading;
	public:
		Ship();
		void applyInstruction(Instruction i);
		int getXLocation() const;
		int getYLocation() const;
		int getHeading() const;
	};

	class WaypointShip {
	private:
		int xLocation;
		int yLocation;
		int wpXLocation;
		int wpYLocation;
	public:
		WaypointShip();
		void applyInstruction(Instruction i);
		int getXLocation() const { return xLocation; };
		int getYLocation() const { return yLocation; };
		int getWPXLocation() const { return wpXLocation; };
		int getWPYLocation() const { return wpYLocation; };
	};
}
