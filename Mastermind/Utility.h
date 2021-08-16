#pragma once
#include <iostream>

static bool validString(std::string& val, std::vector<std::string>& arr)
{
	return find(arr.begin(), arr.end(), val) != arr.end();
}

static bool validChar(char& val, std::vector<std::string>& arr)
{
	for (std::string color : arr)
		if (val == color[0]) 
			return true;
	return false;
}

std::vector<std::string> splitString(std::string str, std::string delimiter)
{
	size_t idx;
	std::vector<std::string> vec;

	// Convert string to lowercase
	for (char& c : str)
		c = tolower(c);

	// Split string into vector according to the delimiter.
	while ((idx = str.find(delimiter)) != str.npos) {
		vec.push_back(str.substr(0, idx));
		str.erase(0, idx + delimiter.size());
	}
	vec.push_back(str);

	return vec;
}

bool validInput(std::string input, std::vector<std::string>& colors)
{
	std::vector<std::string> split = splitString(input, " ");

	if (split.size() != 4) // Check number of input colors
		return false;

	for (std::string s : split) {
		// Return false if input isn't valid strings or chars describing the colors
		if (!validString(s, colors) && !(s.size() == 1 && validChar(s[0], colors)))
			return false;
	}

	return true;
}

std::vector<std::string> generateCode(std::vector<std::string>& colors) {
	std::vector<std::string> code;

	// Generate random code
	for (int i = 0; i < 4; ++i)
		code.push_back(colors[rand() % colors.size()]);

	return code;
}

std::vector<std::string> getCodeFromUser(std::vector<std::string>& colors) {
	std::string code;

	getline(std::cin, code);

	// Validate input
	while (!validInput(code, colors)) {
		std::cout << "Invalid input, please try again: ";
		getline(std::cin, code);
	}
	return splitString(code, " ");
}