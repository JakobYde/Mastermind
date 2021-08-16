#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

enum states {
	UNSOLVED = 0,
	SOLVED = 1,
	FAILED = -1
};

class Board
{
public:
	// Constructors and destructors
	Board(int nAttempts, std::vector<std::string> colors, std::vector<std::string> code);
	~Board();

	// Functions
	int updateBoard(std::vector<std::string> guess);
	void printBoard() const;

private:
	// Variables
	int attemptsLeft;
	std::vector<std::string> code;
	std::vector<std::string> board;
	std::vector<std::string> colors;

	// Functions
	void createBoard(int nAttempts);
	void updateRow(std::string& row, std::vector<std::string>& thisCode, char placeholder);
	int getAttemptsLeft() const;
	std::vector<std::string> getColors() const;
};