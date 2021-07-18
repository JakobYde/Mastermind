#include "StringHandler.h"

StringHandler::StringHandler()
{
}

StringHandler::StringHandler(const std::string& str) : string(str)
{
}

std::vector<std::string> StringHandler::split(std::string delimiter)
{
    std::string tempString = string;
    std::vector<std::string> vec;
    int idx;
    while ((idx = tempString.find(delimiter)) != tempString.npos) {
        vec.push_back(tempString.substr(0, idx));
        tempString.erase(0, idx + delimiter.size());
    }
    vec.push_back(tempString);
    return vec;
}

std::vector<StringHandler> StringHandler::split(StringHandler delimiter)
{
    std::vector<StringHandler> vec;
    int idx;
    while ((idx = string.find(delimiter.asString()) != string.npos)) {
        vec.push_back(string.substr(0, idx));
        string.erase(0, idx + delimiter.asString().size());
    }
    return vec;
}

void StringHandler::toLower()
{
    for (char& c : string) {
        c = tolower(c);
    }
}

std::string StringHandler::asString()
{
    return string;
}

void StringHandler::setString(std::string str)
{
    string = str;
}
