﻿//
// Created by amyho on 12/1/2024.
//
#include "Sort.h"
//Made static, this is required or error
std::unordered_map<std::string, std::vector<std::string>> Sort::recipeStats;
std::unordered_map<std::string, std::vector<std::string>> Sort::recipeIngredients; // stores recipe name and it's ingredients
std::vector<std::vector<std::string>> Sort::recipeData; //stores recipe name, ingredient amount, steps, and time it takes to cook

//turns string into a vector
std::vector<std::string> Sort::parseIngredients(std::string str) {
    std::vector<std::string> temp;
    //removes '[' and ']'
    std::string newStr = str.substr(1, str.size()-2);

    //parsing
    std::istringstream iStr(newStr);
    std::string ingredient;

    //takes first ingredient, is kind of an outlier
    std::getline(iStr, ingredient, ',');

    //removes single quotes and whitespace
    ingredient = ingredient.substr(1, ingredient.size()-2);
    temp.push_back(ingredient);

    while(std::getline(iStr, ingredient, ',')){
        //removes single quotes and whitespace
        ingredient = ingredient.substr(2, ingredient.size()-3);
        temp.push_back(ingredient);
    }

    return temp;
}

//used https://www.geeksforgeeks.org/csv-file-management-using-c/
//https://stackoverflow.com/questions/20256335/undefined-reference-for-vector

void Sort::readCSV(std::string file) {
    std::ifstream fin(file);
    std::string line;
    //std::cout << "readCSV has ran" << std::endl;
    if(fin.is_open()){
        std::getline(fin, line);
        //parses through csv file
        while(std::getline(fin, line)) {
            std::vector<std::string> row;
            std::stringstream s(line);
            std::string col;
            std::string ingredients;
            std::string name;
            std::vector<std::string> stats;

            //attempts to read line, skips if it doesn't work
            try {
                //row number, we do not want
                std::getline(s, col, ',');

                //name, we do want
                std::getline(s, col, ',');
                name = col;
                row.push_back(col);

                // Read quoted ingredients, skips anything that doesn't match formats
                //also generally no one would have them lying around their pantry anyways !
                if (!std::getline(s, col, '"') || !std::getline(s, ingredients, '"')) {
                    continue;
                }
                //parses ingredient string into a vector
                //then pushes to a recipeIngredients map
                recipeIngredients[name] = parseIngredients(ingredients);
                //skips extraneous ','
                std::getline(s, col, ',');
                //pushes back the rest of the columns
                while (std::getline(s, col, ',')) {
                    row.push_back(col);
                    stats.push_back(col);
                }
                //pushes row into recipe data
                recipeData.push_back(row);
                recipeStats[name] = stats;
                }
            //required for trys
            catch(const std::exception& e){}
        }
        //debug
//        if (!recipeData.empty()) {
//            for(const auto& row : recipeData){
//                for (const auto& col : row) {
//                    std::cout << col << " ";
//                }
//                std::cout << std::endl;
//            }
//
//            //std::cout << std::endl;
//            //std::cout << recipeData.size();
//            //std::cout << "\n";
//        }
//        if (!recipeIngredients.empty()) {
//            for (const auto& col : recipeIngredients[recipeData[0][0]]) {
//                std::cout << col << " ";
//            }
//        }
//        if (!recipeStats.empty()) {
//            for (const auto& col : recipeStats) {
//                std::cout << col.first << " ";
//                for(auto& e: col.second) {
//                    std::cout << e << " ";
//                }
//                std::cout << std::endl;
//            }
//        }

    }
    else{
        std::cout << "Error opening file";
        return;
    }
}

//these functions should return a vector which is basically the resorted recipeData
//OR you could make a function that extracts the recipes with that main ingredient
//and puts it into a vector to sort and that gets returned instead.
//you do NOT have to reorder the unordered_map recipeIngredients, that is there
//to assist you in looking up a recipe's ingredients (it's O(1) operation)
std::vector<std::vector<std::string>> Sort::shellShort(std::vector<std::vector<std::string>> vec, int option) {
    return std::vector<std::vector<std::string>>();
}

//taken from Sorting slides
void Sort::quickShort(std::vector<std::vector<std::string>>& vec, int option, int low, int high) {
    if(low < high){
        int pivot = partition(vec, option, low, high);
        quickShort(vec, option, low, pivot - 1);
        quickShort(vec, option, pivot + 1, high);
    }
}
//taken from Sorting slides
int Sort::partition(std::vector<std::vector<std::string>>& vec, int option, int low, int high) {
    //std::string pivot = vec[low][option];
    int pivot = std::stoi(vec[low][option]);
    int up = low, down = high;

    while(up < down){
        for(int j = low; j < high; j++){
            if(std::stoi(vec[up][option]) > pivot){
                break;
            }
            up++;
        }
        for(int j = high; j > low;  j--){
            if(std::stoi(vec[down][option]) < pivot){
                break;
            }
            down--;
        }
        if(up < down){
            std::swap(vec[up], vec[down]);
        }
    }

    std::swap(vec[low], vec[down]);
    return down;
}

std::vector<std::vector<std::string>> Sort::findRecipes(std::string& mainIngredient) {
    std::vector<std::vector<std::string>> temp;
    std::cout << "find recipes is running" << std::endl;
    //this is basically a crappy linear search !
    for(auto& ingredients: recipeIngredients){
        std::vector<std::string> subTemp;
        //yeah this looks bad...
        if(ingredients.second[0] == mainIngredient){
            subTemp.push_back(ingredients.first); //adds in the name of recipe
            subTemp.push_back(recipeStats[ingredients.first][0]); //adds in amt of ingredients
            subTemp.push_back(recipeStats[ingredients.first][1]); //adds in # of steps
            subTemp.push_back(recipeStats[ingredients.first][2]); //adds in time it takes
            //pushes the above into a vec that will contain all recipes that has this main ingredient
            temp.push_back(subTemp);
        }
    }
//    for (const auto& col : temp) {
//        for(auto& e: col) {
//            std::cout << e << " ";
//        }
//        std::cout << std::endl;
//    }

    return temp;
}
