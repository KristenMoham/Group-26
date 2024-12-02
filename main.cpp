#include <iostream>
#include "Sort.h"
//for testing
int main() {
    std::cout << "Hello, World!" << std::endl;
    Sort obj;

    Sort::readCSV("Sorted-Recipes.csv");
    return 0;
}
