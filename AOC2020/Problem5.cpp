#include <iostream>
#include <string>
#include <vector>

#include "FileUtil.h"
#include "Problems.h"

namespace AOC2020 {

	struct SeatLocation {
		unsigned char row;
		unsigned char col;
	};

	int SeatID(SeatLocation s) {
		return 8 * s.row + s.col;
	}

	SeatLocation parseSeatLocation(std::string seatString) {
		SeatLocation s;
		unsigned char low = 0, high = 128, bf = 2;

		for (unsigned char i = 0; i < 7; i++) {
			if (seatString[i] == 'F') {
				high = (unsigned char)(low + (unsigned char) (high - low) / bf);
			}
			else if (seatString[i] == 'B') {
				low = (unsigned char)(high - (unsigned char)(high - low) / bf);
			}
			else {
				std::cout << "this row is FUCKED: " << seatString << std::endl;
			}
		}
		s.row = low;
		unsigned char left = 0, right = 8;
		for (unsigned char i = 7; i < 10; i++) {
			if (seatString[i] == 'L') {
				right = (unsigned char)(left + (unsigned char)(right - left) / 2);
			}
			else if (seatString[i] == 'R') {
				left = (unsigned char)(right - (unsigned char)(right - left) / 2);
			}
			else {
				std::cout << "this row is FUCKED: " << seatString << std::endl;
			}
		}
		s.col = left;
		std::cout << "s " << (int) s.row << " " << (int) s.col << std::endl;
		return s;
	}


	int Problem5() {
		std::string filename("inputs/Problem5Input.txt");
		std::ifstream inputFile = AOCUtils::GetFile(filename);
		std::string line;
		std::vector<std::string> lines;
		std::vector<bool> takenSeats(1024);
		while (std::getline(inputFile, line)) {
			if (line.size() != 0) lines.push_back(line);
		}
		for (int i = 0; i < 1024; i++) {
			takenSeats[i] = false;
		}
		for (auto line : lines) {
			int seatId = SeatID(parseSeatLocation(line));
			takenSeats[seatId] = true;
		}
		int result;
		for (int i = 0; i < 1022; i++) {
			if (takenSeats[i] && (!takenSeats[i + 1]) && takenSeats[i + 2]) result = i + 1;
		}
		std::cout << "Your seat: " << result << std::endl;
		return EXIT_SUCCESS;
	}
}