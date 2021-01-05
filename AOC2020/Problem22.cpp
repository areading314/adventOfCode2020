#include <iostream>
#include <list>
#include <sstream>
#include <unordered_set>
#include <vector>

#include "FileUtil.h"
#include "Problems.h"

namespace AOC2020 {
	long long score(const std::list<int>& deck) {
		long long i = 1;
		long long result = 0;
		for (auto idx = deck.rbegin(); idx != deck.rend(); idx++) {
			result += *idx * i++;
		}
		return result;
	}

	std::string deck2str(const std::list<int> deck) {
		std::stringstream ss("");
		for (auto d : deck) ss << d << ",";
		return ss.str();
	}

	std::string decks2str(const std::list<int>& p1deck, const std::list<int>& p2deck) {
		std::stringstream ss("");
		ss << deck2str(p1deck) << "-" << deck2str(p2deck);
		return ss.str();
	}

	bool recursiveCombatP1Win(std::list<int> p1deck, std::list<int> p2deck) {
		std::unordered_set<std::string> seenGames;
		std::string deckstring;
		while (p1deck.size() > 0 && p2deck.size() > 0) {
			deckstring = decks2str(p1deck, p2deck);
			if (seenGames.find(deckstring) != seenGames.end()) {
				std::cout << "dejavu: " << deckstring << std::endl;
				std::cout << "p1win score: " << score(p1deck) << std::endl;
				return true; // p1 wins
			}
			seenGames.insert(deckstring);
			int p1 = p1deck.front();
			int p2 = p2deck.front();
			p1deck.pop_front();
			p2deck.pop_front();

			if ((p1deck.size() >= p1) && (p2deck.size() >= p2)) {
				std::list<int> p1deckcopy;
				std::list<int> p2deckcopy;
				for (auto i : p1deck) p1deckcopy.push_back(i);
				for (auto i : p2deck) p2deckcopy.push_back(i);
				while (p1deckcopy.size() > p1) p1deckcopy.pop_back();
				while (p2deckcopy.size() > p2) p2deckcopy.pop_back();
				bool recursiveOutcome = recursiveCombatP1Win(p1deckcopy, p2deckcopy);
				if (recursiveOutcome) {
					std::cout << "p1 won recursive battle." << std::endl;
					p1deck.push_back(p1);
					p1deck.push_back(p2);
				}
				else {
					std::cout << "p2 won recursive battle." << std::endl;
					p2deck.push_back(p2);
					p2deck.push_back(p1);
				}
			}
			else {
				if (p1 > p2) {
					std::cout << "p1 won compare." << std::endl;
					p1deck.push_back(p1);
					p1deck.push_back(p2);
				}
				else {
					std::cout << "p2 won compare." << std::endl;
					p2deck.push_back(p2);
					p2deck.push_back(p1);
				}
			}
		}
		if (p1deck.size() == 0) {
			std::cout << "p2win score: " << score(p2deck) << std::endl;
			return false;
		}
		else {
			std::cout << "p1win score: " << score(p1deck) << std::endl;
			return true;
		}
	}

	int Problem22() {
		std::list<int> player1Deck;
		std::list<int> player2Deck;
		std::string line;
		std::ifstream infile = AOCUtils::GetFile("inputs/Problem22Input.txt");

		bool skipOne = true;
		while (std::getline(infile, line) && line.size() > 0) {
			if (!skipOne) {
				player1Deck.push_back(std::stoi(line));
			}
			skipOne = false;
		}

		skipOne = true;
		while (std::getline(infile, line) && line.size() > 0) {
			if (!skipOne) {
				player2Deck.push_back(std::stoi(line));
			}
			skipOne = false;
		}

		std::cout << "Player 1 Deck: ";
		for (const auto& s : player1Deck) std::cout << s << ", ";
		std::cout << std::endl;
		std::cout << "Player 2 Deck: ";
		for (const auto& s : player2Deck) std::cout << s << ", ";
		std::cout << std::endl;

		/*
		while (player1Deck.size() > 0 && player2Deck.size() > 0) {
			int p1 = player1Deck.front();
			player1Deck.pop_front();
			int p2 = player2Deck.front();
			player2Deck.pop_front();

			if (p1 > p2) {
				player1Deck.push_back(p1);
				player1Deck.push_back(p2);
			}
			else {
				player2Deck.push_back(p2);
				player2Deck.push_back(p1);
			}
		}

		if (player1Deck.size() == 0) {
			std::cout << "Player 2 wins! Final score: " << score(player2Deck) << std::endl;
		}
		if (player2Deck.size() == 0) {
			std::cout << "Player 1 wins! Final score: " << score(player1Deck) << std::endl;
		}
		*/

		infile.clear();
		infile.seekg(0);
		player1Deck.clear();
		player2Deck.clear();

		skipOne = true;
		while (std::getline(infile, line) && line.size() > 0) {
			if (!skipOne) {
				player1Deck.push_back(std::stoi(line));
			}
			skipOne = false;
		}

		skipOne = true;
		while (std::getline(infile, line) && line.size() > 0) {
			if (!skipOne) {
				player2Deck.push_back(std::stoi(line));
			}
			skipOne = false;
		}

		std::cout << "recursive combat commencing: " << std::endl;
		std::cout << "Player 1 Deck: ";
		for (const auto& s : player1Deck) std::cout << s << ", ";
		std::cout << std::endl;
		std::cout << "Player 2 Deck: ";
		for (const auto& s : player2Deck) std::cout << s << ", ";
		std::cout << std::endl;
		recursiveCombatP1Win(player1Deck, player2Deck);

		return EXIT_SUCCESS;
	}
}