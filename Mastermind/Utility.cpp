#include "Utility.h"

bool inArray(std::string& val, std::vector<std::string>& arr)
{
	return find(arr.begin(), arr.end(), val) != arr.end();
}

bool validInput(String& input, std::vector<std::string>& colors)
{
	input.toLower();
	std::vector<std::string> split = input.split(" ");
	if (split.size() != 4) return false;

	for (std::string s : split) {
		if (!inArray(s, colors)) return false;
	}

	return true;
}

std::vector<std::string> generateCode(std::vector<std::string>& colors) {
	std::vector<std::string> code;

	// Generate random code
	for (int i = 0; i < 4; ++i)
	{
		code.push_back(colors[rand() % colors.size()]);
	}

	return code;
}

std::vector<std::string> getCodeFromUser(std::vector<std::string>& colors) {
	std::string codeString;
	String code;

	// Get input
	std::cout << std::endl << "Player 1 please enter the code (use space as separator): ";
	getline(std::cin, codeString);
	code.setString(codeString);

	// Validate input
	while (!validInput(code, colors)) {
		std::cout << "Invalid input, please try again: ";
		getline(std::cin, codeString);
		code.setString(codeString);
	}
	return code.split(" ");
}
