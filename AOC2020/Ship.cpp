#include <iostream>

#include "FileUtil.h"
#include "Ship.h"

namespace AOC2020 {
	Ship::Ship() : xLocation(0), yLocation(0), heading(0) {
	}

	Instruction parseInstruction(const std::string& inst) {
		char d = inst[0];
		int a = std::stoi(inst.substr(1, inst.size() - 1));
		InstructionDirection id;
		switch (d) {
		case 'N': id = InstructionDirection::NORTH; break;
		case 'E': id = InstructionDirection::EAST; break;
		case 'S': id = InstructionDirection::SOUTH; break;
		case 'W': id = InstructionDirection::WEST; break;
		case 'F': id = InstructionDirection::FORWARD; break;
		case 'R': id = InstructionDirection::RIGHT; break;
		case 'L': id = InstructionDirection::LEFT; break;
		default: std::cout << "ERROR: Invalid direction. Got " << d << std::endl;
		}
		return Instruction{ id, a };
	}

	int Ship::getXLocation() const {
		return xLocation;
	}

	int Ship::getYLocation() const {
		return yLocation;
	}

	int Ship::getHeading() const {
		return heading;
	}

	void Ship::applyInstruction(Instruction i) {
		if (i.dir == InstructionDirection::NORTH) {
			yLocation += i.amount;
		}
		else if (i.dir == InstructionDirection::EAST) {
			xLocation += i.amount;
		}
		else if (i.dir == InstructionDirection::WEST) {
			xLocation -= i.amount;
		}
		else if (i.dir == InstructionDirection::SOUTH) {
			yLocation -= i.amount;
		}
		else if (i.dir == InstructionDirection::RIGHT) {
			heading = (heading + i.amount) % 360;
		}
		else if (i.dir == InstructionDirection::LEFT) {
			heading = (heading + 360 - i.amount) % 360;
		}
		else if (i.dir == InstructionDirection::FORWARD) {
			if (heading == 0) xLocation += i.amount;
			else if (heading == 90) yLocation -= i.amount;
			else if (heading == 180) xLocation -= i.amount;
			else if (heading == 270) yLocation += i.amount;
		}
		else std::cout << "Unknown direction found." << std::endl;
	}

	WaypointShip::WaypointShip() : xLocation(0), yLocation(0), wpXLocation(10), wpYLocation(1) {}

	void WaypointShip::applyInstruction(Instruction i) {
		if (i.dir == InstructionDirection::NORTH) {
			wpYLocation += i.amount;
		}
		else if (i.dir == InstructionDirection::EAST) {
			wpXLocation += i.amount;
		}
		else if (i.dir == InstructionDirection::WEST) {
			wpXLocation -= i.amount;
		}
		else if (i.dir == InstructionDirection::SOUTH) {
			wpYLocation -= i.amount;
		}
		else if (i.dir == InstructionDirection::RIGHT) {
			int tmpx = wpXLocation;
			int tmpy = wpYLocation;
			if (i.amount % 360 == 90) {
				wpXLocation = tmpy;
				wpYLocation = -tmpx;
			}
			else if (i.amount % 360 == 180) {
				wpXLocation = -tmpx;
				wpYLocation = -tmpy;
			}
			else if (i.amount % 360 == 270) {
				wpXLocation = -tmpy;
				wpYLocation = tmpx;
			}
			else {
				std::cout << "invalid: " << "R" << i.amount << std::endl;
			}
		}
		else if (i.dir == InstructionDirection::LEFT) {
			int tmpx = wpXLocation;
			int tmpy = wpYLocation;
			if (i.amount % 360 == 90) {
				wpXLocation = -tmpy;
				wpYLocation = tmpx;
			}
			else if (i.amount % 360 == 180) {
				wpXLocation = -tmpx;
				wpYLocation = -tmpy;
			}
			else if (i.amount % 360 == 270) {
				wpXLocation = tmpy;
				wpYLocation = -tmpx;
			}
			else {
				std::cout << "invalid: " << "L" << i.amount << std::endl;
			}
		}
		else if (i.dir == InstructionDirection::FORWARD) {
			xLocation += wpXLocation * i.amount;
			yLocation += wpYLocation * i.amount;
		}
		else std::cout << "Unknown direction found." << std::endl;
	}
}