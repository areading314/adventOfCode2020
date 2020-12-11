#include <iostream>
#include <unistd.h>

#include "Problems.h"
#include "WaitingArea.h"


namespace AOC2020 {
	int Problem11() {
		WaitingArea wa("inputs/Problem11Input.txt");
		std::uint32_t iteration = 0;
		wa.print(iteration);
		int count = 0;
		while (wa.update(false)) {
			if (count % 2 == 0) {
				system("clear");
				wa.print(++iteration);
				usleep(300000);
			}
			count++;
		}
		std::cout << "Total occupied at equilibrium: " << wa.countOccupied() << std::endl;
		WaitingArea wa2("inputs/Problem11Input.txt");
		iteration = 0;
		wa2.print(iteration);
		count = 0;
		while (wa2.update(true)) {
			if (count % 2 == 0) {
				system("clear");
				wa2.print(++iteration);
				usleep(300000);
			}
			count++;
		}
		std::cout << "Total occupied at equilibrium (LOS mode): " << wa2.countOccupied() << std::endl;
		return EXIT_SUCCESS;
	}
}