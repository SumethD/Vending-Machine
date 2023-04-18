#include "LinkedList.h"
#include <fstream>  // for file input stream
#include <sstream>  // for string stream
#include <string>   // for string class
#include <iostream> // for console input/output
#include <iomanip>  // for output formatting
#include <vector>   // for std::vector container
#include <cmath>



LinkedList::LinkedList() {
   head = nullptr;
   count =0;
}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    count = 0;
}

void LinkedList::loadData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Split the line into fields using '|' as the delimiter
        std::istringstream iss(line);
        std::vector<std::string> fields;
        std::string field;
        while (std::getline(iss, field, '|')) {
            fields.push_back(field);
        }

    //     // Create a new Node and populate it with data from the fields
        Node* newNode = new Node();
        newNode->data->id = fields[0];
        newNode->data->name = fields[1];
        newNode->data->description = fields[2];
        newNode->data->on_hand = std::stoi(fields[4]);

        double value =std::stod(fields[3]) ;
        int dollars = std::floor(value); // get integer part
        int cents = (value - dollars) * 100; // get decimal part as cents

        newNode->data->price.dollars = dollars;
        newNode->data->price.cents =cents;



        //Add the new Node to the end of the list
        if (head == nullptr) {
            head = newNode;
        } 
        else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;

        }
        count++;
    }

    file.close();
}

void LinkedList::sortByName()
{
    Node* current = head;

    while (current != nullptr)
    {
        Node* minNode = current;
        Node* searchNode = current->next;

        while (searchNode != nullptr)
        {
            if (searchNode->data->name < minNode->data->name)
            {
                minNode = searchNode;
            }
            searchNode = searchNode->next;
        }

        // Swap the current node and the minimum node
        Stock* temp = current->data;
        current->data = minNode->data;
        minNode->data = temp;

        current = current->next;
    }
}

