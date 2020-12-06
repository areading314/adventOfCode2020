#include <iostream>

#include "FileUtil.h"

std::ifstream AOCUtils::GetFile(const std::string& filename) {
	std::ifstream inputFile(filename);
	if (!inputFile.is_open()) {
		std::cerr << "Could not open the file: " << filename << std::endl;
	}
	return inputFile;
}
