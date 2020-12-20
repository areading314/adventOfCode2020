#include <iostream>
#include <vector>

#include "Computer.h"
#include "FileUtil.h"
#include "Problems.h"


namespace AOC2020 {
	int Problem14() {
		std::ifstream infile = AOCUtils::GetFile("inputs/Problem14Input.txt");
		std::string line;
		std::vector<Instruction*> instructions;
		int counter = 0;
		while (std::getline(infile, line)) {
			Computer::readInstruction(line);
			instructions.push_back(Computer::readInstruction(line));
			counter++;
		}
		Computer c;
		std::cout << "Got " << instructions.size() << " instructions." << std::endl;
		for (auto i : instructions) {
			c.handleInstruction(*i);
			// c.printMemory();
		}
		std::cout << "Sum of integers in memory is: " << c.memorySum() << std::endl;
		Computer c2;
		for (auto i : instructions) {
			c2.handleInstructionV2(*i);
			// c2.printMemory();
		}
		std::cout << "V2: Sum of integers in memory is: " << c2.memorySum() << std::endl;
		for (auto i : instructions) delete i;
		return EXIT_SUCCESS;
	}
}