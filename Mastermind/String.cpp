#include "String.h"

String::String()
{
}

String::String(const std::string& str) : string(str)
{
}

std::vector<std::string> String::split(std::string delimiter)
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

std::vector<String> String::split(String delimiter)
{
    std::vector<String> vec;
    int idx;
    while ((idx = string.find(delimiter.asString()) != string.npos)) {
        vec.push_back(string.substr(0, idx));
        string.erase(0, idx + delimiter.asString().size());
    }
    return vec;
}

void String::toLower()
{
    for (char& c : string) {
        c = tolower(c);
    }
}

std::string String::asString()
{
    return string;
}

void String::setString(std::string str)
{
    string = str;
}
