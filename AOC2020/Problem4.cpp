#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "Problems.h"
#include "FileUtil.h"
#include "StringUtil.h"

const std::regex heightRegex("(\\d{1,3})(cm|in)");
const std::regex eyeColorRegex("(amb|blu|brn|gry|grn|hzl|oth)");
const std::regex pidRegex("\\d{9}");
const std::regex hairColorRegex("#[a-f0-9]{6}");


bool validateHeight(const std::string& hgt) {
	std::smatch matchedGroups;
	std::regex_search(hgt, matchedGroups, heightRegex);
	if (matchedGroups.size() == 0) { return false; }
	int height = std::stoi(matchedGroups[1]);
	std::string units = matchedGroups[2];
	if (units == "in") {
		if (height < 59 || height > 76) return false;
	}
	else if (units == "cm") {
		if (height < 150 || height > 193) return false;
	}
	else {
		std::cout << "Invalid height: " << hgt << std::endl;
	}
	return true;
}


bool validateLines(const std::vector<std::string>& lines) {
	std::unordered_map<std::string, std::string> fields;
	std::vector<std::string> chunks;
	for (auto line : lines) {
		AOCUtils::splitString(line, chunks, ' ');
		for (auto chunk : chunks) {
			std::vector<std::string> kv;
			AOCUtils::splitString(chunk, kv, ':');
			fields.emplace(kv[0], kv[1]);
		}
	}
	bool missingField = false;
	if (fields.find("hgt") == fields.end()
		|| fields.find("byr") == fields.end()
		|| fields.find("hcl") == fields.end()
		|| fields.find("eyr") == fields.end()
		|| fields.find("iyr") == fields.end()
		|| fields.find("ecl") == fields.end()
		|| fields.find("pid") == fields.end()) {
		missingField = true;
	}
	if (missingField) { return false; }
	auto byr = std::stoi((*fields.find("byr")).second);
	if (byr < 1920 || byr > 2002) { return false; }
	auto iyr = std::stoi((*fields.find("iyr")).second);
	if (iyr < 2010 || iyr > 2020) { return false; }
	auto eyr = std::stoi((*fields.find("eyr")).second);
	if (eyr < 2020 || eyr > 2030) { return false; }
	auto hgt = (*fields.find("hgt")).second;
	if (!validateHeight(hgt)) { return false; }
	auto ecl = (*fields.find("ecl")).second;
	if (!std::regex_match(ecl, eyeColorRegex)) { return false; }
	auto hcl = (*fields.find("hcl")).second;
	if (!std::regex_match(hcl, hairColorRegex)) { return false; }
	auto pid = (*fields.find("pid")).second;
	if (!std::regex_match(pid, pidRegex)) { return false; }
	return true;
}


int AOC2020::Problem4() {
	std::string filename("inputs/P4Input.txt");
	std::ifstream inputFile = AOCUtils::GetFile(filename);
	std::string line;
	std::vector<std::string> lines;
	unsigned int validLines = 0;
	while (std::getline(inputFile, line)) {
		if (line.size() == 0) {
			if (validateLines(lines)) {
				validLines++;
			}
			lines.clear();
		}
		else {
			lines.push_back(line);
		}
	}
	if (validateLines(lines)) {
		validLines++;
	}
	std::cout << "Valid passports: " << validLines << std::endl;
	return EXIT_SUCCESS;
}