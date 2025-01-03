﻿//
//
#include "Sort.h"
//Made static, this is required or error
std::unordered_map<std::string, std::vector<std::string>> Sort::recipeStats; // stores recipe name and its stats
std::unordered_map<std::string, std::vector<std::string>> Sort::recipeIngredients; // stores recipe name and it's ingredients

//turns string into a vector
std::vector<std::string> Sort::parseIngredients(std::string str) {
    std::vector<std::string> temp;
    //removes '[' and ']'
    std::string newStr = str.substr(1, str.size()-1);

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
                //this specifically goes after recipes that have ingredients with double quotes...
                if (!std::getline(s, col, '"') || !std::getline(s, ingredients, ']')) {
                    continue;
                }
                //extraneous double quote
                if (!std::getline(s, col, '"')) {
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
                //instead of ingredients, it attaches the stats of the recipe
                recipeStats[name] = stats;
                }
            //required for trys
            catch(const std::exception& e){}
        }

    }
    else{
        std::cout << "Error opening file";
        return;
    }
}

double Sort::shellSort(std::vector<std::vector<std::string>> &vec, int option) {
    //start timer
    auto start =  std::chrono::high_resolution_clock::now();

    //gap is equal to half the size of the recipe list
    int n = vec.size();
    int gap = n/2;
    //gap decreases by half each loop until it reaches 0
    while(gap > 0){
        //starting from the gap loop though each element comparing its gap pair
        for(int i = gap; i < n; i++){
            //get the first element for comparisons
            std::vector<std::string> temp = vec[i];
            int tempVar = stoi(temp[option]);
            int j = i;

            //compare with gap partner until in right spot
            while(j >= gap && stoi(vec[j - gap][option]) > tempVar){
                vec[j] = vec[j - gap];
                j -= gap;
            }
            vec[j] = temp;
        }

        //decrease gap by half
        gap /= 2;
    }

    //end timer
    auto end =  std::chrono::high_resolution_clock::now();
    //calculate time taken
    auto time2 = end - start;
    //convert to double in seconds
    double dTime = time2.count();
    return dTime;
}

//taken from Sorting slides
double Sort::quickSort(std::vector<std::vector<std::string>>& vec, int option, int low, int high) {
    //start timer
    auto start = std::chrono::high_resolution_clock::now();

    //not done if the 'pointers' aren't past eachother
    if(low < high){
        //index of the pivot/what we sort around
        int pivot = partition(vec, option, low, high);
        //quick sorts the 2 halves
        quickSort(vec, option, low, pivot - 1);
        quickSort(vec, option, pivot + 1, high);
    }

    //end timer
    auto end =  std::chrono::high_resolution_clock::now();
    //calculate time taken
    auto time2 = end - start;
    //convert to double in seconds
    double dTime = time2.count();
    return dTime;
}

//taken from Sorting slides
int Sort::partition(std::vector<std::vector<std::string>>& vec, int option, int low, int high) {
    //std::string pivot = vec[low][option];
    int pivot = std::stoi(vec[low][option]);
    int up = low, down = high;

    //as long as up and down 'pointers' dont pass eachother
    while(up < down){
        //continuously increment up until it is greater than the val of pivot
        for(int j = low; j < high; j++){
            if(std::stoi(vec[up][option]) > pivot){
                break;
            }
            up++;
        }
        //continuously decrement down until it is less than the val of pivot
        for(int j = high; j > low;  j--){
            if(std::stoi(vec[down][option]) < pivot){
                break;
            }
            down--;
        }
        //if up is still less than down, swap the two
        //up's element is greater than down's element at this point
        if(up < down){
            std::swap(vec[up], vec[down]);
        }
    }
    //swap the pivot with down, return down so it can be used as the new pivot
    std::swap(vec[low], vec[down]);
    return down;
}

//compiles all the recipes that share the same main ingredient found in the recipeIngredients map into one vector,
//that vector would contain the information used to sort the recipe by, that information is stored in recipeStats
std::vector<std::vector<std::string>> Sort::findRecipes(std::string &mainIngredient) {
    std::vector<std::vector<std::string>> temp;
    //linear search
    for(auto& ingredients: recipeIngredients){
        std::vector<std::string> subTemp;
        //does the process of creating the inner vector
        if(ingredients.second[0] == mainIngredient){
            subTemp.push_back(ingredients.first); //adds in the name of recipe
            subTemp.push_back(recipeStats[ingredients.first][0]); //adds in amt of ingredients
            subTemp.push_back(recipeStats[ingredients.first][1]); //adds in # of steps
            subTemp.push_back(recipeStats[ingredients.first][2]); //adds in time it takes
            subTemp.push_back(recipeStats[ingredients.first][3]); //adds in the ID of recipe
            //pushes the above into a vec that will contain all recipes that has this main ingredient
            temp.push_back(subTemp);
        }
    }
    return temp;
}
