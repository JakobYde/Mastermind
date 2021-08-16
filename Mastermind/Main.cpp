#pragma once
#include "Board.h"
#include <conio.h>
#include "Utility.h"

int main()
{
	const int nAttempts = 10;
	std::vector<std::string> colors = { "red", "green", "blue", "yellow", "purple", "orange", "cyan", "white"};

	while(true) {
		// Gamemode - one or two players
		std::cout << "Please press 'S' for single player or 'M' for multiplayer" << std::endl;
		char mode;
		while ((mode = tolower(_getch())) != 's' and mode != 'm'); // Waiting for input

		// Get code
		std::vector<std::string> code;
		if (mode == 's') 
			code = generateCode(colors); // Random code
		else {
			std::cout << std::endl << "Player 1 please enter the code (use space as separator): ";
			code = getCodeFromUser(colors); // User enters code
		}

		Board board = Board(nAttempts, colors, code);
		board.printBoard();

		int state = UNSOLVED;
		std::vector<std::string> guess;

		// Loop until the code is guessed or all attemps have been used
		while (state == UNSOLVED) {
			std::cout << "Please enter your guess (use space as separator): ";
			
			guess = getCodeFromUser(colors);

			state = board.updateBoard(guess);
		}
		
		// Check and print the final state
		if (state == FAILED)
			std::cout << "You have run out of attempts, the code was: ";
		else if (state == SOLVED)
			std::cout << "You have guesses the code, congratulations! The code was: ";

		// Display code
		for (std::string color : code) std::cout << color << " ";
		std::cout << std::endl << "Press Enter to play again...";
		
		// Wait for Enter
		while (!(_getch() == 13));
		system("CLS"); // Clear console
	}
	return 0;
}