#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>

class Sort{
private:
    //stats meaning: 0, name of recipe; 1, amt of ingredients; 2, # of steps; 3, time it takes to cook; 4, id for recipe
    static std::unordered_map<std::string, std::vector<std::string>> recipeStats; //holds each recipe name and it's stats
    static std::unordered_map<std::string, std::vector<std::string>> recipeIngredients; // stores recipe name and it's ingredients

public:
    static void readCSV(std::string file); //this should modify recipeData and recipe ingredients
    static std::vector<std::string> parseIngredients(std::string str);
    //takes in a vector containing all recipes that share a common main ingredient and then sorts them by the given input option
    //Options would likely be the index of what we want to sort by:
    //i.e i want to sort by the amount of ingredients so option 1 would be vec[i][1]
    //OPTIONS ARE ONLY: 1, sort by amount of ingredients; 2, sort by # of steps; 3, sort by time it takes
    static double shellSort(std::vector<std::vector<std::string>>& vec, int option);
    static double quickSort(std::vector<std::vector<std::string>>& vec, int option, int low, int high);
    static std::vector<std::vector<std::string>> findRecipes(std::string& mainIngredient);
    static int partition(std::vector<std::vector<std::string>>& vec, int option, int low, int high);
};