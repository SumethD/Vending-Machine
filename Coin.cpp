#include "Coin.h"
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>
#include <cmath>
#include <iomanip>
std::map<int, int> coinCounts;


void Coin::loadCoin(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file " << filename << std::endl;
        return;
    }
     // map to store the coin counts by denomination
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::getline(iss, token, DELIM); // read the denomination
        int denom = std::stoi(token);
        std::getline(iss, token); // read the count
        int count = std::stoi(token);
        coinCounts[denom] = count;
    }

    // populate the coin counts in the Coin object
    denom = FIVE_CENTS;
    count= coinCounts[5];
    denom = TEN_CENTS;
    count = coinCounts[10];
    denom = TWENTY_CENTS;
    count = coinCounts[20];
    denom = FIFTY_CENTS;
    count = coinCounts[50];
    denom = ONE_DOLLAR;
    count = coinCounts[100];
    denom = TWO_DOLLARS;
    count = coinCounts[200];
    denom = FIVE_DOLLARS;
    count = coinCounts[500];
    denom = TEN_DOLLARS;
    count = coinCounts[1000];

    file.close();
}

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
}

bool Coin::newCoin(int cents){
    bool val = false;
    if (cents == 5 || cents == 10 || cents == 50 || cents == 100 || cents == 200 || cents == 500 || cents == 1000) {
        coinCounts[cents]++;
        val = true;
    }
    return val;
}



