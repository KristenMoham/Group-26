#include <iostream>
#include "Sort.h"
//for testing
int main() {
    //std::cout << "Hello, World!" << std::endl;
    Sort obj;

    Sort::readCSV("Sorted-Recipes.csv");
    //ingredient we are sorting by
    //std::string inge = "acorn squash";
    std::string inge = "butter";


    std::vector<std::vector<std::string>> recipesIncluded = Sort::findRecipes(inge);
    for(const auto& row : recipesIncluded){
        for (const auto& col : row) {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
   double time = Sort::quickSort(recipesIncluded, 1, 0, recipesIncluded.size()-1);

//    double time = Sort::shellSort(recipesIncluded, 1);

    std::cout << time << std::endl;

    for (const auto& col : recipesIncluded) {
        for(auto& e: col) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
