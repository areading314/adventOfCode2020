#include <functional>
#include <iostream>
#include <utility>
#include <vector>

#include "Problems.h"


int main()
{
    unsigned int problemNumber = 0;
    std::vector<std::function<int (void)>>functions;
    functions.push_back(AOC2020::Problem1);
    functions.push_back(AOC2020::Problem2);
    functions.push_back(AOC2020::Problem3);
    functions.push_back(AOC2020::Problem4);
    functions.push_back(AOC2020::Problem5);

    std::cout << "Please enter the problem you would like to solve: " << std::endl;
    std::cin >> problemNumber;


    if (problemNumber < 1 || problemNumber > functions.size()) {
        std::cout << "Please enter a valid number. Goodbye." << std::endl;
		return EXIT_FAILURE;
    }
    else {
		std::function<int (void)> chosenFunction = functions[problemNumber - 1];
		std::cout << "You have selected Problem " << problemNumber << std::endl;
        return chosenFunction();
    }

}