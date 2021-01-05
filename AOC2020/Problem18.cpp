#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "FileUtil.h"
#include "Problems.h"


namespace AOC2020 {

	void tokenize(const std::string& input, std::vector<std::string>& output) {
		std::string currentstring;
		for (std::string::size_type i = 0; i < input.size(); i++) {
			if (input[i] == '(') {
				if (currentstring.size() > 0) output.push_back(currentstring);
				currentstring.clear();
				output.push_back("(");
			} else if (input[i] == ')') {
				if (currentstring.size() > 0) output.push_back(currentstring);
				currentstring.clear();
				output.push_back(")");
			}
			else if (input[i] == ' ') {
				if (currentstring.size() > 0) output.push_back(currentstring);
				currentstring.clear();
			}
			else if (input[i] == '+' || input[i] == '*') {
				if (currentstring.size() > 0) output.push_back(currentstring);
				currentstring.clear();
				std::string v = input.substr(i, 1);
				output.push_back(v);
			}
			else if (input[i] >= '0' && input[i] <= '9') {
				/* noop */
				currentstring.push_back(input[i]);
			}
			else {
				std::cout << "Invalid char: " << input[i] << std::endl;
			}
		}
		if (currentstring.size() > 0) output.push_back(currentstring);
	}

	enum class Operation {
		ADD,
		MULTIPLY
	};

	std::uint64_t calc_tokens(std::vector<std::string>::iterator& start,
							  std::vector<std::string>::iterator end,
							  bool multFirst) {
		std::stack<std::uint64_t> values;
		std::stack<Operation> ops;
		bool haveOp = false;
		while (start != end) {
			if (*start == "(") {
				if (haveOp && !multFirst) {
					std::uint64_t lhs = values.top();
					values.pop();
					Operation op = ops.top();
					ops.pop();
					if (op == Operation::ADD) {
						std::advance(start, 1);
						lhs += calc_tokens(start, end, multFirst);
					}
					else if (op == Operation::MULTIPLY) {
						std::advance(start, 1);
						lhs *= calc_tokens(start, end, multFirst);
					}
					values.push(lhs);
					haveOp = false;

				}
				else if (haveOp && multFirst) {
					Operation op = ops.top();
					if (op == Operation::ADD) {
						std::uint64_t lhs = values.top();
						values.pop();
						std::advance(start, 1);
						lhs += calc_tokens(start, end, multFirst);
						values.push(lhs);
						haveOp = false;
						ops.pop();
					}
					else if (op == Operation::MULTIPLY) {
						std::advance(start, 1);
						values.push(calc_tokens(start, end, multFirst));
						haveOp = false;
					}
				}
				else {
					std::advance(start, 1);
					values.push(calc_tokens(start, end, multFirst));
				}
			}
			else if (*start == ")") {
				if (multFirst) {
					std::uint64_t prod = 1;
					while (!values.empty()) {
						prod *= values.top();
						values.pop();
					}
					return prod;
				}
				return values.top();
			}
			else if (*start == "+") {
				haveOp = true;
				ops.push(Operation::ADD);
			}
			else if (*start == "*") {
				haveOp = true;
				ops.push(Operation::MULTIPLY);
			}
			else if ((*start)[0] >= '0' && (*start)[0] <= '9') {
				if (haveOp && !multFirst) {
					std::uint64_t lhs = values.top();
					values.pop();
					Operation op = ops.top();
					ops.pop();
					if (op == Operation::ADD) {
						lhs += std::stoull(*start);
					}
					else if (op == Operation::MULTIPLY) {
						lhs *= std::stoull(*start);
					}
					values.push(lhs);
					haveOp = false;
				}
				else if (haveOp && multFirst) {
					Operation op = ops.top();
					if (op == Operation::ADD) {
						std::uint64_t lhs = values.top();
						values.pop();
						lhs += std::stoull(*start);
						values.push(lhs);
						haveOp = false;
						ops.pop();
					}
					else if (op == Operation::MULTIPLY) {
						values.push(std::stoull(*start));
						haveOp = false;
					}
				}
				else {
					values.push(std::stoull(*start));
				}
			}
			start++;
		}
		if (multFirst) {
			std::uint64_t prod = 1;
			while (!values.empty()) {
				prod *= values.top();
				values.pop();
			}
			return prod;
		}
		return values.top();
	}

	std::uint64_t evaluate(const std::string& input, bool multFirst) {
		std::vector<std::string> tokens;
		tokenize(input, tokens);
		std::vector<std::string>::iterator it = tokens.begin();
		return calc_tokens(it, tokens.end(), multFirst);
	}


	int Problem18() {
		std::ifstream infile("inputs/Problem18Input.txt");
		std::string line;
		std::vector<std::string> lines;
		while (std::getline(infile, line)) {
			lines.push_back(line);
		}

		std::vector<std::uint64_t> values;
		for (const auto& s : lines) {
			values.push_back(evaluate(s, false));
		}
		std::uint64_t sum = 0;
		for (auto n : values) sum += n;
		std::cout << "Total evaluate values: " << sum << std::endl;
		values.clear();
		for (const auto& s : lines) {
			values.push_back(evaluate(s, true));
		}
		sum = 0;
		for (auto n : values) sum += n;
		std::cout << "Total evaluate values (multiplication first): " << sum << std::endl;
		return EXIT_SUCCESS;
	}
}