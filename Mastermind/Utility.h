#pragma once
#include <iostream>
#include "String.h"

bool inArray(std::string& val, std::vector<std::string>& arr);
bool validInput(String& input, std::vector<std::string>& colors);
std::vector<std::string> generateCode(std::vector<std::string>& colors);
std::vector<std::string> getCodeFromUser(std::vector<std::string>& colors);