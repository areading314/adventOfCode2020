#pragma once

#include <string>
#include <vector>

namespace AOC2020 {
	enum class GameboyInstruction {
		ACC,
		JMP,
		NOP
	};

	std::string InstructionToString(GameboyInstruction);

	struct Instruction {
		GameboyInstruction inst;
		int count;
	};

	Instruction ParseInstruction(std::string inst);

	class Gameboy {
	private: 
		int accumulator;
		std::vector<Instruction> instructions;
		std::vector<Instruction>::size_type _execute(const Instruction& i, int& accumulator, std::vector<Instruction>::size_type currentInstruction);
	public:
		int getAccumulator() const {
			return accumulator;
		}
		Gameboy(const std::vector<std::string>& instructions);
		int findAccumulatorAtFirstRepeat();
		int uncorruptAndRunProgram();
	};
}
