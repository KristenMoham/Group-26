#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

class Sort{
private:
    static std::unordered_map<std::string, std::vector<std::string>> recipeIngredients; // stores recipe name and it's ingredients
    static std::vector<std::vector<std::string>> recipeData; //stores recipe name, ingredient amount, steps, and time it takes to cook

public:
    static void readCSV(std::string file); //this should modify recipeData and recipe ingredients
    static std::vector<std::string> parseIngredients(std::string str);
    //takes in a vector containing the contents of the csv files and then sorts them
    //by the given input option
    //Options would likely be the index of what we want to sort by:
    //i.e i want to sort by the amount of ingredients so option 1 would be vec[i][1]
    std::vector<std::vector<std::string>> shellShort(std::vector<std::vector<std::string>> vec, int option);
    std::vector<std::vector<std::string>> quickShort(std::vector<std::vector<std::string>> vec, int option);
};