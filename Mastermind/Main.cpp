#pragma once
#include "Board.h"
#include "StringHandler.h"
#include <conio.h>

bool in_array(std::string& val, std::vector<std::string>& arr)
{
	return find(arr.begin(), arr.end(), val) != arr.end();
}

bool validInput(StringHandler& input, std::vector<std::string>& colors) 
{
	input.toLower();
	std::vector<std::string> split = input.split(" ");
	if (split.size() != 4) return false;

	for (std::string s : split) {
		if (!in_array(s, colors)) return false;
	}
	
	return true;
}

std::vector<std::string> getCode(char& mode, std::vector<std::string>& colors)
{
	std::vector<std::string> code;
	// Singleplayer
	if (mode == 's') {
		for (int i = 0; i < 4; ++i)
		{
			code.push_back(colors[rand() % colors.size()]);
		}
	}
	//Multiplayer
	else {
		std::string codeString;
		StringHandler codeHandler;
		std::cout << "\nPlayer 1 please enter the code (use space as delimiter): ";
		getline(std::cin, codeString);
		codeHandler.setString(codeString);
		while (!validInput(codeHandler, colors)) {
			std::cout << "Invalid input, please try again: ";
			getline(std::cin, codeString);
			codeHandler.setString(codeString);
		}
		code = codeHandler.split(" ");
	}
	return code;
}

inline bool file_exists(const char* filename) {
	struct stat buffer;
	return (stat(filename, &buffer) == 0);
}

int main(int argc, char** argv)
{
	std::vector<std::string> colors = { "red", "green", "blue", "yellow", "purple", "orange", "cyan", "white" };

	std::vector<std::string> boardLayout = {
	{"          ---------------------"},
	{"Answer:   |   H   H   H   H   |"},
	{"          ---------------------"},
	{"Guess 10: |   X   X   X   X   | "},
	{"Guess 9:  |   X   X   X   X   | "},
	{"Guess 8:  |   X   X   X   X   | "},
	{"Guess 7:  |   X   X   X   X   | "},
	{"Guess 6:  |   X   X   X   X   | "},
	{"Guess 5:  |   X   X   X   X   | "},
	{"Guess 4:  |   X   X   X   X   | "},
	{"Guess 3:  |   X   X   X   X   | "},
	{"Guess 2:  |   X   X   X   X   | "},
	{"Guess 1:  |   X   X   X   X   | "},
	{"          ---------------------"} };

	// Allows for using custom board, however, the division lines should always be first, third and last,
	// the answer should be on the second line and X's and H's should still be used.
	std::string externalBoard = "";
	if (argc == 2 and file_exists(argv[1])) externalBoard = argv[1];

	while(true) {

		// Gamemode - one or two players
		std::cout << "Please press 'S' for single player or 'M' for multiplayer";
		char mode;
		while ((mode = tolower(_getch())) != 's' and mode != 'm');

		Board board = Board(boardLayout, colors);
		if (externalBoard != "") board = Board(externalBoard, colors);

		// Set code
		std::vector<std::string> code = getCode(mode, colors);
		board.setCode(code);

		//Loop runs until the code is broken or all attemps have been used
		int solved = 0;
		while (solved == 0)
		{
			system("CLS");
			board.print();

			// Waiting for guess
			std::string guess;
			StringHandler guessHandler;

			std::cout << "Please enter your guess (use space as delimiter): ";
			getline(std::cin, guess);
			guessHandler.setString(guess);

			while (!validInput(guessHandler, colors)) {
				std::cout << "Invalid input, please try again\n";
				getline(std::cin, guess);
				guessHandler.setString(guess);
			}
			solved = board.UpdateBoard(guessHandler.split(" "));
		}
		system("CLS");
		board.print();
		if (solved == -1) {
			std::cout << "You have run out of attempts and have lost, the code was: ";
			for (int i = 0; i < code.size(); ++i) std::cout << code[i] << " ";
			std::cout << std::endl;
		}
		else if (solved == 1) {
			std::cout << "You have guesses the code and have won, congratulations! The code was: ";
			for (int i = 0; i < code.size(); ++i) std::cout << code[i] << " ";
			std::cout << std::endl;
		}
		
		std::cout << "Press Enter to play again...";
		while (!_getch() == 13);
	}
	return 0;
}