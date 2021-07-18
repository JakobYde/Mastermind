#pragma once
#include <string>
#include <vector>

class StringHandler
{
public:
    StringHandler();
    StringHandler(const std::string& str);

    std::vector<std::string> split(std::string delimiter);
    std::vector<StringHandler> split(StringHandler delimiter);
    void toLower();
    std::string asString();
    void setString(std::string str);
private:
    std::string string;
};