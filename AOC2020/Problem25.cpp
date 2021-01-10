#include <iostream>

#include "Problems.h"

namespace AOC2020 {
	std::uint64_t transform(std::uint64_t value, std::uint64_t subject) {
		return (value * subject) % 20201227;
	}

	int Problem25() {
		std::uint64_t doorPublicKey = 10604480;
		std::uint64_t cardPublicKey = 4126658;

		std::uint64_t doorLoopSize = 0;
		std::uint64_t cardLoopSize = 0;
		std::uint64_t value = 1;
		while (value != doorPublicKey) {
			value = transform(value, 7);
			doorLoopSize++;
		}
		std::cout << "Door loopsize: " << doorLoopSize << std::endl;

		value = 1;
		while (value != cardPublicKey) {
			value = transform(value, 7);
			cardLoopSize++;
		}
		std::cout << "Card loopsize: " << cardLoopSize << std::endl;

		value = 1;
		for (std::uint64_t i = 0; i < cardLoopSize; i++) {
			value = transform(value, doorPublicKey);
		}
		std::cout << "Encryption key: " << value << std::endl;

		value = 1;
		for (std::uint64_t i = 0; i < doorLoopSize; i++) {
			value = transform(value, cardPublicKey);
		}
		std::cout << "Encryption key: " << value << std::endl;

		return EXIT_SUCCESS;
	}
}