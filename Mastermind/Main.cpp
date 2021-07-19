#pragma once
#include "Board.h"
#include "String.h"
#include "Utility.h"
#include <conio.h>

int main()
{
	const int nAttempts = 10;
	std::vector<std::string> colors = { "red", "green", "blue", "yellow", "purple", "orange", "cyan", "white"};

	while(true) {
		// Gamemode - one or two players
		std::cout << "Please press 'S' for single player or 'M' for multiplayer";
		char mode;
		while ((mode = tolower(_getch())) != 's' and mode != 'm');

		Board board = Board(nAttempts, colors);

		// Get code
		std::vector<std::string> code;
		if (mode == 's') code = generateCode(colors);
		else code = getCodeFromUser(colors);

		board.setCode(code);

		//Loop runs until the code is broken or all attemps have been used
		while (!board.isSolved() and board.getAttemptsLeft() > 0)
		{
			system("CLS");
			board.print();

			// Waiting for guess
			std::string guessString;
			String guess;

			std::cout << "Please enter your guess (use space as separator): ";
			getline(std::cin, guessString);
			guess.setString(guessString);

			while (!validInput(guess, colors)) {
				std::cout << "Invalid input, please try again" << std::endl;
				getline(std::cin, guessString);
				guess.setString(guessString);
			}
			board.updateBoard(guess.split(" "));
		}
		system("CLS");
		board.print();

		if (board.getAttemptsLeft() == 0)
			std::cout << "You have run out of attempts, the code was: ";
		else if (board.isSolved())
			std::cout << "You have guesses the code, congratulations! The code was: ";

		for (std::string color : code) std::cout << color << " ";
		std::cout << std::endl << "Press Enter to play again...";
		
		// Wait for Enter
		while (!_getch() == 13);
		system("CLS");
	}
	return 0;
}