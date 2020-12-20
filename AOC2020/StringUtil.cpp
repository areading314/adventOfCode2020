#include <iostream>
#include "StringUtil.h"

void AOCUtils::splitString(const std::string& target, std::vector<std::string>& results, char separator) {
	results.clear();
	std::string::size_type last = 0;
	std::string::size_type i = 0;
	for (; i < target.size(); i++) {
		if ((target[i] == separator) && (i >= last)) {
			results.push_back(target.substr(last, i - last));
			last = i + 1;
		}
	}
	results.push_back(target.substr(last, target.size() - last));
}