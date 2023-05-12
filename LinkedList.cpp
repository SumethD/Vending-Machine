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
    if (head == nullptr) {
        return;
    }
    Node* current = head;
    Node* next = head->next;
    while (next != nullptr)
    {
        delete current;
        current = next;
        next = current->next;
    }
    delete current;
    head = nullptr;
    count = 0;
}

bool LinkedList::loadData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file " << filename << std::endl;
        return false;
    }

    std::string line;
bool allLinesValid = true; // initialize variable to true

while (std::getline(file, line)) {
    // Split the line into fields using '|' as the delimiter
    std::istringstream iss(line);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(iss, field, '|')) {
        fields.push_back(field);
    }

    // Check if all conditions are met
    bool validLine = true;

    // Check if ID has a length of 5 and meets the format requirements
    if (fields[0].length() != 5 || fields[0][0] != 'I' || !std::isdigit(fields[0][1]) || !std::isdigit(fields[0][2]) || !std::isdigit(fields[0][3]) || !std::isdigit(fields[0][4])) {
        validLine = false;
    }

    // Check if name is less than 40 characters
    if (fields[1].length() >= 40) {
        validLine = false;
    }

    // Check if description is less than 255 characters
    if (fields[2].length() >= 255) {
        validLine = false;
    }

    // Check if on-hand value is an integer
    try {
        std::stoi(fields[4]);
    } catch (const std::invalid_argument&) {
        validLine = false;
    }

    // If any condition is not met, mark the line as invalid
    if (!validLine) {
        allLinesValid = false;
    } else {
        // Check if ID already exists in the list
        bool idExists = false;
        Node* current = head;
        while (current != nullptr) {
            if (current->data->id == fields[0]) {
                idExists = true;
                break;
            }
            current = current->next;
        }

        // If ID doesn't exist, add the new node to the end of the list
        if (!idExists) {
            Node* newNode = new Node();
            newNode->data->id = fields[0];
            newNode->data->name = fields[1];
            newNode->data->description = fields[2];
            newNode->data->on_hand = std::stoi(fields[4]);

            double value = std::stod(fields[3]);
            int dollars = std::floor(value); // get integer part
            int cents = std::round(((value - dollars) * 100));

            if (cents == 0) {
                std::stringstream ss;
                ss << std::setw(2) << std::setfill('0') << cents;
                newNode->data->price.cents = ss.str();
            } else {
                newNode->data->price.cents = std::to_string(cents);  
            }

            newNode->data->price.dollars = dollars;

            // Add the new Node to the end of the list
            if (head == nullptr) {
                head = newNode;
            } else {
                current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newNode;
            }
            count++;
        }
    }
}

file.close();
return allLinesValid;
}


void LinkedList::sortByName() {
    Node* current = head;

    while (current != nullptr)
    {
        Node* minNode = current;
        Node* searchNode = current->next;

        while (searchNode != nullptr)
        {
            if (searchNode->data->name < minNode->data->name) {
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

void LinkedList::remove(const std::string id) {

     if (head == nullptr) {
        std::cout << "List is empty." << std::endl;
        return;
    }

    // Check if the node to be removed is the head node
    if (head->data->id == id) {
        Node* temp = head;
        head = head->next;
        std::cout <<'"'<< id << " - " << temp->data->name << " - " << temp->data->description << '"'<< " has been removed from the system." << std::endl;
        delete temp;
        return;
    }

    // Traverse the list to find the node to be removed
    Node* curr = head;
    Node* prev = nullptr;
    while (curr != nullptr && curr->data->id != id) {
        prev = curr;
        curr = curr->next;
    }

    // If the node is not found in the list
    if (curr == nullptr) {
        std::cout << "Node with ID " << id << " not found." << std::endl;
        return;
    }

    // Remove the node
    prev->next = curr->next;
    std::cout <<'"'<< id << " - " << curr->data->name << " - " << curr->data->description << '"'<< " has been removed from the system." << std::endl;
    delete curr;
}

// Find out the nextId of the list
std::string LinkedList::nextID() {
    if (head == nullptr) {
        return "I0001";
    }

    Node* current = head;
    std::string lastId = current->data->id;
    while (current->next != nullptr) {
        current = current->next;
        std::string currentId = current->data->id;
        if (currentId > lastId) {
            lastId = currentId;
        }
    }

    int idNum = std::stoi(lastId.substr(1)) + 1;
    std::string newId = "I000" + std::to_string(idNum);
    return newId;
}


std::string LinkedList::addNewNode(const std::string& newId, const std::string& name, const std::string& description, int dollars, int cents) {
    // Create a new Node and populate it with the provided data
    Node* newNode = new Node();
    newNode->data->id = newId;
    newNode->data->name = name;
    newNode->data->description = description;
    newNode->data->on_hand = 20;


    if (cents == 0){
            std::stringstream ss;
            ss << std::setw(2) << std::setfill('0') << cents;
            newNode->data->price.cents =ss.str();
        }
        else{
            newNode->data->price.cents =std::to_string(cents);  
        }


    newNode->data->price.dollars = dollars;

    // Add the new Node to the end of the list
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

    std::cout<< "This item " <<'"'<< name << "-"<< description <<'"' <<" has now been added to the menu."<< "\n"<<  std::endl;
    std::string input;
    return input;
}

void LinkedList::resetStock() {
    Node* current = head;
    while (current != nullptr) {
        current->data->on_hand = 20;
        current = current->next;
    }
    std::cout << "All stock has been reset to the default level of " << 20 << std::endl;

}

void LinkedList::saveStock(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        file << std::setfill('0') << std::setw(4) << current->data->id << "|" 
             << current->data->name << "|" 
             << current->data->description << "|" 
             << current->data->price.dollars << "." 
             << std::setw(2) << std::setfill('0') << current->data->price.cents << "|" 
             << current->data->on_hand << std::endl;

        current = current->next;
    }
    file.close();
    std::cout << "Data saved to file " << filename << std::endl;
}

bool LinkedList::get(std::string identity) {
    Node* current = head;
    bool isPresent = false;
    while(current != nullptr){
        std::string new_id = current->data->id;

        if(new_id == identity){
            isPresent = true;
        }
        current = current->next; // move to next node
    }
    return isPresent;
}


Price LinkedList::getPrice(std::string id) {
    Node* curr = head;
    while(curr != nullptr){
        std::string new_id = curr->data->id;
        Price pr = curr->data->price;

        if(new_id == id){
            return pr;
        }

        curr = curr->next;
    }

    // Item with the given ID was not found, return a default Price object
    return Price{0, "00"};
}
Stock* LinkedList::getStock(std::string id) {
    Node* curr = head;
    while(curr != nullptr){
        std::string new_id = curr->data->id;
        Stock* stock = curr->data;

        if(new_id == id){
            return stock;
        }

        curr = curr->next; // move to the next node
    }

    return nullptr; // ID not found, return nullptr
}


