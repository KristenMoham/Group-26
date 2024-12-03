#include <iostream>
#include "Sort.h"
//for testing
int main() {
    std::cout << "Hello, World!" << std::endl;
    Sort obj;

    Sort::readCSV("Sorted-Recipes.csv");
    std::string inge = "acorn squash";
    //std::string& ingredient =  inge;
    std::vector<std::vector<std::string>> recipesIncluded = Sort::findRecipes(inge);
    Sort::quickShort(recipesIncluded, 1, 0, recipesIncluded.size()-1);
    for (const auto& col : recipesIncluded) {
        for(auto& e: col) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
