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
        int cents = std::round(((value - dollars) * 100));

        if (cents == 0){
            std::stringstream ss;
            ss << std::setw(2) << std::setfill('0') << cents;
            newNode->data->price.cents =ss.str();
        }
        else{
            newNode->data->price.cents =std::to_string(cents);  
        }


        newNode->data->price.dollars = dollars;
        



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




/*void LinkedList::writeData(std::ostream& filename)const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file " << filename << std::endl;
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        file << current->data->id << "|" << current->data->name << "|" << current->data->description << "|" << current->data->price.dollars << "." << std::setw(2) << std::setfill('0') << current->data->price.cents << "|" << current->data->on_hand << std::endl;
        current = current->next;
    }

    file.close();
}*/

void LinkedList::writeData(std::ostream& filename)const {
    std::ofstream file;
    file.open(&filename == &std::cout ? "/dev/null" : dynamic_cast<std::ostringstream&>(filename).str());
    if (!file.is_open()) {
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        file << current->data->id << "|" << current->data->name << "|" << current->data->description << "|" << current->data->price.dollars << "." << std::setw(2) << std::setfill('0') << current->data->price.cents << "|" << current->data->on_hand << std::endl;
        current = current->next;
    }

    file.close();
}
