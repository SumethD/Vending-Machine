#include <iostream>
#include "LinkedList.h"
#include "Coin.h"
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <fstream>


/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program.
 **/
std::string mainMenu();
std::string readInput();
std::string displayItems(LinkedList &stock);

int main(int argc, char **argv)
{
    std::string choice;
    if (argc != 3)
    {
        std::cerr << "Use: " << argv[0] << " stock.dat coins.dat" << std::endl;
        return 1;
    }

    std::string stockFile = argv[1];
    std::string coinsFile = argv[2];
    LinkedList itemstock;
    Coin coinstock;

    std::string filename = stockFile;
    std::string coinsf = coinsFile;
    
    std::string stock_file;
    std::string coins_file;


    coinstock.loadCoin(coinsf);
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
            std::string newd = displayItems(itemstock);
            choice = mainMenu();
        }
        else if (choice == "2") {

            std::string itemId, name, desc;
            double price;
            int stockCount;


            std::cout << "Purchase Item" << std::endl;
            std::cout << "-------------" << std::endl;
            std::cout << "Please enter the id of the item you wish to purchase: ";
            std::getline(std::cin, itemId);
            bool validId = false;



            bool foundItem = false;
            for (int i = 0; i < itemstock.getLength() && !foundItem; i++) {
                Item* item = itemstock.get(i);
                if (item->getId() == itemId) {
                    name = item->getName();
                    desc = item->getDescription();
                    price = item->getPrice();
                    stockCount = item->getStockCount();
                    validId = true;
                    foundItem = true;
                }
            }


            /*


            for (int i = 0; i < itemstock.getLength(); i++) {
                Item* item = itemstock.get(i);
                if (item->getId() == itemId) {
                    name = item->getName();
                    desc = item->getDescription();
                    price = item->getPrice();
                    stockCount = item->getStockCount();
                    validId = true;
                    break;
                }
            }

            */


            if(!validId){
                std::cout << "Invalid item ID." << std::endl; ////move to getID
                choice = mainMenu();
            }
            else if(stockCount <= 0){
                std::cout << "This item is out of stock." << std::endl;
                choice = mainMenu();
            }



            else{
                std::cout << "You have selected \"" << name << "\". This will cost you $ " << std::fixed << std::setprecision(2) << price << "." << std::endl;
                double amountPaid = 0.0;
                double remainingAmount = price;
                bool transactionCancelled = false;
                while (remainingAmount > 0.0 && !transactionCancelled) {


                    std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;
                    std::string input;
                    std::getline(std::cin, input);


                    if (input.empty()) {
                    // Transaction cancelled, refund the amount paid and return to main menu
                    std::cout << "Transaction cancelled. Refunding $" << amountPaid << "." << std::endl;
                    ///////// ADD REFUND FUNCTIONAILITY ///////////
                    choice = mainMenu();
                    }
                    else{
                        int amount = std::stoi(input);
                        if (amount < 0) {
                            std::cout << "Invalid amount. Please try again." << std::endl;
                        }
                        else if(amount > remainingAmount * 100){
                            std::cout << "You have paid too much. Your change is $" << amountPaid - price << "." << std::endl;
                            ////// refund coins amt paid - price
                            choice = mainMenu();
                            transactionCancelled = true;

                        }
                        else if(!coinstock.isValidCoin(amount)){
                            std::cout << "Invalid denomination of money. Please try again." << std::endl;
                        }
                        else{
                            amountPaid += amount / 100.0;
                            remainingAmount -= amount / 100.0;
                            if (remainingAmount == 0.0) {
                                std::cout << "Here is your " << name << "." << std::endl;
                                itemstock.get(itemId)->reduceStockCount(1);
                                updateCoinStock(amountPaid);
                                choice = mainMenu();
                                transactionCancelled = true;
                                }
        }

        

        
        else if (choice == "3") {




            std::ofstream stock_file(stockFile);
            std::ofstream coins_file(coinsFile);

            if (stock_file.is_open() && coins_file.is_open()) {
                itemstock.writeData(stock_file); // Pass ofstream object as reference
                coinstock.writeCoin(coins_file);
                stock_file.close();
                coins_file.close();
                std::cout << "Data saved successfully." << std::endl;
                exit(0);
            }
            else {
                std::cerr << "Error: Cannot open file." << std::endl;
                exit(1);
            }

            /*std::ofstream stock_file(stockFile);
            std::ofstream coins_file(coinsFile);

            if (stock_file.is_open() && coins_file.is_open()) {
                itemstock.writeData(stock_file);
                coinstock.writeCoin(coins_file);
                stock_file.close();
                coins_file.close();
                std::cout << "Data saved successfully." << std::endl;
                exit(0);
            }
            else {
                std::cerr << "Error: Cannot open file." << std::endl;
                exit(1);
            }*/


        }




        
        else if (choice == "4") {
            std::string newId = itemstock.nextID();
            std::cout << "The id of the new stock will be: " << newId << std::endl;

            std::string name, description, prc;

            std::cout << "Enter the Item name: ";
            std::getline(std::cin, name);
            if (name.empty()){
                std::cout << "Cancelling [add item] as requested." << std::endl;
                choice = mainMenu();
            }
            else {
                std::cout << "Enter the item description: ";
                std::getline(std::cin, description);
                if (description.empty()){
                    std::cout << "Cancelling [add item] as requested.." << std::endl;
                    choice = mainMenu();
                }
                else{
                    std::cout << "Enter the price for the item: ";
                    std::getline(std::cin, prc);
                    bool ifpriceEntered = true;
                    double price;
                    int dollars = 0;
                    int cents = 0;
                    bool corrprc = false;
                    double epsilon = 1e-9;

                    if (prc.empty())
                    {
                        std::cout << "Cancelling [add item] as requested." << std::endl;
                        choice = mainMenu();
                    }
                    else
                    {
                            while (!corrprc)
                            {
                                if (!ifpriceEntered){
                                    std::cerr << "Enter price in dollars and cents" << std::endl;
                                    std::cout << "Enter the price for the item: ";
                                    std::getline(std::cin, prc);
                                }
                                try
                                {
                                    price = std::stod(prc);
                                    corrprc = true;
                                    price = std::stod(prc);
                                    dollars = std::floor(price); // get integer part of the price
                                    cents = std::round((price - dollars) * 100);
                                    double nearest_multiple_of_5 = std::round(cents / 5.0) * 5.0; // get the nearest multiple of 5
                                    double difference = std::fabs(cents - nearest_multiple_of_5); // get the absolute difference
                                    while (!(difference < epsilon))
                                    {
                                        std::cout << "Error:Enter dollars and cents";
                                        std::cout << "Enter the price for the item: ";
                                        std::getline(std::cin, prc);

                                        price = std::stod(prc);
                                        dollars = std::floor(price);                 // get integer part of the price
                                        cents = std::round((price - dollars) * 100); // get cents rounded to the nearest integer

                                        nearest_multiple_of_5 = std::round(cents / 5.0) * 5.0; // get the nearest multiple of 5
                                        std::cout<<nearest_multiple_of_5<<"\n";
                                        difference = std::fabs(cents - nearest_multiple_of_5); // get the absolute difference
                                        std::cout<< difference<<"\n";
                                    }
                                    choice = itemstock.addNewNode(newId, name, description, dollars, cents);
                                    choice = mainMenu();
                                }
                                catch (const std::invalid_argument &e)
                                {
                                    ifpriceEntered =false;
                                    corrprc = false;
                                }
                            }
                            
                    }
                }
            }
        }
        else if (choice == "5")
        {
            std::cout << "Enter the item id of the item to remove from the menu: " << std::endl;
            std::string id_name = readInput();
            if (id_name.empty())
            {
                choice = mainMenu();
            }
            else
            {
                itemstock.remove(id_name);
                choice = mainMenu();
            }
        }
        else if (choice == "6")
        { // to do
            coinstock.printCoins();
            choice = mainMenu();
        }
        else if (choice == "7")
        { // to do
            itemstock.resetStock();
            choice = mainMenu();
        }
        else if (choice == "8")
        { // to do
            coinstock.resetCoins();
            choice = mainMenu();
        }
        else if (choice == "9")
        { // segmentation error needs to be fixed
            return EXIT_SUCCESS;   
        }
        else
        {
            std::cout << "Invalid Input please re-enter"
                      << "\n"
                      << std::endl;
            choice = mainMenu();
        }
    }
}



std::string mainMenu()
{
    std::cout << "Main Menu:" << std::endl;
    std::cout << "    1.Display Items" << std::endl;
    std::cout << "    2.Purhcase Items" << std::endl;
    std::cout << "    3.Save and Exit" << std::endl;
    std::cout << "Administrator-Only Menu:" << std::endl;
    std::cout << "    4.Add Items" << std::endl;
    std::cout << "    5.Remove Item" << std::endl;
    std::cout << "    6.Display Coins" << std::endl;
    std::cout << "    7.Reset Stock" << std::endl;
    std::cout << "    8.Reset Coins" << std::endl;
    std::cout << "    9.Abort Program" << std::endl;
    std::cout << "Select your option (1-9)" << std::endl;
    std::string option = readInput();
    return option;
}

std::string readInput()
{
    std::string input;
    std::getline(std::cin, input);
    std::cout << std::endl;
    return input;
}

std::string displayItems(LinkedList &stock)
{
    Node *currentNode = stock.head;
    std::cout << "Items Menu" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << std::left << std::setw(6) << "ID"
              << " | " << std::setw(50) << "Name"
              << " | " << std::setw(10) << "Available"
              << " | " << std::setw(6) << "Price" << std::endl;
    std::cout << std::setfill('-') << std::setw(79) << "-" << std::setfill(' ') << std::endl;
    while (currentNode != nullptr)
    {
        std::cout << std::left << std::setw(6) << currentNode->data->id << " | " << std::setw(50) << currentNode->data->name << " | " << std::setw(10) << currentNode->data->on_hand << " | $" << currentNode->data->price.dollars << "." << currentNode->data->price.cents << std::endl;
        currentNode = currentNode->next;
    }
    std::cout << std::endl;
    return "0";
}