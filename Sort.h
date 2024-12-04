#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>

class Sort{
private:
    //stats meaning: 0, name of recipe; 1, amt of ingredients; 2, # of steps; 3, time it takes to cook
    static std::unordered_map<std::string, std::vector<std::string>> recipeStats; //holds each recipe name and it's stats
    static std::unordered_map<std::string, std::vector<std::string>> recipeIngredients; // stores recipe name and it's ingredients
    static std::vector<std::vector<std::string>> recipeData; //stores recipe name, ingredient amount, steps, and time it takes to cook

public:
    static void readCSV(std::string file); //this should modify recipeData and recipe ingredients
    static std::vector<std::string> parseIngredients(std::string str);
    //takes in a vector containing the contents of the csv files and then sorts them by the given input option
    //Options would likely be the index of what we want to sort by:
    //i.e i want to sort by the amount of ingredients so option 1 would be vec[i][1]
    //OPTIONS ARE ONLY: 1, sort by amount of ingredients; 2, sort by # of steps; 3, sort by time it takes
    //WILL BREAK IF YOU USE 0, SORT ALPHABETICALLY
    //not done
    static void shellSort(std::vector<std::vector<std::string>> &vec, int option);
    //static std::vector<std::vector<std::string>> findRecipesS(std::vector<std::vector<std::string>> vec, std::string& mainIngredient);
    //finished
    static void quickSort(std::vector<std::vector<std::string>>& vec, int option, int low, int high);
    static std::vector<std::vector<std::string>> findRecipes(std::string& mainIngredient);
    static int partition(std::vector<std::vector<std::string>>& vec, int option, int low, int high);
};