#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>


namespace AOC2020 {

	typedef std::uint64_t CUINT;

	enum class MaskLetter {
		KEEP, ZERO, ONE
	};
	enum class InstructionType { MEMSET, SETMASK };
	MaskLetter charToMaskType(char c);

	struct Instruction {
		InstructionType instructionType;
		CUINT location;
		CUINT value;
	};

	std::ostream& operator<<(std::ostream& out, const InstructionType value);
	std::ostream& operator<<(std::ostream& out, const Instruction value);

	class Computer {
	private:
		std::unordered_map<CUINT, CUINT> memory;
		CUINT currentMaskValues;
		CUINT currentMaskShape;
	public:
		Computer();
		static Instruction* readInstruction(const std::string& inputString);
		bool handleInstruction(Instruction i);
		bool handleInstructionV2(Instruction i);
		CUINT memorySum() const;
		void printMemory() const;
	};
}
