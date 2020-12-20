#include <bitset>
#include <iostream>

#include "Computer.h"
#include "StringUtil.h"

namespace AOC2020 {

	MaskLetter charToMaskType(char c) {
		switch (c) {
		case 'X': return MaskLetter::KEEP;
		case '1': return MaskLetter::ONE;
		case '0': return MaskLetter::ZERO;
		default:
			std::cout << "Error: Invalid mask letter: " << c << std::endl;
		}
		return MaskLetter(0);
	}

	Instruction* Computer::readInstruction(const std::string& inputString) {
		std::vector<std::string> tokens;
		Instruction* inst = new Instruction();
		AOCUtils::splitString(inputString, tokens, ' ');

		if (tokens[0].substr(0, 3) == "mem") {
			int ind = 4;
			while (tokens[0][ind] >= '0' && tokens[0][ind] <= '9') {
				ind++;
			}
			CUINT memoryAddress = std::stol(tokens[0].substr(4, ind - 4));
			CUINT value = std::stol(tokens[2]);
			inst->instructionType = InstructionType::MEMSET;
			inst->location = memoryAddress;
			inst->value = value;
		}
		else if (tokens[0].substr(0, 4) == "mask") {
			std::vector<MaskLetter> mls;
			for (auto c : tokens[2]) {
				mls.push_back(charToMaskType(c));
			}
			CUINT values = 0L;
			CUINT shape = 0L;
			CUINT cursor = 1L << 35;
			for (auto ml : mls) {
				if (ml == MaskLetter::KEEP) {
					shape |= cursor;
				}
				else if (ml == MaskLetter::ONE) {
					values |= cursor;
				}
				else if (ml == MaskLetter::ZERO) {
					/* noop */
				}
				cursor >>= 1;
			}
			inst->instructionType = InstructionType::SETMASK;
			inst->location = shape;
			inst->value = values;
		}
		else {
			std::cout << "Invalid tokens: ";
			for (auto t : tokens) std::cout << t;
			std::cout << std::endl;
		}
		return inst;
	}

	std::ostream& operator<<(std::ostream& out, const Instruction value) {
		std::bitset<36> locationbs(value.location);
		std::bitset<36> valuebs(value.value);
		out << "[Instruction:" << value.instructionType
			<< " " << locationbs << " " << valuebs
			<< "]";
		return out;
	}

	std::ostream& operator<<(std::ostream& out, const InstructionType value) {
		if (value == InstructionType::MEMSET) {
			out << "MEMSET";
		}
		else if (value == InstructionType::SETMASK) {
			out << "SETMASK";
		}
		else {
			out << "?????";
		}
		return out;
	}

	bool Computer::handleInstruction(Instruction i) {
		if (i.instructionType == InstructionType::SETMASK) {
			currentMaskShape = i.location;
			currentMaskValues = i.value;
		}
		else if (i.instructionType == InstructionType::MEMSET) {
			CUINT newValue = ((~currentMaskShape) & currentMaskValues) | (currentMaskShape & i.value);
			memory[i.location] = newValue;
		}
		else {
			std::cout << "Invalid instruction: " << i << std::endl;
			return false;
		}
		return true;
	}

	bool Computer::handleInstructionV2(Instruction i) {
		if (i.instructionType == InstructionType::SETMASK) {
			currentMaskShape = i.location;
			currentMaskValues = i.value;
		}
		else if (i.instructionType == InstructionType::MEMSET) {
			std::bitset<36> bs(currentMaskShape);
			std::bitset<36> mv(currentMaskValues);
			int floatingCount = 0;
			for (int i = 0; i < 36; i++) if (bs.test(i)) floatingCount++;
			CUINT maxFloatings = 1L << floatingCount;
			for (CUINT ii = 0; ii < maxFloatings; ii++) {
				std::bitset<36> address(i.location);
				std::bitset<36> iiBs(ii);
				for (int i = 0, j = 0; i < 36; i++) {
					if (bs.test(i)) {
						address.set(i, iiBs.test(j++));
					}
					else if (mv.test(i)) {
						address.set(i, mv.test(i));
					}
				}
				memory[address.to_ullong()] = i.value;
			}
		}
		else {
			std::cout << "Invalid instruction: " << i << std::endl;
			return false;
		}
		return true;
	}

	void Computer::printMemory() const {
		std::cout << "Current memory: " << std::endl;
		for (auto i : memory) {
			std::cout << i.first << "\t\t" << std::bitset<36>(i.second) << std::endl;
		}
		std::cout << "mask shape:\t" << std::bitset<36>(currentMaskShape) << std::endl;
		std::cout << "mask value:\t" << std::bitset<36>(currentMaskValues) << std::endl;
	}

	CUINT Computer::memorySum() const {
		CUINT sum = 0;
		for (auto i : memory) {
			sum += i.second;
		}
		return sum;
	}

	Computer::Computer() : currentMaskValues(0), currentMaskShape(0) {}
}