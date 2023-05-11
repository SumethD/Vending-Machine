#include "Coin.h"
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <unordered_set>
std::map<int, int> coinCounts;
std::unordered_set<int> denoms = {5, 10, 20, 50, 100, 200, 500, 1000};


void Coin::loadCoin(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file " << filename << std::endl;
        return;
    }

    // Initialize coinCounts to 0 for all denoms
    for (int denom : denoms) {
        coinCounts[denom] = 0;
    }

    std::string line;
    int count_line = 0;
    while (std::getline(file, line) && count_line < 8) {
        std::istringstream iss(line);
        std::string token;
        std::getline(iss, token, DELIM); // read the denomination
        int denom = std::stoi(token);
        std::getline(iss, token); // read the count
        int count = std::stoi(token);

        // If the denom is not in the set, reject the file
        if (denoms.find(denom) == denoms.end()) {
            std::cout << "File rejected: Invalid denomination " << denom << std::endl;
            // Set all coinCounts to 0 and return
            for (int denom : denoms) {
                coinCounts[denom] = 0;
            }
            file.close();
            return;
        }

        coinCounts[denom] = count;
        count_line++;
    }

    // If the file has more than 8 lines or less than 8 lines, reject it
    if (count_line != 8) {
        std::cout << "File rejected: Invalid number of lines " << count_line << std::endl;
        // Set all coinCounts to 0
        for (int denom : denoms) {
            coinCounts[denom] = 0;
        }
    }

    file.close();
}


// function to print coins
void Coin::printCoins() {
    std::cout << std::left << std::setw(15) << "Denomination" << "|" << std::setw(5) << "Count" << std::endl;
    std::cout << "------------------------" << std::endl;

    std::string denomStr;
    unsigned denomVal;
    int temp = 0;

    // Iterate through the denominations and print out the counts
    for (int i = 0; i < 8; i++) {
        denomVal = pow(10, i + 1);
        if (i < 2) {
            denomVal /= 2;
        }

        if (i == 0) {
            denomStr = "5 cents";
            temp = 5;
        }
        else if (i == 1) {
            denomStr = "10 cents";
            temp = 10;
        }
        else if (i == 2) {
            denomStr = "20 cents";
            temp = 20;
        }
        else if (i == 3) {
            denomStr = "50 cents";
            temp = 50;
        }
        else if (i == 4) {
            denomStr = "1 dollar";
            temp = 100;
        }
        else if (i == 5) {
            denomStr = "2 dollars";
            temp = 200;
        }
        else if (i == 6) {
            denomStr = "5 dollars";
            temp = 500;
        }
        else if (i == 7) {
            denomStr = "10 dollars";
            temp = 1000;
        }

        std::cout << std::left << std::setw(15) << denomStr << "|" << std::right << std::setw(5) << coinCounts[temp] << std::endl;
    }
    std::cout << std::endl;
}


void Coin::resetCoins() {
    coinCounts[5] = 20;
    coinCounts[10] = 20;
    coinCounts[20] = 20;
    coinCounts[50] = 20;
    coinCounts[100] = 20;
    coinCounts[200] = 20;
    coinCounts[500] = 20;
    coinCounts[1000] = 20;
    std::cout<< "All coins have been set to 20 "<< std::endl;

}

void Coin::storeCoins(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file " << filename << std::endl;
        return;
    }

    // write coin counts to file in format "denom|count"
    file << "5" << DELIM << coinCounts[5] << std::endl;
    file << "10" << DELIM << coinCounts[10] << std::endl;
    file << "20" << DELIM << coinCounts[20] << std::endl;
    file << "50" << DELIM << coinCounts[50] << std::endl;
    file << "100" << DELIM << coinCounts[100] << std::endl;
    file << "200"<< DELIM << coinCounts[200] << std::endl;
    file << "500" << DELIM << coinCounts[500] << std::endl;
    file << "1000" << DELIM << coinCounts[1000] << std::endl;

    file.close();
     std::cout << "Saved to new_stock.dat " << filename << std::endl;
}

bool Coin::newCoin(int cents){
    bool val = false;
    if (cents == 5 || cents == 10 || cents == 50 || cents == 100 || cents == 200 || cents == 500 || cents == 1000) {
        coinCounts[cents]++;
        val = true;
    }
    return val;
}

std::vector<int> Coin::getChange(int change) {
    std::vector<int> changeCoins;
    int remainingChange = change;

    if (remainingChange > 0) {
        if (remainingChange >= 1000 ) {
            coinCounts[1000] = coinCounts[1000]-1;
            changeCoins.push_back(1000);
            remainingChange -= 1000;
        }while (remainingChange >= 500 ) {
            coinCounts[500]--;
            changeCoins.push_back(500);
            remainingChange -= 500;
        }while (remainingChange >= 200 ) {
            coinCounts[200]--;
            changeCoins.push_back(200);
            remainingChange -= 200;
        } while (remainingChange >= 100 ) {
            coinCounts[100] = coinCounts[100]-1;
            changeCoins.push_back(100);
            remainingChange -= 100;
        }while (remainingChange >= 50) {
            coinCounts[50] = coinCounts[50]-1;
            changeCoins.push_back(50);
            remainingChange -= 50;
        }while (remainingChange >= 10 ) {
            coinCounts[10]--;
            changeCoins.push_back(10);
            remainingChange -= 10;
        }while (remainingChange >= 5 ) {
            coinCounts[5] = coinCounts[5] -1;
            changeCoins.push_back(5);
            remainingChange -= 5;
        } if (remainingChange ==0){
            // No suitable coin found to give change
           remainingChange =0;
        }
    }

    return changeCoins;
}

void Coin::addCents(int cents){
    if (cents == 1000){
       coinCounts[1000] = coinCounts[1000]+1; 
    }
    if (cents == 500){
       coinCounts[500] = coinCounts[500]+1; 
    }
    if (cents == 200){
       coinCounts[200] = coinCounts[200]+1; 
    }
    if (cents == 100){
       coinCounts[100] = coinCounts[100]+1; 
    }
    if (cents == 50){
       coinCounts[50] = coinCounts[50]+1; 
    }
    if (cents == 10){
       coinCounts[10] = coinCounts[10]+1; 
    }
    if (cents == 5){
       coinCounts[5] = coinCounts[5]+1; 
    }
}





