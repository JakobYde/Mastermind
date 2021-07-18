#pragma once
#include "StringHandler.h"
#include <iostream>
#include <fstream>
#include <algorithm>

class Board
{
public:
	Board(std::string filename, std::vector<std::string> colors);
	Board(std::vector<std::string> board, std::vector<std::string> colors);

	void print();
	int UpdateBoard(std::vector<std::string> guess);
	std::vector<std::string> getColors();
	void setCode(std::vector<std::string> codeIn);
private:
	int maxTries;
	int NTries = 0;
	std::vector<std::string> code;
	std::vector<std::string> board;
	std::vector<std::string> colors;
	std::vector<std::string> getBoard(std::string filename);
};