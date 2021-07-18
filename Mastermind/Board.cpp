#include "Board.h"

Board::Board(std::string filename, std::vector<std::string> cols)
{
	board = getBoard(filename);
	colors = cols;
	maxTries = board.size() - 5;
}

Board::Board(std::vector<std::string> boardIn, std::vector<std::string> cols)
{
	board = boardIn;
	colors = cols;
	maxTries = board.size() - 5;
}

void Board::print()
{
	std::cout << "Available colors are: ";
	for (std::string color : colors) std::cout << color << " ";
	std::cout << std::endl;
	for (std::string line : board) {
		std::cout << line << std::endl;
	}
}

int Board::UpdateBoard(std::vector<std::string> guess)
{
	++NTries;
	std::string keyPegs = "";
	std::vector<std::string> tempCode = code;
	for (int i = 0; i < guess.size(); ++i)
	{
		// Insert first letter of color instead of Xs to show previous guesses
		int idx = board[board.size() - NTries - 1].find('X');
		board[board.size() - NTries - 1][idx] = toupper(guess[i][0]);

		// Find out which and how many key pegs to use
		if (guess[i] == tempCode[i]) {
			keyPegs.append("R");
			tempCode[i] = "Used";
		}
		else {
			for (int j = 0; j < tempCode.size(); j++) {
				if (guess[i] == tempCode[j]) {
					keyPegs.append("W");
					tempCode[j] = "Used";
					break;
				}
			}
			if (keyPegs.size() <= i) keyPegs.append("-");
		}

	}
	// Add key pegs next to board in random order to indicate quality of guess
	random_shuffle(keyPegs.begin(), keyPegs.end());
	board[board.size() - NTries - 1].append(keyPegs);

	if (keyPegs == "RRRR") {
		
		for (int i = 0; i < code.size(); ++i) {
			int idx = board[1].find("H");
			board[1][idx] = toupper(code[i][0]);
		}
		return 1;
	}
	
	if (NTries > maxTries) return -1;

	return 0;
}

std::vector<std::string> Board::getColors()
{
	return colors;
}

void Board::setCode(std::vector<std::string> codeIn)
{
	code = codeIn;
}

std::vector<std::string> Board::getBoard(std::string filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cout << "Error opening board file";
		exit(1);
	}
	std::vector<std::string> board;
	std::string line;
	while (getline(file, line)) {
		board.push_back(line);
	}
	return board;
}