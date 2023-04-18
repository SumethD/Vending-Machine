#include <iostream>
#include "LinkedList.h"
#include <iomanip>



/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
std::string mainMenu();
std::string readInput();
std::string displayItems(LinkedList& stock);

int main(int argc, char **argv)
{
    std::string choice ;
    if (argc != 3) {
        std::cerr << "Use: " << argv[0] << " stock.dat coins.dat" << std::endl;
        return 1;
    }

    std::string stockFile = argv[1];
    std::string coinsFile = argv[2];
    LinkedList itemstock;
    std::string filename = stockFile; 
    itemstock.loadData(filename);
    itemstock.sortByName();
    choice = mainMenu();
    bool exitLoop = false;
    while (!exitLoop) {
        // check if the input is empty (i.e., "Enter" was pressed)
        if (choice.empty()) {
            exitLoop = true;
        } 
        else if (choice == "1") {
            std::string newd= displayItems(itemstock);
            choice = mainMenu();
        }
        else if (choice == "2") {
            std::cout<<"choice 2"<<std::endl;
            choice = mainMenu();
        }
        else if (choice == "3") {
            std::cout<<"choice 3"<<std::endl;
            choice = mainMenu();
        }
        else if (choice == "4") {
            std::cout<<"choice 4"<<std::endl;
            choice = mainMenu();
        }
        else if (choice == "5") {
            std::cout<<"choice 5"<<std::endl;
            choice = mainMenu();
        }
        else if (choice == "6") {
            std::cout<<"choice 6"<<std::endl;
            choice = mainMenu();
        }
        else if (choice == "7") {
            std::cout<<"choice 7"<<std::endl;
            choice = mainMenu();
        }
        else if (choice == "8") {
            std::cout<<"choice 8"<<std::endl;
            choice = mainMenu();
        }
        else if (choice == "9") {
            return EXIT_SUCCESS;
        }
        else{
            std::cout<<"Invalid Input please re-enter"<<"\n"<<std::endl;
            choice = mainMenu();
        }
        
    }

}

std::string mainMenu(){
    std::cout << "Main Menu:"<< std::endl;
    std::cout << "    1.Display Items"<< std::endl;
    std::cout << "    2.Purhcase Items"<< std::endl;
    std::cout << "    3.Save and Exit"<< std::endl;
    std::cout << "Administrator-Only Menu:"<< std::endl;
    std::cout << "    4.Add Items"<< std::endl;
    std::cout << "    5.Remove Item"<< std::endl;
    std::cout << "    6.Display Coins"<< std::endl;
    std::cout << "    7.Reset Stock"<< std::endl;
    std::cout << "    8.Reset Coins"<< std::endl;
    std::cout << "    9.Abort Program"<< std::endl;
    std::cout << "Select your option (1-9)"<< std::endl;
    std::string option = readInput();
    return option;
    
}

std::string readInput(){
    std::string input;
    std::getline(std::cin, input);
    std::cout << std::endl;
    return input;
}

std::string displayItems(LinkedList& stock){
    Node* currentNode = stock.head;
    std::cout << "Items Menu" << std::endl;
    std::cout << "----------" << std::endl;         
    std::cout << std::left << std::setw(5) << "ID" << " | " << std::setw(50) << "Name" << " | " << std::setw(10) << "Available" << " | " << std::setw(6) << "Price" << std::endl;
    std::cout << std::setfill('-') << std::setw(79) << "-" << std::setfill(' ') << std::endl;
    while (currentNode != nullptr) {
        std::cout << std::left << std::setw(4) << currentNode->data->id << " | " << std::setw(50) << currentNode->data->name << " | " << std::setw(10) << currentNode->data->on_hand << " | $" << currentNode->data->price.dollars << "." <<currentNode->data->price.cents << std::endl;
        currentNode = currentNode->next;
    }
    std::cout<<std::endl;
    return "0";
}