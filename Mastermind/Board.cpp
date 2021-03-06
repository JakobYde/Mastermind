#include "Board.h"

Board::Board(int nAttempts, std::vector<std::string> cols, std::vector<std::string> codeIn)
{
	colors = cols;
	attemptsLeft = nAttempts;
	code = codeIn;
	createBoard(nAttempts);
	printBoard();
}

Board::~Board()
{
}

int Board::updateBoard(std::vector<std::string> guess)
{
	int retval = UNSOLVED;
	std::string keyPegs = "";
	std::vector<std::string> tempCode = code;
	int row = attemptsLeft + 2;

	for (int i = 0; i < guess.size(); ++i)
	{
		// Insert first letter of color instead of Xs to show previous guesses
		size_t idx = board[row].find('X');
		board[row][idx] = toupper(guess[i][0]);

		// Check for correct colors in correct positions
		if (guess[i][0] == tempCode[i][0]) {
			keyPegs.append("R");
			tempCode[i] = "Used";
			continue;
		}

		// Check for correct colors in wrong positions
		for (int j = 0; j < tempCode.size(); j++) {
			if (guess[i][0] == tempCode[j][0]) {
				keyPegs.append("W");
				tempCode[j] = "Used";
				break;
			}
		}
	}
	// Add key pegs next to board in sorted order to indicate quality of guess
	sort(keyPegs.begin(), keyPegs.end());
	reverse(keyPegs.begin(), keyPegs.end());

	// Pad with dashes for incorrect colors
	while (keyPegs.size() < 4) keyPegs.append("-");
	
	board[row].append(keyPegs);

	--attemptsLeft;
	if (keyPegs == "RRRR") // If the code is guessed
		retval = SOLVED;
	else if (attemptsLeft == 0) // If all attempts are used
		retval = FAILED;

	if (retval != UNSOLVED)
		updateRow(board[1], code, 'H');
	
	printBoard();

	return retval;
}

void Board::createBoard(int nAttempts)
{
	// Example of board layout

/*            ---------------------
	Answer:   |   H   H   H   H   |
			  ---------------------
	Guess 10: |   X   X   X   X   |
	Guess 9:  |   X   X   X   X   |
	Guess 8:  |   X   X   X   X   |
	Guess 7:  |   X   X   X   X   |
	Guess 6:  |   X   X   X   X   |
	Guess 5:  |   X   X   X   X   |
	Guess 4:  |   X   X   X   X   |
	Guess 3:  |   X   X   X   X   |
	Guess 2:  |   X   X   X   X   |
	Guess 1:  |   X   X   X   X   |
			  ---------------------*/

	// This method could also load the board from a file, 
	// however, then the program could not be run using only the binary. 

	// BoardLayout
	std::string boardDivision = "---------------------";
	std::string boardAnswer = "|   H   H   H   H   |";
	std::string boardGuess = "|   X   X   X   X   |";

	board.push_back("          " + boardDivision);
	board.push_back("Answer:   " + boardAnswer);
	board.push_back("          " + boardDivision);

	// Insertion of guess rows
	for (int i = nAttempts; i > 0; --i) {
		std::string prefix = "Guess " + std::to_string(i) + ":"; // Write Guess and number

		for (size_t i = prefix.size(); i < 10; ++i) prefix += " "; // Padding with spaces
		
		board.push_back(prefix + boardGuess);
	}

	board.push_back("          " + boardDivision);
}

void Board::updateRow(std::string& row, std::vector<std::string>& thisCode, char placeholder)
{
	for (std::string color : thisCode) {
		size_t idx = row.find(placeholder);
		row[idx] = toupper(color[0]);
	}
}

int Board::getAttemptsLeft() const
{
	return attemptsLeft;
}

std::vector<std::string> Board::getColors() const
{
	return colors;
}

void Board::printBoard() const
{
	system("CLS");
	std::cout << "Available colors are: ";
	for (std::string color : colors) std::cout << color << " ";
	std::cout << std::endl << "Example of a valid input: [red blue green red] OR [r b g r] (without brackets)" << std::endl;

	for (std::string line : board) {
		std::cout << line << std::endl;
	}
}