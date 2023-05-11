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
        std::cerr << "Use: " << argv[0] << " stock coins" << std::endl;
        return 1;
    }

    std::string stockFile = argv[1];
    std::string coinsFile = argv[2];
    bool incorrect_f = false;
    LinkedList itemstock;
    Coin coinstock;

    std::string filename = stockFile;
    std::string coinsf = coinsFile;

    // Check if coins file has exactly 8 lines
    std::ifstream coins(coinsf);
    std::string line;
    int count = 0;
    while (std::getline(coins, line)) {
        count++;
    }
    while (count != 8) {
        std::cerr << "Coins file should have exactly 8 lines" << std::endl;
        std::cout << "Please enter the correct coins file: ";
        incorrect_f= true;
        std::cin >> coinsf;
        coins.open(coinsf);
        count = 0;
        while (std::getline(coins, line)) {
            count++;
        }
        coins.close();
    }

    std::string new_coinsfile = "new_coins.dat";
    std::string new_stockfile = "new_stock.dat";

    coinstock.loadCoin(coinsf);
    itemstock.loadData(filename);

    itemstock.sortByName();
    if (incorrect_f){
        choice = mainMenu();
        std::getline(std::cin, choice);
    }else{
        choice = mainMenu();
    }
    bool exitLoop = false;
    while (!exitLoop) {
        // check if the input is empty (i.e., "Enter" was pressed)
        if (choice.empty()) {
            exitLoop = true;
        }
        //displays item if 1 input
        else if (choice == "1") { 
            std::string newd = displayItems(itemstock);
            choice = mainMenu();
        }
        else if (choice == "2") {
            bool menutype =true,to_menu = false,invalid=false;
            Stock * itm =nullptr;
            std::string item_id,final_c="",centz;
            int cents,item_prc,five_c=0, ten_c=0,twenty_c=0,fifty_c=0,one_d=0,two_d=0,five_d=0,ten_d=0;
            float int_item,final_total=0;
            int remainder =1;
            std::vector<int> change_vec;
            std::cout << "Purchase Item" << std::endl;
            std::cout << "--------------------" << std::endl;
            std::cout << "Please enter the id of the item you wish to purchase:" << std::endl;
            std::getline(std::cin, item_id);
            while(!itemstock.get(item_id)){
                    std::cout <<"The " << item_id << " is invalid, ENTER a different ID: " << std::endl;
                    std::getline(std::cin, item_id);
            };
            if(itemstock.get(item_id)){
                Price prc= itemstock.getPrice(item_id);
                itm = itemstock.getStock(item_id);
                std::string price_str = std::to_string(prc.dollars) + "." + prc.cents;
                item_prc = std::stod(price_str) * 100;
                std::cout << item_prc << std::endl;
                std::cout << "You have selected "<< '"'<< itm->name << "-"<<itm->description <<'"'<<".This will cost you $"<< prc.dollars<<"."<<prc.cents<< std::endl;
                std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;
                std::getline(std::cin, centz);
                if (centz.empty()){
                    to_menu= true;
                }
                else{
                    while(!invalid){
                        try{
                        cents = std::stoi(centz);
                        invalid= true;
                        }catch(const std::invalid_argument& e){
                            std::cout <<"Error wrong format of currecny"<< std::endl;
                            std::getline(std::cin, centz);

                        }
                    }

                    while(!coinstock.newCoin(cents)){
                        std::cout <<"Error:"<< cents/100.0 <<  "$ is not a valid denomination of money. Please try again."<< std::endl;
                        std::getline(std::cin, centz);
                        invalid =false;
                        while(!invalid){
                            try{
                            cents = std::stoi(centz);
                            invalid= true;
                            }catch(const std::invalid_argument& e){
                                std::cout <<"Error wrong format of currecny"<< std::endl;
                                std::getline(std::cin, centz);

                            }
                        }
    
                    };
                    remainder = cents -item_prc;
                    while(remainder !=0){
                        if (remainder <0){
                            item_prc = std::abs(remainder); 
                            int_item = item_prc / 100.0;
                            std::cout << "You still need to give $" << int_item << std::endl;
                            std::getline(std::cin, centz);
                            invalid =false;
                            while(!invalid){
                                try{
                                cents = std::stoi(centz);
                                invalid= true;
                                }catch(const std::invalid_argument& e){
                                    std::cout <<"Error wrong format of currecny"<< std::endl;
                                    std::getline(std::cin, centz);

                                }
                            }
                            while(!coinstock.newCoin(cents)){
                                std::cout <<"Error:"<< cents/100.0 <<  "$ is not a valid denomination of money. Please try again."<< std::endl;
                                std::getline(std::cin, centz);
                                    invalid =false;
                                    while(!invalid){
                                    try{
                                    cents = std::stoi(centz);
                                    invalid= true;
                                    }catch(const std::invalid_argument& e){
                                        std::cout <<"Error wrong format of currecny"<< std::endl;
                                        std::getline(std::cin, centz);

                                }
                            }
                            };
                            remainder = cents - item_prc;
                            menutype =false;
                        }
                        else if(remainder >0){
                            change_vec=coinstock.getChange(remainder);
                            for (int element : change_vec) {
                                if (element == 1000) {
                                    ten_d += 1;
                                    remainder-= 1000;
                                } else if (element == 500) {
                                    five_d += 1;
                                    remainder-= 500;
                                } else if (element == 200) {
                                    two_d += 1;
                                    remainder-= 200;
                                } else if (element == 100) {
                                    one_d += 1;
                                    remainder-= 100;
                                } else if (element == 50) {
                                    fifty_c += 1;
                                    remainder-= 50;
                                } else if (element == 20) {
                                    twenty_c += 1;
                                    remainder-= 20;
                                } else if (element == 10) {
                                    ten_c += 1;
                                    remainder-= 10;
                                } else if (element == 5) {
                                    five_c += 1;
                                    remainder-= 5;
                                }
                            }
                            for (int i = 0; i < ten_d; i++) {
                                final_c += "$10 ";
                                final_total+=1000;
                            }
                            for (int j = 0; j < five_d; j++) {
                                final_c += "$5 ";
                                final_total+=500;
                            }

                            for (int k = 0; k < two_d; k++) {
                                final_c += "$2 ";
                                final_total+=200;
                            }

                            for (int l = 0; l < one_d; l++) {
                            final_c += "$1 ";
                            final_total+=100;
                            }

                            for (int m = 0; m < fifty_c; m++) {
                                final_c += "50c ";
                                final_total+=50;
                            }

                            for (int n = 0; n < twenty_c; n++) {
                                final_c += "20c ";
                                final_total+=20;
                        }

                            for (int o = 0; o < ten_c; o++) {
                                final_c += "10c ";
                                final_total+=10;
                            }

                            for (int p = 0; p < five_c; p++) {
                                final_c += "5c ";
                                final_total+=5;
                            }
                            menutype =true;
                    }
                }
                }
            }
            if (!to_menu){
                itm->on_hand --;
                final_total = final_total / 100.0;
                std::cout <<"Here is your "<<itm->name <<" and your change of $ "<<final_total<<": "<<final_c<< std::endl;
                if (menutype){
                    choice =mainMenu();
                    std::getline(std::cin, choice);
                    }else{
                choice =mainMenu();
                }
            }else{
                choice =mainMenu();
            }
                    
        }

        else if (choice == "3") {
            itemstock.saveStock(new_stockfile);
            coinstock.storeCoins(new_coinsfile);
            exitLoop =true;
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
