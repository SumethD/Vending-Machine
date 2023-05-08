#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    Node* head;

    // more functions to be added perhaps...
    void loadData(const std::string& filename);
    void sortByName();
    void remove(std::string id);
    std::string nextID();
    std::string addNewNode(const std::string& newId, const std::string& name, const std::string& description, int dollars, int cents);
    void resetStock();
    void saveStock(const std::string& filename) const;
    bool get(std::string id);
    Price getPrice(std::string id);
    int getStock(std::string id);
private:
    // the beginning of the list
    // how many nodes are there in the list?
    unsigned count;
    
};

#endif  // LINKEDLIST_H


