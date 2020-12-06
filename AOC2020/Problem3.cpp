#include <iostream>

#include "Problems.h"
#include "TreeMap.h"


int AOC2020::Problem3() {
	std::string filename("inputs/Problem3Input.txt");
	AOC2020::TreeMap tm = AOC2020::TreeMap(filename);
	unsigned int numTrees1 = tm.countTreesAtAngle(1, 1);
	unsigned int numTrees2 = tm.countTreesAtAngle(1, 3);
	unsigned int numTrees3 = tm.countTreesAtAngle(1, 5);
	unsigned int numTrees4 = tm.countTreesAtAngle(1, 7);
	unsigned int numTrees5 = tm.countTreesAtAngle(2, 1);
	std::cout << "product of treecounts is " << numTrees1 * numTrees2 * numTrees3 * numTrees4 * numTrees5 << std::endl;
	return EXIT_SUCCESS;
}