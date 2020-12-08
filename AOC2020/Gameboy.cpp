#include <iostream>
#include <unordered_set>
#include <vector>

#include "Gameboy.h"
#include "StringUtil.h"

namespace AOC2020 {
	Instruction ParseInstruction(std::string inst) {
		std::vector<std::string> bits;
		AOCUtils::splitString(inst, bits, ' ');
		Instruction i;
		i.count = std::stoi(bits[1]);
		std::string bit = bits[0];
		if (bit == "nop") {
			i.inst = GameboyInstruction::NOP;
		}
		else if (bit == "jmp") {
			i.inst = GameboyInstruction::JMP;
		}
		else if (bit == "acc") {
			i.inst = GameboyInstruction::ACC;
		}
		else {
			std::cout << "Invalid instruction: " << bit << std::endl;
		}
		return i;
	}

	Gameboy::Gameboy(const std::vector<std::string>& _instructions) {
		for (auto i = _instructions.begin(); i != _instructions.end(); ++i) {
			instructions.push_back(ParseInstruction(*i));
		}
	}

	int Gameboy::findAccumulatorAtFirstRepeat() {
		std::unordered_set<std::vector<Instruction>::size_type> seenInstructions;
		std::vector<Instruction>::size_type currentInstruction = 0;
		int accumulator = 0;
		while (seenInstructions.find(currentInstruction) == seenInstructions.end()) {
			seenInstructions.insert(currentInstruction);
			currentInstruction = _execute(instructions[currentInstruction], accumulator, currentInstruction);
		}
		return accumulator;
	}

	Instruction overrideInst(Instruction i) {
		Instruction i2 = i;
		if (i.inst == GameboyInstruction::JMP) {
			i2.inst = GameboyInstruction::NOP;
		}
		else if (i.inst == GameboyInstruction::NOP) {
			i2.inst = GameboyInstruction::JMP;
		}
		return i2;
	}

	int Gameboy::uncorruptAndRunProgram() {
		std::vector<Instruction>::size_type currentInstruction = 0;
		int accumulator = 0;
		std::unordered_set<std::vector<Instruction>::size_type> seenInstructions;
		for (std::vector<Instruction>::size_type overrideInstruction = 0; overrideInstruction < instructions.size(); overrideInstruction++) {
			while (seenInstructions.find(currentInstruction) == seenInstructions.end()) {
				seenInstructions.insert(currentInstruction);
				auto nextIntro = instructions[currentInstruction];
				if (overrideInstruction == currentInstruction) nextIntro = overrideInst(nextIntro);
				currentInstruction = _execute(nextIntro, accumulator, currentInstruction);
				if (currentInstruction == instructions.size()) {
					std::cout << "Terminated, after changing " << overrideInstruction << std::endl;
					return accumulator;
				}
			}
			seenInstructions.clear();
			currentInstruction = 0;
			accumulator = 0;
		}
		return accumulator;
	}

	std::vector<Instruction>::size_type Gameboy::_execute(const Instruction& i, int& accumulator, std::vector<Instruction>::size_type currentIndex) {
		if (i.inst == GameboyInstruction::JMP) {
			return currentIndex + i.count;
		}
		else if (i.inst == GameboyInstruction::NOP) {
			return currentIndex + 1;
		}
		else if (i.inst == GameboyInstruction::ACC) {
			accumulator += i.count;
			return currentIndex + 1;
		}
		else {
			std::cout << "Invalid instruction: " << InstructionToString(i.inst) << " " << i.count << std::endl;
		}
		return 0;
	}

	std::string InstructionToString(GameboyInstruction i) {
		if (i == GameboyInstruction::JMP) return "jmp";
		else if (i == GameboyInstruction::ACC) return "acc";
		else if (i == GameboyInstruction::NOP) return "nop";
		else {
			std::cout << "invalid instruction" << std::endl;
			return "??";
		}
	}
}