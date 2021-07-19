#pragma once
#include "String.h"
#include <iostream>
#include <fstream>
#include <algorithm>

class Board
{
public:
	// Constructors
	Board(int nAttempts, std::vector<std::string> colors);

	// Functions
	void updateBoard(std::vector<std::string> guess);
	void updateRow(std::string& row, std::vector<std::string>& thisCode, char placeholder);
	void setCode(std::vector<std::string> codeIn);
	void print();
	int getAttemptsLeft();
	bool isSolved();
	std::vector<std::string> getColors();
private:
	// Variables
	bool solved = false;
	int attemptsLeft;
	std::vector<std::string> code;
	std::vector<std::string> board;
	std::vector<std::string> colors;

	// BoardLayout
	std::string boardDivision = "---------------------";
	std::string boardAnswer = "|   H   H   H   H   |";
	std::string boardGuess = "|   X   X   X   X   |";

	// Functions
	void createBoard(int nAttempts);
};