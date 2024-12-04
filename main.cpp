#include <iostream>
#include "Sort.h"
#include <string>
#include <vector>

//for testing
int main() {
    //std::cout << "Hello, World!" << std::endl;
    Sort obj;
    std::vector<std::vector<std::string>> sort5;
    std::string inge, filter,sortMethod;
    int filterNum, sortMethodNum;
    double time;

    Sort::readCSV("Sorted-Recipes.csv");
    std::cout<<"---- WELCOME TO SHELFCHEF ----\nChoose one main ingredient: ";
    //ingredient we are sorting by
    getline(std::cin, inge); // getline
    std::vector<std::vector<std::string>> recipesIncluded = Sort::findRecipes(inge);

    std::cout<<"\n---- ENTER WHAT YOU'D LIKE TO FILTER BY ----\n1. sort by amount of ingredients\n2. sort by # of steps\n3. sort by time it takes"<<std::endl;
    getline(std::cin, filter);
    filterNum = stoi(filter);


    std::cout<<"\n---- ENTER WHAT SORT YOU'D LIKE ----\n1. Quick sort\n2. ShellSort"<<std::endl;
    getline(std::cin, sortMethod);

    sortMethodNum = std::stoi(sortMethod);

    if(sortMethodNum == 1){
        sortMethod = "Quick Sort";
        time = Sort::quickSort(recipesIncluded, filterNum, 0, recipesIncluded.size()-1);
    } else if (sortMethodNum == 2){
        sortMethod = "Shell Sort";
        time = Sort::shellSort(recipesIncluded, filterNum);
    } else{
        std::cout<<"Enter a usable input. Try again."<<std::endl;
        return 1;
    }

    std::cout <<"Time for "<<sortMethod<<" is: \n"<< time << " microseconds\n" << std::endl;

//    for (const auto& col : recipesIncluded) {
//        for(auto& e: col) {
//            std::cout << e << " ";
//        }
//        std::cout << std::endl;
//    }
    int itemsPrinted = 0;
    int itemsPerPage =5;
    bool moreToPrint = true;
    while (moreToPrint && itemsPrinted < recipesIncluded.size()) {
        for (int i = itemsPrinted; i < std::min(itemsPrinted + itemsPerPage, int(recipesIncluded.size())); ++i) {
            for (const auto& e : recipesIncluded[i]) {
                std::cout << e << " ";
            }
            std::cout << std::endl;
        }

        itemsPrinted += itemsPerPage;

        // Ask the user if they want to print more
        if (itemsPrinted < recipesIncluded.size()) {
            std::cout << "\nDo you want to see more recipes? (y/n): ";
            char choice;
            std::cin >> choice;

            if (choice != 'y' && choice != 'Y') {
                moreToPrint = false;
            }
        }
    }
    return 0;
}
