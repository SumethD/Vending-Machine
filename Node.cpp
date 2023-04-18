#include "Node.h"

Node::Node(){
    data = new Stock();
    next =nullptr;
};
Node::~Node(){
    delete data;
    data = nullptr;
    next = nullptr;
};