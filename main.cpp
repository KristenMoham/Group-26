#include <iostream>
#include "Sort.h"
//for testing
int main() {
    //std::cout << "Hello, World!" << std::endl;
    Sort obj;

    Sort::readCSV("Sorted-Recipes.csv");
    //ingredient we are sorting by
    std::string inge = "acorn squash";

    std::vector<std::vector<std::string>> recipesIncluded = Sort::findRecipes(inge);
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
