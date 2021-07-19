#pragma once
#include <string>
#include <vector>

class String
{
public:
    // Constructors
    String();
    String(const std::string& str);

    // Functions
    void toLower();
    void setString(std::string str);
    std::vector<std::string> split(std::string delimiter);
    std::vector<String> split(String delimiter);
    std::string asString();
    
private:
    // Variables
    std::string string;
};